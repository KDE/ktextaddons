/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateChat>
#include <TextAutoGenerateText/TextAutoGenerateChatSettings>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
#include <TextAutoGenerateText/TextAutoGenerateProject>
#include <TextAutoGenerateText/TextAutoGenerateSearchMessage>
#include <TextAutoGenerateText/TextAutoGenerateTag>
#include <memory>
namespace TextAutoGenerateText
{
class TextAutoGenerateLocalChatsDatabase;
class TextAutoGenerateLocalMessagesDatabase;
class TextAutoGenerateLocalChatPendingTypedInfoDatabase;
class TextAutoGenerateLocalTagsDatabase;
class TextAutoGenerateLocalProjectsDatabase;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateLocalDatabaseManager final
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

    [[nodiscard]] QStringList chatsList() const;

    [[nodiscard]] QList<TextAutoGenerateSearchMessage> searchTextInDatabase(const QList<QByteArray> &listIds, const QString &searchText);

    void updateChatPendingTypedInfo(const QByteArray &chatIdentifier, const TextAutoGenerateChatSettings::PendingTypedInfo &pendingTypedInfo);
    void deleteChatPendingTypedInfo(const QByteArray &chatIdentifier);
    [[nodiscard]] QMap<QByteArray, TextAutoGenerateChatSettings::PendingTypedInfo> loadChatPendingTypedInfo() const;

    [[nodiscard]] TextAutoGenerateLocalMessagesDatabase *messagesDatabase() const;

    [[nodiscard]] TextAutoGenerateLocalChatsDatabase *chatsDatabase() const;

    [[nodiscard]] TextAutoGenerateLocalChatPendingTypedInfoDatabase *chatPendingTypedInfoDatabase() const;

    void deleteTag(const QByteArray &tagId);
    void insertOrUpdateTag(const TextAutoGenerateTag &tag);

    [[nodiscard]] QList<TextAutoGenerateTag> loadTags() const;

    [[nodiscard]] TextAutoGenerateLocalTagsDatabase *tagsDatabase() const;

    void deleteProject(const QByteArray &projectId);
    void insertOrUpdateProject(const TextAutoGenerateProject &project);

    [[nodiscard]] QList<TextAutoGenerateProject> loadProjects() const;

    [[nodiscard]] TextAutoGenerateLocalProjectsDatabase *projectsDatabase() const;

private:
    std::unique_ptr<TextAutoGenerateLocalMessagesDatabase> mMessagesDatabase;
    std::unique_ptr<TextAutoGenerateLocalChatsDatabase> mChatsDatabase;
    std::unique_ptr<TextAutoGenerateLocalChatPendingTypedInfoDatabase> mChatPendingTypedInfoDatabase;
    std::unique_ptr<TextAutoGenerateLocalTagsDatabase> mTagsDatabase;
    std::unique_ptr<TextAutoGenerateLocalProjectsDatabase> mProjectsDatabase;
};
}
