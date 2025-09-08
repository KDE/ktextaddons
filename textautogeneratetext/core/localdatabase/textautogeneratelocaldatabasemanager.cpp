/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocaldatabasemanager.h"
#include "textautogeneratetextcore_database_debug.h"

#include "textautogeneratelocalchatsdatabase.h"
#include "textautogeneratelocalmessagesdatabase.h"

using namespace TextAutoGenerateText;
TextAutoGenerateLocalDatabaseManager::TextAutoGenerateLocalDatabaseManager()
    : mMessagesDatabase(std::make_unique<TextAutoGenerateLocalMessagesDatabase>())
    , mChatsDatabase(std::make_unique<TextAutoGenerateLocalChatsDatabase>())
{
}

TextAutoGenerateLocalDatabaseManager::~TextAutoGenerateLocalDatabaseManager() = default;

QList<TextAutoGenerateMessage> TextAutoGenerateLocalDatabaseManager::loadMessages(const QByteArray &chatIdentifier) const
{
    return mMessagesDatabase->loadMessages(QString::fromLatin1(chatIdentifier));
}

QList<TextAutoGenerateChat> TextAutoGenerateLocalDatabaseManager::loadChats() const
{
    return mChatsDatabase->loadChats();
}

QStringList TextAutoGenerateLocalDatabaseManager::chatsList() const
{
    QStringList lst;
    const QList<TextAutoGenerateChat> chats = loadChats();
    for (const auto &chat : chats) {
        lst.append(chat.title());
    }
    return lst;
}

QList<TextAutoGenerateSearchMessage> TextAutoGenerateLocalDatabaseManager::searchTextInDatabase(const QList<QByteArray> &listIds, const QString &searchText)
{
    QList<TextAutoGenerateSearchMessage> lst;
    for (const QByteArray &id : listIds) {
        lst.append(mMessagesDatabase->searchMessages(QString::fromLatin1(id), searchText));
    }
    return lst;
}

void TextAutoGenerateLocalDatabaseManager::deleteMessage(const QByteArray &chatIdentifier, const QString &messageId)
{
    mMessagesDatabase->deleteMessage(chatIdentifier, messageId);
}

void TextAutoGenerateLocalDatabaseManager::insertOrReplaceMessage(const QByteArray &chatIdentifier, const TextAutoGenerateMessage &m)
{
    mMessagesDatabase->insertOrReplaceMessage(chatIdentifier, m);
}

void TextAutoGenerateLocalDatabaseManager::deleteChat(const QByteArray &chatId)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Delete Chat" << chatId;
    mChatsDatabase->deleteChat(chatId);
    mMessagesDatabase->deleteDatabase(chatId);
}

void TextAutoGenerateLocalDatabaseManager::insertOrUpdateChat(const TextAutoGenerateChat &chat)
{
    mChatsDatabase->insertOrUpdateChat(chat);
}
