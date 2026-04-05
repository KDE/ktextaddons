/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpprotocolplugin.h"
namespace McpProtocol
{
class McpProtocolPluginInterface;
};
class McpClientPlugin : public McpProtocol::McpProtocolPlugin
{
    Q_OBJECT
public:
    explicit McpClientPlugin(QObject *parent = nullptr);
    ~McpClientPlugin() override;

    [[nodiscard]] McpProtocol::McpProtocolPluginInterface *createInterface(McpProtocol::McpProtocolPlugin::ProtocolType type, QObject *parent) override;
};
