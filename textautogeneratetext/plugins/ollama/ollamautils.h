/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QString>

namespace OllamaUtils
{
[[nodiscard]] QString tagsPath();
[[nodiscard]] QString completionPath();
[[nodiscard]] QString pullPath();
[[nodiscard]] QString versionPath();
[[nodiscard]] QString modelInfoPath();
[[nodiscard]] QString chatPath();
};
