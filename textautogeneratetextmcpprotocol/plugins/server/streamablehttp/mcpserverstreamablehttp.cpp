/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserverstreamablehttp.h"
#include "autogeneratetext_mcpprotocolserverplugin_lib_debug.h"
#include "streamablehttp/mcpserverstreamhttpplugininterface.h"
#include <KLocalizedString>
#include <QHostAddress>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUrl>
#include <QUuid>
#include <algorithm>
#include <utility>

using namespace Qt::Literals::StringLiterals;

namespace
{
constexpr qsizetype maxHeaderSize = 64 * 1024;
// Maximum size of a message (it can contain images or files)
constexpr qsizetype maxBodySize = 64 * 1024 * 1024;
// Messages kept while client doesn't listen event stream
constexpr qsizetype maxPendingMessages = 1000;
// JSON-RPC error codes
constexpr int parseErrorCode = -32700;
constexpr int invalidRequestCode = -32600;

[[nodiscard]] QByteArray idKey(const QJsonValue &id)
{
    if (id.isString()) {
        return 's' + id.toString().toUtf8();
    }
    if (id.isDouble()) {
        return 'n' + QByteArray::number(id.toDouble(), 'g', 17);
    }
    return {};
}

[[nodiscard]] bool isRequest(const QJsonObject &obj)
{
    return obj.contains("method"_L1) && obj.contains("id"_L1);
}

[[nodiscard]] bool isResponse(const QJsonObject &obj)
{
    return !obj.contains("method"_L1) && obj.contains("id"_L1) && (obj.contains("result"_L1) || obj.contains("error"_L1));
}

[[nodiscard]] QByteArray reasonPhrase(int status)
{
    switch (status) {
    case 200:
        return "OK"_ba;
    case 202:
        return "Accepted"_ba;
    case 400:
        return "Bad Request"_ba;
    case 403:
        return "Forbidden"_ba;
    case 404:
        return "Not Found"_ba;
    case 405:
        return "Method Not Allowed"_ba;
    case 406:
        return "Not Acceptable"_ba;
    case 411:
        return "Length Required"_ba;
    case 413:
        return "Content Too Large"_ba;
    case 431:
        return "Request Header Fields Too Large"_ba;
    case 501:
        return "Not Implemented"_ba;
    default:
        break;
    }
    return "Status"_ba;
}
}

McpServerStreamableHttp::McpServerStreamableHttp(McpServerStreamHttpPluginInterface *interface, QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpBase{parent}
    , mTcpServer(new QTcpServer(this))
    , mInterface(interface)
{
    connect(mTcpServer, &QTcpServer::newConnection, this, &McpServerStreamableHttp::newConnection);
}

McpServerStreamableHttp::~McpServerStreamableHttp()
{
    // Don't emit signals while we are destroyed.
    closeSockets();
}

void McpServerStreamableHttp::connection()
{
    if (mStarted) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Server already started:" << mTcpServer->serverAddress() << mTcpServer->serverPort();
        return;
    }
    const QUrl url = mInterface->protocolSettings().serverUrl();
    if (!url.isValid() || url.scheme() != "http"_L1 || url.port() <= 0) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Impossible to start server. Url is invalid:" << url;
        Q_EMIT error(i18n("Impossible to start server. URL is invalid."));
        Q_EMIT finished();
        return;
    }
    QHostAddress address;
    if (url.host().isEmpty() || url.host() == "localhost"_L1) {
        // Specification recommends to listen only on localhost
        address = QHostAddress::LocalHost;
    } else if (!address.setAddress(url.host())) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Impossible to start server. Host must be an IP address:" << url.host();
        Q_EMIT error(i18n("Impossible to start server. URL is invalid."));
        Q_EMIT finished();
        return;
    }
    if (!mTcpServer->listen(address, static_cast<quint16>(url.port()))) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Impossible to listen:" << url << mTcpServer->errorString();
        Q_EMIT error(i18n("Impossible to start server: %1", mTcpServer->errorString()));
        Q_EMIT finished();
        return;
    }
    mPath = url.path().isEmpty() ? u"/"_s : url.path();
    mSessionId.clear();
    mEventId = 0;
    mStarted = true;
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Listen on" << url;
    Q_EMIT started();
}

void McpServerStreamableHttp::stop()
{
    if (!mStarted) {
        return;
    }
    closeSockets();
    mTcpServer->close();
    mSessionId.clear();
    mStarted = false;
    Q_EMIT finished();
}

void McpServerStreamableHttp::closeSockets()
{
    // Sockets are children of server
    const QList<QTcpSocket *> sockets = mTcpServer->findChildren<QTcpSocket *>();
    mBuffers.clear();
    for (QTcpSocket *socket : sockets) {
        socket->disconnect(this);
        socket->abort();
        socket->deleteLater();
    }
    mPendingRequests.clear();
    mPendingMessages.clear();
    mEventStreamSocket.clear();
}

void McpServerStreamableHttp::newConnection()
{
    while (QTcpSocket *socket = mTcpServer->nextPendingConnection()) {
        mBuffers.insert(socket, {});
        connect(socket, &QTcpSocket::readyRead, this, [this, socket]() {
            readData(socket);
        });
        connect(socket, &QTcpSocket::disconnected, this, [this, socket]() {
            socketDisconnected(socket);
        });
    }
}

void McpServerStreamableHttp::socketDisconnected(QTcpSocket *socket)
{
    mBuffers.remove(socket);
    // Client doesn't wait for answers anymore
    mPendingRequests.removeIf([socket](const auto &it) {
        return it.value()->socket == socket;
    });
    if (mEventStreamSocket == socket) {
        mEventStreamSocket.clear();
    }
    socket->deleteLater();
}

void McpServerStreamableHttp::readData(QTcpSocket *socket)
{
    if (socket->state() != QAbstractSocket::ConnectedState) {
        // Response already sent
        return;
    }
    QByteArray &buffer = mBuffers[socket];
    buffer.append(socket->readAll());
    const qsizetype headerEnd = buffer.indexOf("\r\n\r\n");
    if (headerEnd == -1) {
        if (buffer.size() > maxHeaderSize) {
            writeResponse(socket, 431);
        }
        return;
    }
    HttpRequest request;
    const QList<QByteArray> lines = buffer.left(headerEnd).split('\n');
    const QList<QByteArray> requestLine = lines.constFirst().trimmed().split(' ');
    if (requestLine.count() != 3) {
        writeResponse(socket, 400);
        return;
    }
    request.method = requestLine.at(0);
    request.path = requestLine.at(1);
    for (qsizetype i = 1; i < lines.count(); ++i) {
        const QByteArray &line = lines.at(i);
        const qsizetype index = line.indexOf(':');
        if (index > 0) {
            request.headers.insert(line.left(index).trimmed().toLower(), line.mid(index + 1).trimmed());
        }
    }
    if (request.headers.contains("transfer-encoding")) {
        writeResponse(socket, 501);
        return;
    }
    bool ok = true;
    const QByteArray contentLengthHeader = request.headers.value("content-length");
    const qsizetype contentLength = contentLengthHeader.isEmpty() ? 0 : contentLengthHeader.toLongLong(&ok);
    if (!ok || contentLength < 0) {
        writeResponse(socket, 400);
        return;
    }
    if (contentLength > maxBodySize) {
        writeResponse(socket, 413);
        return;
    }
    if (request.method == "POST" && contentLengthHeader.isEmpty()) {
        writeResponse(socket, 411);
        return;
    }
    if (buffer.size() < headerEnd + 4 + contentLength) {
        return;
    }
    request.body = buffer.mid(headerEnd + 4, contentLength);
    // One request by connection: response closes connection
    mBuffers.remove(socket);
    disconnect(socket, &QTcpSocket::readyRead, this, nullptr);
    handleRequest(socket, request);
}

bool McpServerStreamableHttp::isAllowedOrigin(const HttpRequest &request) const
{
    // Protect against DNS rebinding attacks: only allow local web pages
    const QByteArray origin = request.headers.value("origin");
    if (origin.isEmpty()) {
        return true;
    }
    const QString host = QUrl(QString::fromUtf8(origin)).host();
    return host == "localhost"_L1 || QHostAddress(host).isLoopback() || QHostAddress(host) == mTcpServer->serverAddress();
}

void McpServerStreamableHttp::handleRequest(QTcpSocket *socket, const HttpRequest &request)
{
    if (QUrl(QString::fromUtf8(request.path)).path() != mPath) {
        writeResponse(socket, 404);
        return;
    }
    if (!isAllowedOrigin(request)) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Origin not allowed:" << request.headers.value("origin");
        writeResponse(socket, 403);
        return;
    }
    if (request.method == "POST") {
        handlePost(socket, request);
    } else if (request.method == "GET") {
        handleGet(socket, request);
    } else if (request.method == "DELETE") {
        handleDelete(socket, request);
    } else {
        writeResponse(socket, 405, {}, {}, {{"Allow"_ba, "GET, POST, DELETE"_ba}});
    }
}

bool McpServerStreamableHttp::checkSession(QTcpSocket *socket, const HttpRequest &request)
{
    const QByteArray sessionId = request.headers.value("mcp-session-id");
    if (sessionId.isEmpty()) {
        if (mSessionId.isEmpty()) {
            writeJsonRpcError(socket, 400, invalidRequestCode, u"Server not initialized"_s);
        } else {
            writeJsonRpcError(socket, 400, invalidRequestCode, u"Missing Mcp-Session-Id header"_s);
        }
        return false;
    }
    if (sessionId != mSessionId) {
        // Client must start a new session
        writeJsonRpcError(socket, 404, invalidRequestCode, u"Session not found"_s);
        return false;
    }
    return true;
}

void McpServerStreamableHttp::handlePost(QTcpSocket *socket, const HttpRequest &request)
{
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(request.body, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Invalid json:" << parseError.errorString();
        writeJsonRpcError(socket, 400, parseErrorCode, u"Parse error"_s);
        return;
    }
    QList<QJsonObject> messages;
    if (doc.isObject()) {
        messages.append(doc.object());
    } else if (doc.isArray()) {
        // JSON-RPC batch (protocol 2025-03-26)
        const QJsonArray array = doc.array();
        for (const auto &value : array) {
            if (!value.isObject()) {
                messages.clear();
                break;
            }
            messages.append(value.toObject());
        }
    }
    if (messages.isEmpty()) {
        writeJsonRpcError(socket, 400, invalidRequestCode, u"Invalid request"_s);
        return;
    }
    const bool initialize = std::any_of(messages.cbegin(), messages.cend(), [](const QJsonObject &obj) {
        return obj.value("method"_L1).toString() == "initialize"_L1;
    });
    if (initialize && messages.count() > 1) {
        writeJsonRpcError(socket, 400, invalidRequestCode, u"Initialize request must not be part of a batch"_s);
        return;
    }
    if (!initialize && !checkSession(socket, request)) {
        return;
    }

    auto pending = std::make_shared<PendingPost>();
    for (const QJsonObject &obj : std::as_const(messages)) {
        if (!isRequest(obj)) {
            continue;
        }
        const QByteArray key = idKey(obj.value("id"_L1));
        if (key.isEmpty() || mPendingRequests.contains(key) || pending->ids.contains(key)) {
            writeJsonRpcError(socket, 400, invalidRequestCode, u"Invalid request id"_s);
            return;
        }
        pending->ids.append(key);
    }

    if (initialize) {
        // New session: previous client can't use its session anymore
        terminateSession();
        mSessionId = QUuid::createUuid().toByteArray(QUuid::WithoutBraces);
    }
    if (pending->ids.isEmpty()) {
        // Only notifications or responses
        writeResponse(socket, 202);
    } else {
        pending->socket = socket;
        pending->batch = doc.isArray();
        pending->initialize = initialize;
        for (const QByteArray &key : std::as_const(pending->ids)) {
            mPendingRequests.insert(key, pending);
        }
    }
    // Responses can be sent synchronously in slots connected to received()
    for (const QJsonObject &obj : std::as_const(messages)) {
        qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << " received " << obj;
        Q_EMIT received(obj);
        if (!mStarted) {
            return;
        }
    }
}

void McpServerStreamableHttp::handleGet(QTcpSocket *socket, const HttpRequest &request)
{
    if (!request.headers.value("accept").contains("text/event-stream")) {
        writeResponse(socket, 406);
        return;
    }
    if (!checkSession(socket, request)) {
        return;
    }
    // Only one stream: messages must not be sent twice
    if (mEventStreamSocket) {
        mEventStreamSocket->disconnectFromHost();
    }
    mEventStreamSocket = socket;
    socket->write("HTTP/1.1 200 OK\r\nContent-Type: text/event-stream\r\nCache-Control: no-cache\r\nConnection: close\r\n\r\n"_ba);
    const QList<QJsonObject> messages = std::exchange(mPendingMessages, {});
    for (const QJsonObject &obj : messages) {
        sendEvent(obj);
    }
    socket->flush();
}

void McpServerStreamableHttp::handleDelete(QTcpSocket *socket, const HttpRequest &request)
{
    if (!checkSession(socket, request)) {
        return;
    }
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Client terminated session:" << mSessionId;
    terminateSession();
    writeResponse(socket, 200);
}

void McpServerStreamableHttp::terminateSession()
{
    mSessionId.clear();
    mPendingMessages.clear();
    if (mEventStreamSocket) {
        mEventStreamSocket->disconnectFromHost();
        mEventStreamSocket.clear();
    }
    const auto pendingRequests = std::exchange(mPendingRequests, {});
    for (const PendingPostPtr &pending : pendingRequests) {
        if (pending->socket) {
            pending->socket->disconnectFromHost();
        }
    }
}

void McpServerStreamableHttp::send(const QJsonObject &obj)
{
    if (!mStarted) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Server not started. Can't send message";
        Q_EMIT error(i18n("Server is not started."));
        return;
    }
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << " send " << obj;
    if (isResponse(obj)) {
        const QByteArray key = idKey(obj.value("id"_L1));
        if (const PendingPostPtr pending = mPendingRequests.take(key)) {
            pending->responses.insert(key, obj);
            if (pending->responses.count() == pending->ids.count()) {
                sendPostResponse(pending);
            }
            return;
        }
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "No pending request for response, client is disconnected:" << obj.value("id"_L1);
        return;
    }
    // Requests and notifications from server
    sendEvent(obj);
}

void McpServerStreamableHttp::sendPostResponse(const PendingPostPtr &pending)
{
    if (!pending->socket) {
        return;
    }
    QByteArray body;
    if (pending->batch) {
        QJsonArray array;
        for (const QByteArray &key : std::as_const(pending->ids)) {
            array.append(pending->responses.value(key));
        }
        body = QJsonDocument(array).toJson(QJsonDocument::Compact);
    } else {
        body = QJsonDocument(pending->responses.value(pending->ids.constFirst())).toJson(QJsonDocument::Compact);
    }
    QList<std::pair<QByteArray, QByteArray>> headers;
    if (pending->initialize && !mSessionId.isEmpty()) {
        headers.append({"Mcp-Session-Id"_ba, mSessionId});
    }
    writeResponse(pending->socket, 200, "application/json"_ba, body, headers);
}

void McpServerStreamableHttp::sendEvent(const QJsonObject &obj)
{
    if (!mEventStreamSocket || mEventStreamSocket->state() != QAbstractSocket::ConnectedState) {
        if (mPendingMessages.count() >= maxPendingMessages) {
            qCWarning(AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG) << "Client doesn't listen event stream, drop message";
            mPendingMessages.removeFirst();
        }
        mPendingMessages.append(obj);
        return;
    }
    ++mEventId;
    mEventStreamSocket->write("id: "_ba + QByteArray::number(mEventId) + "\ndata: "_ba + QJsonDocument(obj).toJson(QJsonDocument::Compact) + "\n\n"_ba);
    mEventStreamSocket->flush();
}

void McpServerStreamableHttp::writeResponse(QTcpSocket *socket,
                                            int status,
                                            const QByteArray &contentType,
                                            const QByteArray &body,
                                            const QList<std::pair<QByteArray, QByteArray>> &headers)
{
    QByteArray response = "HTTP/1.1 "_ba + QByteArray::number(status) + ' ' + reasonPhrase(status) + "\r\n"_ba;
    if (!contentType.isEmpty()) {
        response += "Content-Type: "_ba + contentType + "\r\n"_ba;
    }
    for (const auto &[name, value] : headers) {
        response += name + ": "_ba + value + "\r\n"_ba;
    }
    response += "Content-Length: "_ba + QByteArray::number(body.size()) + "\r\nConnection: close\r\n\r\n"_ba + body;
    socket->write(response);
    // Data is sent before connection is closed
    socket->disconnectFromHost();
}

void McpServerStreamableHttp::writeJsonRpcError(QTcpSocket *socket, int status, int code, const QString &message)
{
    const QJsonObject obj{
        {"jsonrpc"_L1, u"2.0"_s},
        {"id"_L1, QJsonValue::Null},
        {"error"_L1, QJsonObject{{"code"_L1, code}, {"message"_L1, message}}},
    };
    writeResponse(socket, status, "application/json"_ba, QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

#include "moc_mcpserverstreamablehttp.cpp"
