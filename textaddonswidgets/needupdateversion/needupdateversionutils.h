/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

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
/*!
 * \enum ObsoleteVersion
 * \brief Enumeration of version obsolescence levels
 */
enum class TEXTADDONSWIDGETS_EXPORT ObsoleteVersion : uint8_t {
    Unknown, /*!< Unknown obsolescence status */
    NotObsoleteYet, /*!< Version is not obsolete */
    OlderThan6Months, /*!< Version is older than 6 months */
    OlderThan12Months, /*!< Version is older than 12 months */
};
/*!
 * \brief Disables the check for new version
 */
TEXTADDONSWIDGETS_EXPORT void disableCheckVersion();

/*!
 * \brief Checks if version check is enabled
 * \return True if version check is enabled, false otherwise
 */
TEXTADDONSWIDGETS_EXPORT bool checkVersion();
/*!
 * \brief Returns the compilation date
 * \return The compilation date
 */
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT QDate compileDate();
/*!
 * \brief Determines the obsolescence status of a version
 * \param str The version string
 * \param currentDate The current date to compare against
 * \return The obsolescence status
 */
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT NeedUpdateVersionUtils::ObsoleteVersion obsoleteVersionStatus(const QString &str, QDate currentDate);
};
}
