/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPlugin>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolSettings;
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolClient : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolClient(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType protocolType, QObject *parent = nullptr);
    ~McpProtocolClient() override;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType protocolType() const;
    void setSettings(const McpProtocolSettings &settings);

    void start();

    [[nodiscard]] bool canStart() const;

    void notify(const QJsonObject &obj);
    void request(const QJsonObject &obj);

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj);
    void error(const QString &str);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void emitNotificationOrRequest(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void loadPlugin();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initialize();
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType mProtocolType;
    McpProtocolPlugin *mPlugin = nullptr;
    McpProtocolPluginInterface *mPluginInterface = nullptr;
    McpProtocolSettings *mProtocolSettings = nullptr;
};
}
