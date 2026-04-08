/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "common/mcpprotocolplugininterface.h"
#include "mcpprotocolclientplugin_export.h"
#include <QObject>
class McpClientStdio;
class MCPPROTOCOLCLIENTPLUGIN_EXPORT McpClientStdioPluginInterface : public McpProtocol::McpProtocolPluginInterface
{
    Q_OBJECT
public:
    explicit McpClientStdioPluginInterface(QObject *parent = nullptr);
    ~McpClientStdioPluginInterface() override;

    void start() override;

    void send(const QJsonObject &obj) override;

private:
    McpClientStdio *const mClientStdio;
};
