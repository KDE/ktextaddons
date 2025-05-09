/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateChat>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
#include <memory>
namespace TextAutoGenerateText
{
class TextAutoGenerateLocalChatsDatabase;
class TextAutoGenerateLocalMessagesDatabase;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateLocalDatabaseManager
{
public:
    TextAutoGenerateLocalDatabaseManager();
    ~TextAutoGenerateLocalDatabaseManager();

    [[nodiscard]] QList<TextAutoGenerateMessage> loadMessages(const QString &chatIdentifier) const;

    void deleteMessage(const QString &chatIdentifier, const QString &messageId);
    void insertOrReplaceMessage(const QString &chatIdentifier, const TextAutoGenerateMessage &m);

    void deleteChat(const QString &chatId);
    void insertOrUpdateChat(const TextAutoGenerateChat &chat);

    [[nodiscard]] QList<TextAutoGenerateChat> loadChats() const;

private:
    std::unique_ptr<TextAutoGenerateLocalMessagesDatabase> mMessagesDatabase;
    std::unique_ptr<TextAutoGenerateLocalChatsDatabase> mChatsDatabase;
};
}
