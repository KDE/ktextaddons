/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpprotocolplugininterface.h"
#include "mcpprotocolserverplugin_export.h"

class MCPPROTOCOLSERVERPLUGIN_EXPORT McpServerStreamHttpPluginInterface : public TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface
{
    Q_OBJECT
public:
    explicit McpServerStreamHttpPluginInterface(QObject *parent = nullptr);
    ~McpServerStreamHttpPluginInterface() override;

    void start() override;
    void send(const QJsonObject &obj) override;
};
