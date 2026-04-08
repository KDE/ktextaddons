/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpprotocolplugininterface.h"
#include "mcpprotocolclientplugin_export.h"

class MCPPROTOCOLCLIENTPLUGIN_EXPORT McpClientStreambleHttpPluginInterface : public McpProtocol::McpProtocolPluginInterface
{
    Q_OBJECT
public:
    explicit McpClientStreambleHttpPluginInterface(QObject *parent = nullptr);
    ~McpClientStreambleHttpPluginInterface() override;

    void start() override;
    void send(const QJsonObject &obj) override;
};
