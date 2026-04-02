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
class McpServerPlugin : public McpProtocol::McpProtocolPlugin
{
    Q_OBJECT
public:
    explicit McpServerPlugin(QObject *parent = nullptr);
    ~McpServerPlugin() override;

    /*!
     */
    [[nodiscard]] McpProtocol::McpProtocolPluginInterface *createInterface(McpProtocol::McpProtocolPlugin::ProtocolType type, QObject *parent) override;
};
