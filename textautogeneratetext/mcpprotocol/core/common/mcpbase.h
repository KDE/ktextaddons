/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpBase : public QObject
{
    Q_OBJECT
public:
    explicit McpBase(QObject *parent = nullptr);
    ~McpBase() override;

    virtual void connection() = 0;
    virtual void send(const QJsonObject &obj) = 0;

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj);
    void error(const QString &str);
    void finished();
};
}
