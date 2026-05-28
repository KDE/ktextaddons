/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textaddonswidgets_export.h"
#include <QString>
namespace TextAddonsWidgets::WhatsNewNgUtils
{
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT QString createMD5(const QString &str);
};
