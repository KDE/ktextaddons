/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocaldatabasemanager.h"

#include "textautogeneratelocalchatsdatabase.h"
#include "textautogeneratelocalmessagesdatabase.h"

using namespace TextAutoGenerateText;
TextAutoGenerateLocalDatabaseManager::TextAutoGenerateLocalDatabaseManager()
    : mMessagesDatabase(std::make_unique<TextAutoGenerateLocalMessagesDatabase>())
    , mChatsDatabase(std::make_unique<TextAutoGenerateLocalChatsDatabase>())
{
}

TextAutoGenerateLocalDatabaseManager::~TextAutoGenerateLocalDatabaseManager() = default;

QList<TextAutoGenerateMessage> TextAutoGenerateLocalDatabaseManager::loadMessages(const QString &chatIdentifier) const
{
    return mMessagesDatabase->loadMessages(chatIdentifier);
}

QList<TextAutoGenerateChat> TextAutoGenerateLocalDatabaseManager::loadChats() const
{
    return mChatsDatabase->loadChats();
}

void TextAutoGenerateLocalDatabaseManager::deleteMessage(const QByteArray &chatIdentifier, const QString &messageId)
{
    mMessagesDatabase->deleteMessage(chatIdentifier, messageId);
}

void TextAutoGenerateLocalDatabaseManager::insertOrReplaceMessage(const QByteArray &chatIdentifier, const TextAutoGenerateMessage &m)
{
    mMessagesDatabase->insertOrReplaceMessage(chatIdentifier, m);
}

void TextAutoGenerateLocalDatabaseManager::deleteChat(const QString &chatId)
{
    mChatsDatabase->deleteChat(chatId);
    // TODO delete messageId file
}

void TextAutoGenerateLocalDatabaseManager::insertOrUpdateChat(const TextAutoGenerateChat &chat)
{
    mChatsDatabase->insertOrUpdateChat(chat);
}
