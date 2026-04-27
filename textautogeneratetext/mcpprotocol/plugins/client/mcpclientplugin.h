/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpprotocolplugin.h"
#include <QList>
#include <QVariant>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolPluginInterface;
};
class McpClientPlugin : public TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin
{
    Q_OBJECT
public:
    explicit McpClientPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~McpClientPlugin() override;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface *
    createInterface(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType type, QObject *parent) override;
};
