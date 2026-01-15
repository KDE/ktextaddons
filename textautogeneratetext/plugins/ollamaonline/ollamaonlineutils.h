/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamaonline_private_export.h"
#include <QString>

namespace OllamaOnlineUtils
{
[[nodiscard]] TEXTAUTOGENERATEOLLAMAONLINE_TESTS_EXPORT QString tagsPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMAONLINE_TESTS_EXPORT QString completionPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMAONLINE_TESTS_EXPORT QString pullPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMAONLINE_TESTS_EXPORT QString versionPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMAONLINE_TESTS_EXPORT QString modelInfoPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMAONLINE_TESTS_EXPORT QString chatPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMAONLINE_TESTS_EXPORT QString deletePath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMAONLINE_TESTS_EXPORT QString createPath();
};
