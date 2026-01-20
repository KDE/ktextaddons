/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \brief normalize
 * \param str
 * \return
 */
[[nodiscard]] TEXTUTILS_EXPORT QString normalize(QStringView str);
/*!
 * \brief upperCase
 * \param cursor
 */
TEXTUTILS_EXPORT void upperCase(QTextCursor &cursor);
/*!
 * \brief lowerCase
 * \param cursor
 */
TEXTUTILS_EXPORT void lowerCase(QTextCursor &cursor);
/*!
 * \brief sentenceCase
 * \param cursor
 */
TEXTUTILS_EXPORT void sentenceCase(QTextCursor &cursor);
/*!
 * \brief reverseCase
 * \param cursor
 */
TEXTUTILS_EXPORT void reverseCase(QTextCursor &cursor);
}
}
