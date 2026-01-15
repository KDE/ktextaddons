/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QString>

namespace OllamaCommonUtils
{
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QString tagsPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QString completionPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QString pullPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QString versionPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QString modelInfoPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QString chatPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QString deletePath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QString createPath();
};
