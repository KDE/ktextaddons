/*
  SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textaddonswidgets_export.h"
#include <QString>

namespace TextAddonsWidgets
{
namespace VerifyNewVersionUtils
{
/*!
 * \brief Checks if it's possible to verify a new version
 * \return True if verification is possible, false otherwise
 */
[[nodiscard]] TEXTADDONSWIDGETS_EXPORT bool canVerifyNewVersion();
};
}
