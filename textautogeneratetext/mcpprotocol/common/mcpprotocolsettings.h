/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetextmcpprotocol_export.h"
#include <QObject>
#include <QVariant>
namespace McpProtocol
{
class TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolSettings
{
public:
    McpProtocolSettings();
    ~McpProtocolSettings();

    [[nodiscard]] QVariant serverInfo() const;
    void setServerInfo(const QVariant &newServerInfo);

private:
    QVariant mServerInfo;
};
}
