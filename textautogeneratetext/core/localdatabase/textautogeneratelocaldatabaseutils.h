/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QString>
namespace TextAutoGenerateText
{
namespace TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateLocalDatabaseUtils
{
enum class DatabasePath : uint8_t {
    Chats,
    Messages,
};

[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString localDatabasePath();
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString localMessagesDatabasePath();
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString localChatsDatabasePath();
[[nodiscard]] TEXTAUTOGENERATETEXT_TESTS_EXPORT QString databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath pathType);
}
}
