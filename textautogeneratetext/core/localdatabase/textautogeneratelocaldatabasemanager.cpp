/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocaldatabasemanager.h"
#include "textautogeneratetextcore_database_debug.h"

#include "textautogeneratelocalchatpendingtypedinfodatabase.h"
#include "textautogeneratelocalchatsdatabase.h"
#include "textautogeneratelocalmessagesdatabase.h"
#include "textautogeneratelocalprojectsdatabase.h"
#include "textautogeneratelocaltagsdatabase.h"

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateLocalDatabaseManager::TextAutoGenerateLocalDatabaseManager()
    : mMessagesDatabase(std::make_unique<TextAutoGenerateLocalMessagesDatabase>())
    , mChatsDatabase(std::make_unique<TextAutoGenerateLocalChatsDatabase>())
    , mChatPendingTypedInfoDatabase(std::make_unique<TextAutoGenerateLocalChatPendingTypedInfoDatabase>())
    , mTagsDatabase(std::make_unique<TextAutoGenerateLocalTagsDatabase>())
    , mProjectsDatabase(std::make_unique<TextAutoGenerateLocalProjectsDatabase>())
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
    lst.reserve(chats.count());
    for (const auto &chat : chats) {
        lst.append(u"%1 (%2)"_s.arg(chat.title(), QString::fromLatin1(chat.identifier())));
    }
    return lst;
}

QList<TextAutoGenerateSearchMessage> TextAutoGenerateLocalDatabaseManager::searchTextInDatabase(const QList<QByteArray> &listIds, const QString &searchText)
{
    QList<TextAutoGenerateSearchMessage> lst;
    lst.reserve(listIds.count());
    for (const QByteArray &id : listIds) {
        lst.append(mMessagesDatabase->searchMessages(QString::fromLatin1(id), searchText));
    }
    return lst;
}

void TextAutoGenerateLocalDatabaseManager::deleteMessage(const QByteArray &chatIdentifier, const QString &messageId)
{
    if (mEphemeralChatIds.contains(chatIdentifier)) {
        return;
    }
    mMessagesDatabase->deleteMessage(chatIdentifier, messageId);
}

void TextAutoGenerateLocalDatabaseManager::insertOrReplaceMessage(const QByteArray &chatIdentifier, const TextAutoGenerateMessage &m)
{
    if (mEphemeralChatIds.contains(chatIdentifier)) {
        return;
    }
    mMessagesDatabase->insertOrReplaceMessage(chatIdentifier, m);
}

void TextAutoGenerateLocalDatabaseManager::deleteChat(const QByteArray &chatId)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Delete Chat" << chatId;
    if (mEphemeralChatIds.contains(chatId)) {
        removeEphemeralChat(chatId);
    } else {
        mChatsDatabase->deleteChat(chatId);
        mMessagesDatabase->deleteDatabase(chatId);
        mChatPendingTypedInfoDatabase->deleteChatPendingTypedInfo(chatId);
    }
}

void TextAutoGenerateLocalDatabaseManager::insertOrUpdateChat(const TextAutoGenerateChat &chat)
{
    if (mEphemeralChatIds.contains(chat.identifier())) {
        return;
    }
    mChatsDatabase->insertOrUpdateChat(chat);
}

void TextAutoGenerateLocalDatabaseManager::updateChatPendingTypedInfo(const QByteArray &chatIdentifier,
                                                                      const TextAutoGenerateChatSettings::PendingTypedInfo &pendingTypedInfo)
{
    if (mEphemeralChatIds.contains(chatIdentifier)) {
        return;
    }
    mChatPendingTypedInfoDatabase->updateChatPendingTypedInfo(chatIdentifier, pendingTypedInfo);
}

void TextAutoGenerateLocalDatabaseManager::deleteChatPendingTypedInfo(const QByteArray &chatIdentifier)
{
    if (mEphemeralChatIds.contains(chatIdentifier)) {
        return;
    }
    mChatPendingTypedInfoDatabase->deleteChatPendingTypedInfo(chatIdentifier);
}

QMap<QByteArray /*RoomId*/, TextAutoGenerateChatSettings::PendingTypedInfo> TextAutoGenerateLocalDatabaseManager::loadChatPendingTypedInfo() const
{
    return mChatPendingTypedInfoDatabase->loadChatPendingTypedInfo();
}

TextAutoGenerateLocalMessagesDatabase *TextAutoGenerateLocalDatabaseManager::messagesDatabase() const
{
    return mMessagesDatabase.get();
}

TextAutoGenerateLocalChatsDatabase *TextAutoGenerateLocalDatabaseManager::chatsDatabase() const
{
    return mChatsDatabase.get();
}

TextAutoGenerateLocalChatPendingTypedInfoDatabase *TextAutoGenerateLocalDatabaseManager::chatPendingTypedInfoDatabase() const
{
    return mChatPendingTypedInfoDatabase.get();
}

TextAutoGenerateLocalTagsDatabase *TextAutoGenerateLocalDatabaseManager::tagsDatabase() const
{
    return mTagsDatabase.get();
}

void TextAutoGenerateLocalDatabaseManager::deleteTag(const QByteArray &tagId)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Delete Tag" << tagId;
    mTagsDatabase->deleteTag(tagId);
}

void TextAutoGenerateLocalDatabaseManager::insertOrUpdateTag(const TextAutoGenerateTag &tag)
{
    mTagsDatabase->insertOrUpdateTag(tag);
}

QList<TextAutoGenerateTag> TextAutoGenerateLocalDatabaseManager::loadTags() const
{
    return mTagsDatabase->loadTags();
}

TextAutoGenerateLocalProjectsDatabase *TextAutoGenerateLocalDatabaseManager::projectsDatabase() const
{
    return mProjectsDatabase.get();
}

void TextAutoGenerateLocalDatabaseManager::addEphemeralChat(const QByteArray &chatId)
{
    mEphemeralChatIds.insert(chatId);
}

void TextAutoGenerateLocalDatabaseManager::removeEphemeralChat(const QByteArray &chatId)
{
    mEphemeralChatIds.remove(chatId);
}

QSet<QByteArray> TextAutoGenerateLocalDatabaseManager::ephemeralChatIds() const
{
    return mEphemeralChatIds;
}

void TextAutoGenerateLocalDatabaseManager::setEphemeralChatIds(const QSet<QByteArray> &newEphemeralChatIds)
{
    mEphemeralChatIds = newEphemeralChatIds;
}

void TextAutoGenerateLocalDatabaseManager::deleteProject(const QByteArray &projectId)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_DATABASE_LOG) << "Delete Project" << projectId;
    mProjectsDatabase->deleteProject(projectId);
}

void TextAutoGenerateLocalDatabaseManager::insertOrUpdateProject(const TextAutoGenerateProject &project)
{
    mProjectsDatabase->insertOrUpdateProject(project);
}

QList<TextAutoGenerateProject> TextAutoGenerateLocalDatabaseManager::loadProjects() const
{
    return mProjectsDatabase->loadProjects();
}
