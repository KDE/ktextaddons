/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "textautogeneratetextcore_private_export.h"
#include <QList>
#include <QString>
namespace TextAutoGenerateText
{
namespace TextAutoGenerateMcpToolsUtils
{
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT bool isServerAlwaysAllowed(const QString &serverConfigFileName, const QByteArray &serverIdentifier);
TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT void setServerAlwaysAllowed(const QString &serverConfigFileName, const QByteArray &serverIdentifier, bool allowed);
/*!
 * Servers whose tools are called without confirmation.
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QList<QByteArray> alwaysAllowedServers(const QString &serverConfigFileName);
TEXTAUTOGENERATETEXTCORE_EXPORT void setAlwaysAllowedServers(const QString &serverConfigFileName, const QList<QByteArray> &serverIdentifiers);
/*!
 * Servers \a first and \a second are identical except their allowed tools: connection can be kept.
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT bool sameConnectionSettings(TextAutoGenerateTextMcpProtocolCore::McpServer first,
                                                                          TextAutoGenerateTextMcpProtocolCore::McpServer second);
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QString toolRiskIconName(TextAutoGenerateMcpToolsManager::ToolRisk risk);
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QString toolRiskText(TextAutoGenerateMcpToolsManager::ToolRisk risk);
}
}
