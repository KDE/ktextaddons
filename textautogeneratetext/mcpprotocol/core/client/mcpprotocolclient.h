/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "common/mcpprotocolplugin.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
namespace McpProtocol
{
class McpProtocolSettings;
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolClient : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolClient(McpProtocol::McpProtocolPlugin::ProtocolType protocolType, QObject *parent = nullptr);
    ~McpProtocolClient() override;

    [[nodiscard]] McpProtocol::McpProtocolPlugin::ProtocolType protocolType() const;
    void setSettings(McpProtocolSettings *settings);

    void start();

    [[nodiscard]] bool canStart() const;

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj);
    void error(const QString &str);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void loadPlugin();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initialize();
    const McpProtocol::McpProtocolPlugin::ProtocolType mProtocolType;
    McpProtocolPlugin *mPlugin = nullptr;
    McpProtocolPluginInterface *mPluginInterface = nullptr;
    McpProtocolSettings *mProtocolSettings = nullptr;
};
}
