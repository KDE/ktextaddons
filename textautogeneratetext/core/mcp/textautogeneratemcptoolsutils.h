/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QList>
#include <QString>
namespace TextAutoGenerateText
{
namespace TextAutoGenerateMcpToolsUtils
{
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT bool isServerAlwaysAllowed(const QString &serverConfigFileName, const QByteArray &serverIdentifier);
TEXTAUTOGENERATETEXT_EXPORT void setServerAlwaysAllowed(const QString &serverConfigFileName, const QByteArray &serverIdentifier, bool allowed);
/*!
 * Servers whose tools are called without confirmation.
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QList<QByteArray> alwaysAllowedServers(const QString &serverConfigFileName);
TEXTAUTOGENERATETEXT_EXPORT void setAlwaysAllowedServers(const QString &serverConfigFileName, const QList<QByteArray> &serverIdentifiers);
}
}
