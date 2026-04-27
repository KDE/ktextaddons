/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpprotocolplugin.h"
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolPluginInterface;
};
class McpServerPlugin : public TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin
{
    Q_OBJECT
public:
    explicit McpServerPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~McpServerPlugin() override;

    /*!
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface *
    createInterface(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType type, QObject *parent) override;
};
