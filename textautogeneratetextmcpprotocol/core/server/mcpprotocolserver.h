/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpprotocolplugin.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolSettings;
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServer : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolServer(McpProtocolPlugin::ProtocolType protocolType, QObject *parent = nullptr);
    ~McpProtocolServer() override;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType protocolType() const;
    void setSettings(McpProtocolSettings *settings);

    void start();

    [[nodiscard]] bool canStart() const;

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj);
    void error(const QString &str);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initialize();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void loadPlugin();
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::ProtocolType mProtocolType;
    McpProtocolPlugin *mPlugin = nullptr;
    McpProtocolPluginInterface *mPluginInterface = nullptr;
    McpProtocolSettings *mProtocolSettings = nullptr;
};
}
