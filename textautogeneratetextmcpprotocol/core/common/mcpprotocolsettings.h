/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QObject>
#include <QVariant>
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolSettings
{
public:
    McpProtocolSettings();
    ~McpProtocolSettings();

    [[nodiscard]] QVariant connectionInfo() const;
    void setConnectionInfo(const QVariant &newConnectionInfo);

private:
    QVariant mConnectionInfo;
};
}
