/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QDate>
#include <QString>
namespace TextAddonsWidgets
{
namespace NeedUpdateVersionUtils
{
enum class TEXTADDONSWIDGETS_EXPORT ObsoleteVersion : uint8_t {
    Unknown,
    NotObsoleteYet,
    OlderThan6Months,
    OlderThan12Months,
};

TEXTADDONSWIDGETS_EXPORT void disableCheckVersion();
TEXTADDONSWIDGETS_EXPORT bool checkVersion();
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT QDate compileDate();
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT NeedUpdateVersionUtils::ObsoleteVersion obsoleteVersionStatus(const QString &str, QDate currentDate);
};
}
