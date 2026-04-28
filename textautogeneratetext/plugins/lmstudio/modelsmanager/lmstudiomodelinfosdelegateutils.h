/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QString>

namespace LMStudioModelInfosDelegateUtils
{
[[nodiscard]] qreal basicMargin();
[[nodiscard]] int textMargin();
[[nodiscard]] qreal rectRoundValue();
[[nodiscard]] int categoryOffset();
[[nodiscard]] int categoryMarginText();
[[nodiscard]] int spacingBetweenTextAndCategories();
};
