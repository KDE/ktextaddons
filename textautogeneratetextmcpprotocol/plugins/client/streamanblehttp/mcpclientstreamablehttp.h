/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpbase.h"
#include "common/mcpprotocolsseparser.h"
#include <QJsonValue>
#include <QList>
#include <QPointer>
#include <QUrl>
#include <memory>
class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;
class QTimer;
class QJsonObject;
class McpClientStreambleHttpPluginInterface;
class McpClientStreamableHttp : public TextAutoGenerateTextMcpProtocolCore::McpBase
{
    Q_OBJECT
public:
    explicit McpClientStreamableHttp(McpClientStreambleHttpPluginInterface *interface, QObject *parent = nullptr);
    ~McpClientStreamableHttp() override;

    void connection() override;

    void send(const QJsonObject &obj) override;
    void stop() override;

private:
    // State of the SSE stream returned by a POST
    struct RequestStream {
        TextAutoGenerateTextMcpProtocolCore::McpProtocolSseParser parser;
        // Undefined when we post a notification or a response
        QJsonValue requestId;
        bool isInitializeRequest = false;
        bool responseReceived = false;
        int resumeAttempts = 0;
    };
    using RequestStreamPtr = std::shared_ptr<RequestStream>;

    [[nodiscard]] QNetworkRequest createRequest() const;
    void processEvents(const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolSseParser::Event> &events, RequestStream *stream = nullptr);
    void processMessage(const QJsonObject &obj, RequestStream *stream = nullptr);
    void processJsonBody(const QByteArray &body, RequestStream *stream = nullptr);
    void postFinished(QNetworkReply *reply, const RequestStreamPtr &stream);
    void requestStreamFinished(const RequestStreamPtr &stream);
    void resumeRequestStream(const RequestStreamPtr &stream);
    void trackReply(QNetworkReply *reply);
    void abortPendingReplies();
    void openEventStream();
    void eventStreamFinished(QNetworkReply *reply);
    void scheduleEventStreamReconnection();
    void sessionExpired();
    void closeEventStream();
    QNetworkAccessManager *const mNetworkAccessManager;
    McpClientStreambleHttpPluginInterface *const mInterface;
    QUrl mUrl;
    // Session id sent by server in initialize answer
    QByteArray mSessionId;
    // Protocol version negotiated during initialize
    QByteArray mProtocolVersion;
    // Optional GET stream used by server to send requests/notifications
    QNetworkReply *mEventStreamReply = nullptr;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSseParser mEventStreamParser;
    QTimer *const mReconnectTimer;
    // Number of reconnections without receiving data
    int mReconnectAttempts = 0;
    // POST and resumed streams in progress, aborted when we stop
    QList<QPointer<QNetworkReply>> mPendingReplies;
    // Incremented when we stop, invalidates scheduled resumptions
    quint64 mGeneration = 0;
    bool mStarted = false;
};
