/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "textautogeneratepurgeexpiredchatsjob.h"

using namespace TextAutoGenerateText;
TextAutoGeneratePurgeExpiredChatsJob::TextAutoGeneratePurgeExpiredChatsJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGeneratePurgeExpiredChatsJob::~TextAutoGeneratePurgeExpiredChatsJob() = default;

bool TextAutoGeneratePurgeExpiredChatsJob::excludeFavoriteChat() const
{
    return mExcludeFavoriteChat;
}

void TextAutoGeneratePurgeExpiredChatsJob::setExcludeFavoriteChat(bool newExcludeFavoriteChat)
{
    mExcludeFavoriteChat = newExcludeFavoriteChat;
}

void TextAutoGeneratePurgeExpiredChatsJob::start()
{
    // TODO
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
