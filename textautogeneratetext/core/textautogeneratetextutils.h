/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <KSharedConfig>
#include <QString>
namespace TextAutoGenerateText
{
namespace TextAutoGenerateTextUtils
{
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QString instanceConfigFileName();
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QStringList instancesList(const KSharedConfig::Ptr &config);
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QByteArray generateUUid();

[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QStringList mcpServerList(const KSharedConfig::Ptr &config);
};
}
