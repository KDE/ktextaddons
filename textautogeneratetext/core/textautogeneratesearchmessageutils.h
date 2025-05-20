/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
namespace TextAutoGenerateText
{
namespace TextAutoGenerateSearchMessageUtils
{
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString generatePreview(const QString &str);
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString generateGoToMessageLink(const QString &chatId, const QString &messageId);
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString generatePreviewText(const QByteArray &chatId, const TextAutoGenerateMessage &msg);
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString scheme();
};
}
