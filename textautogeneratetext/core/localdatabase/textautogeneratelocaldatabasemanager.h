/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "core/textautogeneratechatsettings.h"
#include "textautogeneratetext_private_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateChat>
#include <TextAutoGenerateText/TextAutoGenerateMessage>
#include <TextAutoGenerateText/TextAutoGenerateSearchMessage>
#include <memory>
namespace TextAutoGenerateText
{
class TextAutoGenerateLocalChatsDatabase;
class TextAutoGenerateLocalMessagesDatabase;
class TextAutoGenerateLocalRoomPendingTypedInfoDatabase;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateLocalDatabaseManager final
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

    void updateRoomPendingTypedInfo(const QByteArray &chatIdentifier, const TextAutoGenerateChatSettings::PendingTypedInfo &pendingTypedInfo);
    void deleteRoomPendingTypedInfo(const QByteArray &chatIdentifier);
    [[nodiscard]] QMap<QByteArray, TextAutoGenerateChatSettings::PendingTypedInfo> loadRoomPendingTypedInfo() const;

private:
    std::unique_ptr<TextAutoGenerateLocalMessagesDatabase> mMessagesDatabase;
    std::unique_ptr<TextAutoGenerateLocalChatsDatabase> mChatsDatabase;
    std::unique_ptr<TextAutoGenerateLocalRoomPendingTypedInfoDatabase> mRoomPendingTypedInfoDatabase;
};
}
