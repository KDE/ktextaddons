/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include "textautogeneratetext_private_export.h"
#include <QObject>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGeneratePurgeExpiredChatsJob : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGeneratePurgeExpiredChatsJob(TextAutoGenerateManager *manager, QObject *parent = nullptr);
    ~TextAutoGeneratePurgeExpiredChatsJob() override;

    [[nodiscard]] bool excludeFavoriteChats() const;
    void setExcludeFavoriteChats(bool newExcludeFavoriteChat);

    void start();

    [[nodiscard]] int historyRetentionDays() const;
    void setHistoryRetentionDays(int newHistoryRetentionDays);

private:
    int mHistoryRetentionDays = 0;
    bool mExcludeFavoriteChats = true;
    TextAutoGenerateManager *const mManager;
};
}
