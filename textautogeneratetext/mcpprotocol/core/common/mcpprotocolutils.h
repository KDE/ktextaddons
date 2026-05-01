/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <KSharedConfig>
#include <QString>
namespace TextAutoGenerateTextMcpProtocolCore
{
namespace McpProtocolUtils
{
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QString serverConfigFileName();
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QByteArray generateUUid();

[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QStringList mcpServerList(const KSharedConfig::Ptr &config);
};
}
