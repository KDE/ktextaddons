/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpprotocolplugininterface.h"
#include "mcpprotocolserverplugin_export.h"

class MCPPROTOCOLSERVERPLUGIN_EXPORT McpServerStreambleHttpPluginInterface : public TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface
{
    Q_OBJECT
public:
    explicit McpServerStreambleHttpPluginInterface(QObject *parent = nullptr);
    ~McpServerStreambleHttpPluginInterface() override;

    void start() override;
    void send(const QJsonObject &obj) override;
};
