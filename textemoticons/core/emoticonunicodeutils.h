/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textemoticonscore_export.h"
#include <QString>
namespace TextEmoticonsCore
{
namespace EmoticonUnicodeUtils
{
[[nodiscard]] TEXTEMOTICONSCORE_EXPORT QString emojiFontName();
[[nodiscard]] TEXTEMOTICONSCORE_EXPORT QString recentIdentifier();
[[nodiscard]] TEXTEMOTICONSCORE_EXPORT QString customIdentifier();
[[nodiscard]] TEXTEMOTICONSCORE_EXPORT QString recentName();
[[nodiscard]] TEXTEMOTICONSCORE_EXPORT QString customName();
[[nodiscard]] TEXTEMOTICONSCORE_EXPORT QString escapeUnicodeEmoji(const QString &pString);
}
}
