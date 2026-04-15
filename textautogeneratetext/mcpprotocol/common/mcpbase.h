/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocol_export.h"
#include <QObject>
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpBase : public QObject
{
    Q_OBJECT
public:
    explicit McpBase(QObject *parent = nullptr);
    ~McpBase() override;

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj);
    void error(const QString &str);
    void finished();
};
}
