/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QString>
namespace TextAddonsWidgets::ExecutableUtils
{
/*!
 * \brief findExecutable
 * \param exec
 * \return
 */
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT QString findExecutable(const QString &exec);
/*!
 * \brief findExecutable
 * \param exec
 * \return
 */
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT bool executableFound(const QString &exec);
};
