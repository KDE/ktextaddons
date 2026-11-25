/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textaddonswidgets_export.h"
#include <QString>
namespace TextAddonsWidgets
{
/*!
 * \namespace TextAddonsWidgets::NeedUpdateParseHtmlUtil
 * \inmodule TextAddonsWidgets
 * \inheaderfile TextAddonsWidgets/NeedUpdateParseHtmlUtil
 */
namespace NeedUpdateParseHtmlUtil
{
/*!
 */
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT QString extractDate(const QString &dataHtml);
}
}
