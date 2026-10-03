/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpbase.h"
#include "common/mcpprotocolsseparser.h"
#include <QUrl>
class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;
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
    [[nodiscard]] QNetworkRequest createRequest() const;
    void processEvents(const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolSseParser::Event> &events);
    void processMessage(const QJsonObject &obj);
    void processJsonBody(const QByteArray &body);
    void postFinished(QNetworkReply *reply, bool isInitializeRequest, const std::shared_ptr<TextAutoGenerateTextMcpProtocolCore::McpProtocolSseParser> &parser);
    void openEventStream();
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
    bool mStarted = false;
};
