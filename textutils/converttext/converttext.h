/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textutils_export.h"
#include <QStringView>
#include <QTextCursor>

namespace TextUtils
{
namespace ConvertText
{
[[nodiscard]] TEXTUTILS_EXPORT QString normalize(QStringView str);
TEXTUTILS_EXPORT void upperCase(QTextCursor &cursor);
TEXTUTILS_EXPORT void lowerCase(QTextCursor &cursor);
TEXTUTILS_EXPORT void sentenceCase(QTextCursor &cursor);
TEXTUTILS_EXPORT void reverseCase(QTextCursor &cursor);
}
}
