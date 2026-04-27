/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
#include <memory>
namespace McpProtocol
{
class McpProtocolSettings;
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolPluginInterface : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolPluginInterface(QObject *parent = nullptr);
    ~McpProtocolPluginInterface() override;

    virtual void start() = 0;

    void setSettings(McpProtocolSettings *settings);

    [[nodiscard]] bool canStart() const;

    virtual void send(const QJsonObject &obj) = 0;

    [[nodiscard]] QVariant connectionInfo() const;

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj);
    void error(const QString &str);
    void finished();

private:
    std::unique_ptr<McpProtocolSettings> mProtocolSettings;
};
}
