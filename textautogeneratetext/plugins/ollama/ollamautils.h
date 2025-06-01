/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QString>

namespace OllamaUtils
{
[[nodiscard]] TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT QString tagsPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT QString completionPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT QString pullPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT QString versionPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT QString modelInfoPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT QString chatPath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT QString deletePath();
[[nodiscard]] TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT QString createPath();
};
