/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"

#include <QString>

namespace OllamaCommonModelInfosDelegateUtils
{
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT qreal basicMargin();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT int textMargin();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT qreal rectRoundValue();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT int categoryOffset();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT int categoryMarginText();
[[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_EXPORT int spacingBetweenTextAndCategories();
};
