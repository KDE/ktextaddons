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
class QJsonObject;
class McpClientSsePluginInterface;
class McpClientSse : public TextAutoGenerateTextMcpProtocolCore::McpBase
{
    Q_OBJECT
public:
    explicit McpClientSse(McpClientSsePluginInterface *interface, QObject *parent = nullptr);
    ~McpClientSse() override;

    void connection() override;

    void send(const QJsonObject &obj) override;

private:
    void slotRead(QNetworkReply *reply);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSseParser mParser;
    // Url used to post messages, sent by server in "endpoint" event
    QUrl mPostUrl;
    QNetworkAccessManager *const mNetworkAccessManager;
    QNetworkReply *mReply = nullptr;
    McpClientSsePluginInterface *const mInterface;
};
