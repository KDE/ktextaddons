/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "common/mcpprotocolplugininterface.h"
#include "mcpprotocolserverplugin_export.h"
#include <QObject>
class McpServerSse;
class MCPPROTOCOLSERVERPLUGIN_EXPORT McpServerSsePluginInterface : public TextAutoGenerateTextMcpProtocolCore::McpProtocolPluginInterface
{
    Q_OBJECT
public:
    explicit McpServerSsePluginInterface(QObject *parent = nullptr);
    ~McpServerSsePluginInterface() override;
    void start() override;

    void send(const QJsonObject &obj) override;

private:
    McpServerSse *const mServerSse;
};
