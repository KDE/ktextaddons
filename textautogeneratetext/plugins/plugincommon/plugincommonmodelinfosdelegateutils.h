/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogenerateplugincommon_export.h"

#include <QtTypes>

namespace PluginCommonModelInfosDelegateUtils
{
[[nodiscard]] TEXTAUTOGENERATEPLUGINCOMMON_EXPORT qreal basicMargin();
[[nodiscard]] TEXTAUTOGENERATEPLUGINCOMMON_EXPORT int textMargin();
[[nodiscard]] TEXTAUTOGENERATEPLUGINCOMMON_EXPORT qreal rectRoundValue();
[[nodiscard]] TEXTAUTOGENERATEPLUGINCOMMON_EXPORT int categoryOffset();
[[nodiscard]] TEXTAUTOGENERATEPLUGINCOMMON_EXPORT int categoryMarginText();
[[nodiscard]] TEXTAUTOGENERATEPLUGINCOMMON_EXPORT int spacingBetweenTextAndCategories();
};
