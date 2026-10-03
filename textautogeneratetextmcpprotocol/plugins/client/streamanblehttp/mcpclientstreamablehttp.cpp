/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstreamablehttp.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include "mcpclientutils.h"
#include "streamanblehttp/mcpclientstreamblehttpplugininterface.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslError>
#include <QTimer>
#include <algorithm>
#include <memory>

using namespace Qt::Literals::StringLiterals;
using TextAutoGenerateTextMcpProtocolCore::McpProtocolSseParser;

namespace
{
constexpr int defaultReconnectDelay = 1000;
constexpr int maxReconnectDelay = 30000;
constexpr int maxReconnectAttempts = 5;
[[nodiscard]] bool isEventStream(const QNetworkReply *reply)
{
    return reply->header(QNetworkRequest::ContentTypeHeader).toString().startsWith("text/event-stream"_L1);
}
}

McpClientStreamableHttp::McpClientStreamableHttp(McpClientStreambleHttpPluginInterface *interface, QObject *parent)
    : TextAutoGenerateTextMcpProtocolCore::McpBase{parent}
    , mNetworkAccessManager(new QNetworkAccessManager(this))
    , mInterface(interface)
    , mReconnectTimer(new QTimer(this))
{
    mReconnectTimer->setSingleShot(true);
    connect(mReconnectTimer, &QTimer::timeout, this, &McpClientStreamableHttp::openEventStream);
}

McpClientStreamableHttp::~McpClientStreamableHttp()
{
    // Don't emit signals while we are destroyed.
    closeEventStream();
}

void McpClientStreamableHttp::connection()
{
    if (mStarted) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Client already started:" << mUrl;
        return;
    }
    const QUrl url = mInterface->protocolSettings().serverUrl();
    if (!url.isValid() || (url.scheme() != "http"_L1 && url.scheme() != "https"_L1)) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Impossible to start client. Url is invalid:" << url;
        Q_EMIT error(i18n("Impossible to start client. Url is invalid."));
        Q_EMIT finished();
        return;
    }
    mUrl = url;
    mSessionId.clear();
    mProtocolVersion.clear();
    mEventStreamParser.clear();
    // There is no connection to open: each message is sent with a POST request.
    mStarted = true;
    Q_EMIT started();
}

QNetworkRequest McpClientStreamableHttp::createRequest() const
{
    QNetworkRequest request(mUrl);
    McpClientUtils::addHeaders(request, mInterface->protocolSettings().headers());
    if (!mSessionId.isEmpty()) {
        request.setRawHeader("Mcp-Session-Id"_ba, mSessionId);
    }
    if (!mProtocolVersion.isEmpty()) {
        request.setRawHeader("MCP-Protocol-Version"_ba, mProtocolVersion);
    }
    return request;
}

void McpClientStreamableHttp::send(const QJsonObject &obj)
{
    if (!mStarted) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Client not started. Can't send message";
        Q_EMIT error(i18n("Server is not ready."));
        return;
    }
    QNetworkRequest request = createRequest();
    request.setRawHeader("Accept"_ba, "application/json, text/event-stream"_ba);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"_ba);
    const bool isInitializeRequest = obj.value("method"_L1).toString() == "initialize"_L1;
    QNetworkReply *reply = mNetworkAccessManager->post(request, QJsonDocument(obj).toJson(QJsonDocument::Compact));
    // Server can answer with a SSE stream, each POST has its own stream.
    const auto parser = std::make_shared<McpProtocolSseParser>();
    connect(reply, &QNetworkReply::readyRead, this, [this, reply, parser]() {
        if (isEventStream(reply)) {
            processEvents(parser->feed(reply->readAll()));
        }
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply, isInitializeRequest, parser]() {
        postFinished(reply, isInitializeRequest, parser);
    });
    connect(reply, &QNetworkReply::sslErrors, this, [](const QList<QSslError> &errors) {
        for (const QSslError &error : errors) {
            qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << error.errorString();
        }
    });
}

void McpClientStreamableHttp::postFinished(QNetworkReply *reply, bool isInitializeRequest, const std::shared_ptr<McpProtocolSseParser> &parser)
{
    reply->deleteLater();
    const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->error() != QNetworkReply::NoError) {
        if (statusCode == 404 && !mSessionId.isEmpty()) {
            sessionExpired();
            return;
        }
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Post failed:" << statusCode << reply->errorString();
        Q_EMIT error(reply->errorString());
        // Body can contain a JSON-RPC error response
        if (reply->header(QNetworkRequest::ContentTypeHeader).toString().startsWith("application/json"_L1)) {
            processJsonBody(reply->readAll());
        }
        return;
    }
    if (isInitializeRequest) {
        mSessionId = reply->rawHeader("Mcp-Session-Id"_ba);
    }
    if (isEventStream(reply)) {
        processEvents(parser->feed(reply->readAll()));
    } else if (statusCode != 202) {
        // 202 Accepted: notification or response sent, no body.
        processJsonBody(reply->readAll());
    }
}

void McpClientStreamableHttp::processJsonBody(const QByteArray &body)
{
    if (body.trimmed().isEmpty()) {
        return;
    }
    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(body, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Invalid json:" << parseError.errorString() << body;
        return;
    }
    if (doc.isObject()) {
        processMessage(doc.object());
    } else if (doc.isArray()) {
        // JSON-RPC batch (protocol 2025-03-26)
        const QJsonArray array = doc.array();
        for (const auto &value : array) {
            if (value.isObject()) {
                processMessage(value.toObject());
            }
        }
    }
}

void McpClientStreamableHttp::processEvents(const QList<McpProtocolSseParser::Event> &events)
{
    for (const auto &event : events) {
        if (event.event == "message") {
            processJsonBody(event.data);
        } else {
            qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Ignore event:" << event.event;
        }
    }
}

void McpClientStreamableHttp::processMessage(const QJsonObject &obj)
{
    // Store negotiated version, it must be sent in each request after initialize.
    bool initializeResult = false;
    if (mProtocolVersion.isEmpty()) {
        const QJsonObject result = obj.value("result"_L1).toObject();
        if (result.contains("protocolVersion"_L1) && result.contains("serverInfo"_L1)) {
            mProtocolVersion = result.value("protocolVersion"_L1).toString().toLatin1();
            initializeResult = true;
        }
    }
    Q_EMIT received(obj);
    if (initializeResult) {
        // Client sent "notifications/initialized" when it received initialize result,
        // we can listen messages sent by server.
        openEventStream();
    }
}

void McpClientStreamableHttp::openEventStream()
{
    if (mEventStreamReply) {
        return;
    }
    if (!mStarted) {
        return;
    }
    QNetworkRequest request = createRequest();
    request.setRawHeader("Accept"_ba, "text/event-stream"_ba);
    request.setRawHeader("Cache-Control"_ba, "no-cache"_ba);
    // Ask server to resend messages sent while we were disconnected
    if (const QByteArray lastEventId = mEventStreamParser.lastEventId(); !lastEventId.isEmpty()) {
        request.setRawHeader("Last-Event-ID"_ba, lastEventId);
    }
    mEventStreamParser.resetConnection();
    QNetworkReply *reply = mNetworkAccessManager->get(request);
    mEventStreamReply = reply;
    connect(reply, &QNetworkReply::readyRead, this, [this, reply]() {
        const QByteArray data = reply->readAll();
        if (!data.isEmpty()) {
            // Server is alive, reset backoff
            mReconnectAttempts = 0;
        }
        processEvents(mEventStreamParser.feed(data));
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        eventStreamFinished(reply);
    });
}

void McpClientStreamableHttp::eventStreamFinished(QNetworkReply *reply)
{
    if (mEventStreamReply == reply) {
        mEventStreamReply = nullptr;
    }
    reply->deleteLater();
    const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode == 405) {
        // Server doesn't support it. It's allowed by specification.
        qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Server doesn't provide event stream";
        return;
    }
    if (statusCode == 404 && !mSessionId.isEmpty()) {
        sessionExpired();
        return;
    }
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Event stream closed:" << statusCode << reply->errorString();
    // Server can close stream at any time, reconnect
    scheduleEventStreamReconnection();
}

void McpClientStreamableHttp::scheduleEventStreamReconnection()
{
    if (!mStarted) {
        return;
    }
    if (mReconnectAttempts >= maxReconnectAttempts) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Event stream: too many reconnection attempts, give up";
        return;
    }
    int delay = mEventStreamParser.retry();
    if (delay < 0) {
        // No delay sent by server: exponential backoff
        delay = std::min(defaultReconnectDelay << mReconnectAttempts, maxReconnectDelay);
    }
    ++mReconnectAttempts;
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Reconnect event stream in" << delay << "ms";
    mReconnectTimer->start(delay);
}

void McpClientStreamableHttp::sessionExpired()
{
    qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Session expired:" << mSessionId;
    mSessionId.clear();
    mProtocolVersion.clear();
    mStarted = false;
    closeEventStream();
    Q_EMIT error(i18n("Session expired. Client must be restarted."));
    // Allow client to restart a new session
    Q_EMIT finished();
}

void McpClientStreamableHttp::closeEventStream()
{
    mReconnectTimer->stop();
    mReconnectAttempts = 0;
    if (mEventStreamReply) {
        mEventStreamReply->disconnect(this);
        mEventStreamReply->abort();
        mEventStreamReply = nullptr;
    }
}

void McpClientStreamableHttp::stop()
{
    if (!mStarted) {
        return;
    }
    if (!mSessionId.isEmpty()) {
        // Tell server that we don't need session anymore
        QNetworkReply *reply = mNetworkAccessManager->deleteResource(createRequest());
        connect(reply, &QNetworkReply::finished, this, [reply]() {
            // 405: server doesn't allow client to terminate session. It's allowed by specification.
            qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG)
                << "Delete session:" << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() << reply->errorString();
            reply->deleteLater();
        });
    }
    closeEventStream();
    mSessionId.clear();
    mProtocolVersion.clear();
    mStarted = false;
    Q_EMIT finished();
}

#include "moc_mcpclientstreamablehttp.cpp"
