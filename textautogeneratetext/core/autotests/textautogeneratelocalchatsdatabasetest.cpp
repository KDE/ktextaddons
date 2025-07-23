/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocalchatsdatabasetest.h"

#include "core/localdatabase/textautogeneratelocalchatsdatabase.h"
#include <QSqlRecord>
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateLocalChatsDatabaseTest)

enum class ChatsFields {
    ChatId,
    Json,
}; // in the same order as the table
TextAutoGenerateLocalChatsDatabaseTest::TextAutoGenerateLocalChatsDatabaseTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateLocalChatsDatabaseTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);

    // Clean up after previous runs
    TextAutoGenerateText::TextAutoGenerateLocalChatsDatabase chatsDatabase;
    QFile::remove(chatsDatabase.dbFileName({}));
}

void TextAutoGenerateLocalChatsDatabaseTest::shouldDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateLocalChatsDatabase chatsDatabase;
    QCOMPARE(chatsDatabase.schemaDatabaseStr(), u"CREATE TABLE CHATS (chatId TEXT PRIMARY KEY NOT NULL, json TEXT)"_s);
}

void TextAutoGenerateLocalChatsDatabaseTest::shouldVerifyDbFileName()
{
    TextAutoGenerateText::TextAutoGenerateLocalChatsDatabase chatsDataBase;
    QCOMPARE(chatsDataBase.dbFileName({}), QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + u"/ai-database/chats/chats.sqlite"_s);
    // qDebug() << " chatsDataBase.dbFileName({}) " << chatsDataBase.dbFileName({});
}

void TextAutoGenerateLocalChatsDatabaseTest::shouldStoreChats()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalChatsDatabase chatsDataBase;

    TextAutoGenerateText::TextAutoGenerateChat chat1;
    chat1.setIdentifier("chat1");
    chat1.setTitle(u"title-chat1"_s);
    chat1.setDateTime(QDateTime(QDate(2022, 6, 7), QTime(23, 30, 50)).toMSecsSinceEpoch());
    chatsDataBase.insertOrUpdateChat(chat1);

    TextAutoGenerateText::TextAutoGenerateChat chat2;
    chat2.setIdentifier("chat2");
    chat2.setTitle(u"title-chat2"_s);
    chat2.setDateTime(QDateTime(QDate(2023, 6, 7), QTime(23, 30, 50)).toMSecsSinceEpoch());
    chatsDataBase.insertOrUpdateChat(chat2);

    // WHEN
    auto tableModel = chatsDataBase.createChatsModel();

    // THEN
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 2);
    const QSqlRecord record0 = tableModel->record(0);
    QCOMPARE(record0.value(int(ChatsFields::Json)).toByteArray(), TextAutoGenerateText::TextAutoGenerateChat::serialize(chat1, false));

    const QSqlRecord record1 = tableModel->record(1);
    QCOMPARE(record1.value(int(ChatsFields::Json)).toByteArray(), TextAutoGenerateText::TextAutoGenerateChat::serialize(chat2, false));
}

void TextAutoGenerateLocalChatsDatabaseTest::shouldDeleteChats() // this test depends on shouldStoreChats()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalChatsDatabase logger;

    // WHEN
    logger.deleteChat("chat1");

    // THEN
    auto tableModel = logger.createChatsModel();
    QVERIFY(tableModel);
    // FIXME QCOMPARE(tableModel->rowCount(), 1);
}
#include "moc_textautogeneratelocalchatsdatabasetest.cpp"
