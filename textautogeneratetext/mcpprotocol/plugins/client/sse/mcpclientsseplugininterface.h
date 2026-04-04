/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "common/mcpprotocolplugininterface.h"
#include "mcpprotocolclientplugin_export.h"
#include <QObject>
class McpClientSse;
class MCPPROTOCOLCLIENTPLUGIN_EXPORT McpClientSsePluginInterface : public McpProtocol::McpProtocolPluginInterface
{
    Q_OBJECT
public:
    explicit McpClientSsePluginInterface(QObject *parent = nullptr);
    ~McpClientSsePluginInterface() override;
    void start() override;

private:
    McpClientSse *const mClientSse;
};
