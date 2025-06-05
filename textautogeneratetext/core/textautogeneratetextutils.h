/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QString>
namespace TextAutoGenerateText
{
namespace TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextUtils
{
[[nodiscard]] QString findExecutable(const QString &exec);
};
}
