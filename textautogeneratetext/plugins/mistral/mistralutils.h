/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratemistral_private_export.h"
#include <QString>

namespace MistralUtils
{
[[nodiscard]] TEXTAUTOGENERATEMISTRAL_TESTS_EXPORT QString modelsPath();
[[nodiscard]] TEXTAUTOGENERATEMISTRAL_TESTS_EXPORT QString chatPath();
[[nodiscard]] TEXTAUTOGENERATEMISTRAL_TESTS_EXPORT QString mistralAiUrl();
[[nodiscard]] TEXTAUTOGENERATEMISTRAL_EXPORT QString mistralGroupName();
[[nodiscard]] TEXTAUTOGENERATEMISTRAL_EXPORT QString apiGroupName();
};
