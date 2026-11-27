/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textutils_export.h"
#include <QString>

/*!
 * \namespace TextUtils::TextUtilsColorShell
 * \inmodule TextUtils
 * \brief Helpers to format text printed on a terminal with ANSI escape sequences.
 */
namespace TextUtils
{
namespace TextUtilsColorShell
{
/*!
 * \brief Returns whether ANSI formatting should be used for text written to stdout.
 *
 * Returns true if stdout is a terminal, the NO_COLOR environment variable is
 * not set and TERM is not "dumb". The result is computed once and cached.
 * Note that only stdout is checked: text written to stderr is not handled.
 */
[[nodiscard]] TEXTUTILS_EXPORT bool useAnsiFormatting();
/*!
 * \brief Returns \a text wrapped between the ANSI sequences \a on and \a off.
 *
 * Returns \a text unchanged if useAnsiFormatting() is false.
 */
[[nodiscard]] TEXTUTILS_EXPORT QString ansi(const QString &text, QLatin1StringView on, QLatin1StringView off);

/*!
 * \brief Returns \a text formatted in bold.
 */
[[nodiscard]] TEXTUTILS_EXPORT QString bold(const QString &text);
/*!
 * \brief Returns \a text formatted dim (faint).
 */
[[nodiscard]] TEXTUTILS_EXPORT QString dim(const QString &text);
/*!
 * \brief Returns \a text formatted in cyan.
 */
[[nodiscard]] TEXTUTILS_EXPORT QString cyan(const QString &text);
/*!
 * \brief Returns \a underlined text formatted.
 */
[[nodiscard]] TEXTUTILS_EXPORT QString underline(const QString &text);
}
}
