/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPlugin>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServer : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolServer(McpProtocolPlugin::TransportType protocolType, QObject *parent = nullptr);
    ~McpProtocolServer() override;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType protocolType() const;
    void setSettings(const McpProtocolSettings &settings);

    void start();

    [[nodiscard]] bool canStart() const;

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj);
    void error(const QString &str);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initialize();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void loadPlugin();
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType mProtocolType;
    McpProtocolPlugin *mPlugin = nullptr;
    McpProtocolPluginInterface *mPluginInterface = nullptr;
    McpProtocolSettings mProtocolSettings;
};
}
