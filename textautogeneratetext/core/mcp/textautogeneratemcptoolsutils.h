/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "textautogeneratetext_private_export.h"
#include <QList>
#include <QString>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpServer;
}
namespace TextAutoGenerateText
{
namespace TextAutoGenerateMcpToolsUtils
{
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT bool isServerAlwaysAllowed(const QString &serverConfigFileName, const QByteArray &serverIdentifier);
TEXTAUTOGENERATETEXT_TESTS_EXPORT void setServerAlwaysAllowed(const QString &serverConfigFileName, const QByteArray &serverIdentifier, bool allowed);
/*!
 * Servers whose tools are called without confirmation.
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QList<QByteArray> alwaysAllowedServers(const QString &serverConfigFileName);
TEXTAUTOGENERATETEXT_TESTS_EXPORT void setAlwaysAllowedServers(const QString &serverConfigFileName, const QList<QByteArray> &serverIdentifiers);
/*!
 * Servers \a first and \a second are identical except their allowed tools: connection can be kept.
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT bool sameConnectionSettings(TextAutoGenerateTextMcpProtocolCore::McpServer first,
                                                                            TextAutoGenerateTextMcpProtocolCore::McpServer second);
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString toolRiskIconName(TextAutoGenerateMcpToolsManager::ToolRisk risk);
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString toolRiskText(TextAutoGenerateMcpToolsManager::ToolRisk risk);
}
}
