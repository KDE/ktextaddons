/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextcore_private_export.h"
#include <QString>
namespace TextAutoGenerateText
{
namespace TextAutoGenerateLocalDatabaseUtils
{
enum class DatabasePath : uint8_t {
    Chats,
    Messages,
    ChatPendingTypedInfo,
    Tags,
    Projects,
};

[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString localDatabasePath();
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString localMessagesDatabasePath();
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString localChatsDatabasePath();
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString localChatPendingTypedInfoDatabasePath();
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString localTagsDatabasePath();
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString localProjectsDatabasePath();
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString databasePath(TextAutoGenerateLocalDatabaseUtils::DatabasePath pathType);

[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString insertReplaceChat();
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString deleteChat();

[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString insertReplaceMessage();
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString deleteMessage();

[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString insertReplaceChatPendingTypedInfo();
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString deleteChatPendingTypedInfo();

[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString insertReplaceTag();
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString deleteTag();

[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString insertReplaceProject();
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_TESTS_EXPORT QString deleteProject();
}
}
