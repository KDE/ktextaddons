/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "common/mcpprotocolplugininterface.h"
#include "mcpprotocolserverplugin_export.h"
#include <QObject>
class McpServerStdio;
class MCPPROTOCOLSERVERPLUGIN_EXPORT McpServerStdioPluginInterface : public McpProtocol::McpProtocolPluginInterface
{
    Q_OBJECT
public:
    explicit McpServerStdioPluginInterface(QObject *parent = nullptr);
    ~McpServerStdioPluginInterface() override;

    void start() override;

    void send(const QJsonObject &obj) override;

private:
    McpServerStdio *const mServerStdio;
};
