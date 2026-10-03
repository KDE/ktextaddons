/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientstreamablehttp.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include "mcpclientutils.h"
#include "streamablehttp/mcpclientstreamablehttpplugininterface.h"
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
#include <utility>

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

McpClientStreamableHttp::McpClientStreamableHttp(McpClientStreamableHttpPluginInterface *interface, QObject *parent)
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
    abortPendingReplies();
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
    // Server can answer with a SSE stream, each POST has its own stream.
    const auto stream = std::make_shared<RequestStream>();
    stream->isInitializeRequest = obj.value("method"_L1).toString() == "initialize"_L1;
    if (obj.contains("method"_L1)) {
        stream->requestId = obj.value("id"_L1);
    }
    QNetworkReply *reply = mNetworkAccessManager->post(request, QJsonDocument(obj).toJson(QJsonDocument::Compact));
    trackReply(reply);
    connect(reply, &QNetworkReply::readyRead, this, [this, reply, stream]() {
        if (isEventStream(reply)) {
            processEvents(stream->parser.feed(reply->readAll()), stream.get());
        }
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply, stream]() {
        postFinished(reply, stream);
    });
    connect(reply, &QNetworkReply::sslErrors, this, [](const QList<QSslError> &errors) {
        for (const QSslError &error : errors) {
            qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << error.errorString();
        }
    });
}

void McpClientStreamableHttp::postFinished(QNetworkReply *reply, const RequestStreamPtr &stream)
{
    reply->deleteLater();
    const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (reply->error() != QNetworkReply::NoError) {
        if (statusCode == 404 && !mSessionId.isEmpty()) {
            sessionExpired();
            return;
        }
        if (statusCode == 200 && isEventStream(reply)) {
            // SSE stream was cut, try to resume it
            qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Stream interrupted:" << reply->errorString();
            processEvents(stream->parser.feed(reply->readAll()), stream.get());
            requestStreamFinished(stream);
            return;
        }
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Post failed:" << statusCode << reply->errorString();
        // Body can contain a JSON-RPC error response
        if (reply->header(QNetworkRequest::ContentTypeHeader).toString().startsWith("application/json"_L1)) {
            processJsonBody(reply->readAll(), stream.get());
        }
        requestFailed(stream.get(), reply->errorString());
        return;
    }
    if (stream->isInitializeRequest) {
        mSessionId = reply->rawHeader("Mcp-Session-Id"_ba);
    }
    if (isEventStream(reply)) {
        processEvents(stream->parser.feed(reply->readAll()), stream.get());
        // Server can close stream before sending response
        requestStreamFinished(stream);
    } else if (statusCode != 202) {
        // 202 Accepted: notification or response sent, no body.
        processJsonBody(reply->readAll(), stream.get());
    }
}

void McpClientStreamableHttp::requestStreamFinished(const RequestStreamPtr &stream)
{
    if (!mStarted || stream->requestId.isUndefined() || stream->responseReceived) {
        return;
    }
    if (stream->parser.lastEventId().isEmpty()) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Stream closed before response, it can't be resumed. Request:" << stream->requestId;
        requestFailed(stream.get(), i18n("Connection lost before receiving answer."));
        return;
    }
    if (stream->resumeAttempts >= maxReconnectAttempts) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Too many attempts to resume stream. Request:" << stream->requestId;
        requestFailed(stream.get(), i18n("Connection lost before receiving answer."));
        return;
    }
    int delay = stream->parser.retry();
    if (delay < 0) {
        delay = std::min(defaultReconnectDelay << stream->resumeAttempts, maxReconnectDelay);
    }
    ++stream->resumeAttempts;
    qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Resume stream of request" << stream->requestId << "in" << delay << "ms";
    const quint64 generation = mGeneration;
    QTimer::singleShot(delay, this, [this, stream, generation]() {
        if (generation == mGeneration) {
            resumeRequestStream(stream);
        }
    });
}

void McpClientStreamableHttp::resumeRequestStream(const RequestStreamPtr &stream)
{
    if (!mStarted) {
        return;
    }
    // Server replays messages of the stream after this event id
    QNetworkRequest request = createRequest();
    request.setRawHeader("Accept"_ba, "text/event-stream"_ba);
    request.setRawHeader("Cache-Control"_ba, "no-cache"_ba);
    request.setRawHeader("Last-Event-ID"_ba, stream->parser.lastEventId());
    stream->parser.resetConnection();
    QNetworkReply *reply = mNetworkAccessManager->get(request);
    trackReply(reply);
    connect(reply, &QNetworkReply::readyRead, this, [this, reply, stream]() {
        const QByteArray data = reply->readAll();
        if (!data.isEmpty()) {
            stream->resumeAttempts = 0;
        }
        processEvents(stream->parser.feed(data), stream.get());
    });
    connect(reply, &QNetworkReply::finished, this, [this, reply, stream]() {
        reply->deleteLater();
        const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (statusCode == 404 && !mSessionId.isEmpty()) {
            sessionExpired();
            return;
        }
        if (statusCode == 405) {
            qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Server doesn't allow to resume stream. Request:" << stream->requestId;
            requestFailed(stream.get(), i18n("Connection lost before receiving answer."));
            return;
        }
        processEvents(stream->parser.feed(reply->readAll()), stream.get());
        requestStreamFinished(stream);
    });
}

void McpClientStreamableHttp::requestFailed(RequestStream *stream, const QString &errorMessage)
{
    Q_EMIT error(errorMessage);
    if (stream->requestId.isUndefined() || stream->responseReceived) {
        return;
    }
    // Server will never answer: create error response, so caller knows that request failed.
    stream->responseReceived = true;
    Q_EMIT received(McpClientUtils::createConnectionErrorResponse(stream->requestId, errorMessage));
}

void McpClientStreamableHttp::trackReply(QNetworkReply *reply)
{
    mPendingReplies.removeIf([](const QPointer<QNetworkReply> &pending) {
        return pending.isNull();
    });
    mPendingReplies.append(reply);
}

void McpClientStreamableHttp::abortPendingReplies()
{
    ++mGeneration;
    const QList<QPointer<QNetworkReply>> replies = std::exchange(mPendingReplies, {});
    for (const QPointer<QNetworkReply> &reply : replies) {
        if (reply) {
            reply->disconnect(this);
            reply->abort();
            reply->deleteLater();
        }
    }
}

void McpClientStreamableHttp::processJsonBody(const QByteArray &body, RequestStream *stream)
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
        processMessage(doc.object(), stream);
    } else if (doc.isArray()) {
        // JSON-RPC batch (protocol 2025-03-26)
        const QJsonArray array = doc.array();
        for (const auto &value : array) {
            if (value.isObject()) {
                processMessage(value.toObject(), stream);
            }
        }
    }
}

void McpClientStreamableHttp::processEvents(const QList<McpProtocolSseParser::Event> &events, RequestStream *stream)
{
    for (const auto &event : events) {
        if (event.event == "message") {
            processJsonBody(event.data, stream);
        } else {
            qCDebug(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Ignore event:" << event.event;
        }
    }
}

void McpClientStreamableHttp::processMessage(const QJsonObject &obj, RequestStream *stream)
{
    if (stream && !stream->requestId.isUndefined() && obj.value("id"_L1) == stream->requestId && (obj.contains("result"_L1) || obj.contains("error"_L1))) {
        stream->responseReceived = true;
    }
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
    abortPendingReplies();
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
    abortPendingReplies();
    mSessionId.clear();
    mProtocolVersion.clear();
    mStarted = false;
    Q_EMIT finished();
}

#include "moc_mcpclientstreamablehttp.cpp"
