/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QString>
namespace TextAutoGenerateText
{
namespace TextAutoGenerateSearchMessageUtils
{
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString generatePreview(const QString &str);
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString createGoToMessage(const QString &chatId, const QString &messageId);
};
}
