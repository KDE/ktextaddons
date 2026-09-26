/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratepurgeexpiredchatsjobtest.h"
#include "core/jobs/textautogeneratepurgeexpiredchatsjob.h"
#include "core/localdatabase/textautogeneratelocaldatabasemanager.h"
#include "core/models/textautogeneratechatsmodel.h"
#include "core/textautogeneratemanager.h"
#include <QStandardPaths>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGeneratePurgeExpiredChatsJobTest)

using namespace Qt::Literals::StringLiterals;

TextAutoGeneratePurgeExpiredChatsJobTest::TextAutoGeneratePurgeExpiredChatsJobTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGeneratePurgeExpiredChatsJobTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGeneratePurgeExpiredChatsJob job(nullptr);
    QCOMPARE(job.historyRetentionDays(), 0);
    QVERIFY(job.excludeFavoriteChats());
}

void TextAutoGeneratePurgeExpiredChatsJobTest::shouldPurgeExpiredChats_data()
{
    QTest::addColumn<int>("retentionDays");
    QTest::addColumn<bool>("excludeFavorite");
    QTest::addColumn<int>("messageAgeInDays"); // -1 means no message
    QTest::addColumn<bool>("useMilliseconds");
    QTest::addColumn<bool>("favorite");
    QTest::addColumn<bool>("inProgress");
    QTest::addColumn<bool>("purged");

    QTest::newRow("retention-disabled") << 0 << true << 100 << false << false << false << false;
    QTest::newRow("recent") << 30 << true << 2 << false << false << false << false;
    QTest::newRow("expired") << 30 << true << 40 << false << false << false << true;
    QTest::newRow("expired-milliseconds") << 30 << true << 40 << true << false << false << true;
    QTest::newRow("no-message") << 30 << true << -1 << false << false << false << false;
    QTest::newRow("expired-favorite-excluded") << 30 << true << 40 << false << true << false << false;
    QTest::newRow("expired-favorite-not-excluded") << 30 << false << 40 << false << true << false << true;
    QTest::newRow("expired-in-progress") << 30 << true << 40 << false << false << true << false;
}

void TextAutoGeneratePurgeExpiredChatsJobTest::shouldPurgeExpiredChats()
{
    QFETCH(int, retentionDays);
    QFETCH(bool, excludeFavorite);
    QFETCH(int, messageAgeInDays);
    QFETCH(bool, useMilliseconds);
    QFETCH(bool, favorite);
    QFETCH(bool, inProgress);
    QFETCH(bool, purged);

    TextAutoGenerateText::TextAutoGenerateManager manager;
    const QByteArray chatId = "purgeChat-"_ba + QTest::currentDataTag();
    // Clean up after previous runs
    manager.databaseManager()->deleteChat(chatId);

    TextAutoGenerateText::TextAutoGenerateChat chat;
    chat.setIdentifier(chatId);
    chat.setFavorite(favorite);
    chat.setInProgress(inProgress);
    manager.textAutoGenerateChatsModel()->addChat(chat);

    if (messageAgeInDays >= 0) {
        const QDateTime messageDateTime = QDateTime::currentDateTime().addDays(-messageAgeInDays);
        TextAutoGenerateText::TextAutoGenerateMessage message;
        message.setContent(u"message"_s);
        message.setUuid("purge-message");
        message.setDateTime(useMilliseconds ? messageDateTime.toMSecsSinceEpoch() : messageDateTime.toSecsSinceEpoch());
        message.generateHtml();
        manager.databaseManager()->insertOrReplaceMessage(chatId, message);
    }

    auto job = new TextAutoGenerateText::TextAutoGeneratePurgeExpiredChatsJob(&manager);
    job->setHistoryRetentionDays(retentionDays);
    job->setExcludeFavoriteChats(excludeFavorite);
    job->start();

    const auto chats = manager.textAutoGenerateChatsModel()->chats();
    const bool found = std::any_of(chats.cbegin(), chats.cend(), [&chatId](const TextAutoGenerateText::TextAutoGenerateChat &c) {
        return c.identifier() == chatId;
    });
    QCOMPARE(found, !purged);
    QCOMPARE(manager.databaseManager()->lastMessageDateTime(chatId) == -1, purged || messageAgeInDays < 0);

    manager.databaseManager()->deleteChat(chatId);
}

#include "moc_textautogeneratepurgeexpiredchatsjobtest.cpp"
