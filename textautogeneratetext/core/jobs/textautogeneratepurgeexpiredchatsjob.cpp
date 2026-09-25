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
