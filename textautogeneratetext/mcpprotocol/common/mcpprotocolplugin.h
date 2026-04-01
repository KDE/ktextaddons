/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocol_export.h"
#include <QObject>
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolPlugin : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolPlugin(QObject *parent = nullptr);
    ~McpProtocolPlugin() override;
};
}
