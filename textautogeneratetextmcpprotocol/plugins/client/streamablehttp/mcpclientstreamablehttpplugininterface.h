/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpprotocolplugininterface.h"
#include "mcpprotocolclientplugin_export.h"
class McpClientStreamableHttp;

class MCPPROTOCOLCLIENTPLUGIN_EXPORT McpClientStreamableHttpPluginInterface : public TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface
{
    Q_OBJECT
public:
    explicit McpClientStreamableHttpPluginInterface(QObject *parent = nullptr);
    ~McpClientStreamableHttpPluginInterface() override;

    void start() override;
    void stop() override;
    void send(const QJsonObject &obj) override;

private:
    McpClientStreamableHttp *const mClientStreamableHttp;
};
