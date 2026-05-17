/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpprotocolsettings.h"
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolPluginInterface : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolPluginInterface(QObject *parent = nullptr);
    ~McpProtocolPluginInterface() override;

    virtual void start() = 0;

    void setSettings(const McpProtocolSettings &settings);

    [[nodiscard]] bool canStart() const;

    virtual void send(const QJsonObject &obj) = 0;

    [[nodiscard]] McpProtocolSettings protocolSettings() const;

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj);
    void error(const QString &str);
    void finished();

private:
    McpProtocolSettings mProtocolSettings;
};
}
