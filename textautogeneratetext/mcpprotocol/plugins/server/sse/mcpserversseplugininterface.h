/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "common/mcpprotocolplugininterface.h"
#include "mcpprotocolclientplugin_export.h"
#include <QObject>
class McpClientSse;
class MCPPROTOCOLCLIENTPLUGIN_EXPORT McpServerSsePluginInterface : public McpProtocol::McpProtocolPluginInterface
{
    Q_OBJECT
public:
    explicit McpServerSsePluginInterface(QObject *parent = nullptr);
    ~McpServerSsePluginInterface() override;
    void start() override;

    void send(const QJsonObject &obj) override;

private:
    McpClientSse *const mClientSse;
};
