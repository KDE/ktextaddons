/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogeneratepurgeexpiredchatsjob.h"
#include "core/localdatabase/textautogeneratelocaldatabasemanager.h"
#include "core/models/textautogeneratechatsmodel.h"
#include "core/textautogeneratemanager.h"

using namespace TextAutoGenerateText;
TextAutoGeneratePurgeExpiredChatsJob::TextAutoGeneratePurgeExpiredChatsJob(TextAutoGenerateManager *manager, QObject *parent)
    : QObject{parent}
    , mManager(manager)
{
}

TextAutoGeneratePurgeExpiredChatsJob::~TextAutoGeneratePurgeExpiredChatsJob() = default;

bool TextAutoGeneratePurgeExpiredChatsJob::excludeFavoriteChats() const
{
    return mExcludeFavoriteChats;
}

void TextAutoGeneratePurgeExpiredChatsJob::setExcludeFavoriteChats(bool newExcludeFavoriteChat)
{
    mExcludeFavoriteChats = newExcludeFavoriteChat;
}

void TextAutoGeneratePurgeExpiredChatsJob::start()
{
    if (mManager && mHistoryRetentionDays > 0) {
        const QDateTime limitDateTime = QDateTime::currentDateTime().addDays(-mHistoryRetentionDays);
        const auto chats = mManager->textAutoGenerateChatsModel()->chats();
        QList<QByteArray> expiredChatIds;
        for (const auto &chat : chats) {
            // Ephemeral chats aren't stored, and a chat in progress is still in use.
            if (chat.isEphemeral() || chat.inProgress() || (chat.favorite() && mExcludeFavoriteChats)) {
                continue;
            }
            // Read the date from the database: messages are only loaded when a chat is opened.
            qint64 lastDateTime = mManager->databaseManager()->lastMessageDateTime(chat.identifier());
            if (lastDateTime <= 0) {
                continue;
            }
            // Some persisted data may still contain millisecond timestamps.
            if (lastDateTime > 100000000000LL) {
                lastDateTime /= 1000;
            }
            if (QDateTime::fromSecsSinceEpoch(lastDateTime) < limitDateTime) {
                expiredChatIds.append(chat.identifier());
            }
        }
        for (const auto &chatId : std::as_const(expiredChatIds)) {
            mManager->removeDiscussion(chatId);
        }
    }
    deleteLater();
}

int TextAutoGeneratePurgeExpiredChatsJob::historyRetentionDays() const
{
    return mHistoryRetentionDays;
}

void TextAutoGeneratePurgeExpiredChatsJob::setHistoryRetentionDays(int newHistoryRetentionDays)
{
    mHistoryRetentionDays = newHistoryRetentionDays;
}
#include "moc_textautogeneratepurgeexpiredchatsjob.cpp"
