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

    [[nodiscard]] QList<TextAutoGenerateMessage> loadMessages(const QByteArray &chatIdentifier) const;

    void deleteMessage(const QByteArray &chatIdentifier, const QString &messageId);
    void insertOrReplaceMessage(const QByteArray &chatIdentifier, const TextAutoGenerateMessage &m);

    void deleteChat(const QByteArray &chatId);
    void insertOrUpdateChat(const TextAutoGenerateChat &chat);

    [[nodiscard]] QList<TextAutoGenerateChat> loadChats() const;

    void searchTextInDatabase(const QString &searchText);

private:
    std::unique_ptr<TextAutoGenerateLocalMessagesDatabase> mMessagesDatabase;
    std::unique_ptr<TextAutoGenerateLocalChatsDatabase> mChatsDatabase;
};
}
