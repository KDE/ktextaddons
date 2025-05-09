/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocalmessagesdatabasetest.h"
#include "core/localdatabase/textautogeneratelocalmessagesdatabase.h"
#include "core/textautogeneratemessage.h"
#include <QSqlRecord>
#include <QStandardPaths>
#include <QTest>

QTEST_GUILESS_MAIN(TextAutoGenerateLocalMessagesDatabaseTest)

static QString chatId()
{
    return QStringLiteral("myChatId");
}

static QString otherChatId()
{
    return QStringLiteral("otherChatId");
}

TextAutoGenerateLocalMessagesDatabaseTest::TextAutoGenerateLocalMessagesDatabaseTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateLocalMessagesDatabaseTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);

    // Clean up after previous runs
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase chatsDatabase;
    QFile::remove(chatsDatabase.dbFileName(chatId()));
    QFile::remove(chatsDatabase.dbFileName(otherChatId()));
}

void TextAutoGenerateLocalMessagesDatabaseTest::shouldDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase messagesDatabase;
    QCOMPARE(messagesDatabase.schemaDatabaseStr(), QStringLiteral("CREATE TABLE MESSAGES (messageId TEXT PRIMARY KEY NOT NULL, json TEXT)"));
}

void TextAutoGenerateLocalMessagesDatabaseTest::shouldVerifyDbFileName()
{
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase messagesDataBase;
    QCOMPARE(messagesDataBase.dbFileName(chatId()),
             QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + QStringLiteral("/database/messages/myChatId.sqlite"));
}

void TextAutoGenerateLocalMessagesDatabaseTest::shouldStoreMessages()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase logger;

    TextAutoGenerateText::TextAutoGenerateMessage message1;
    message1.setContent(QString::fromUtf8("Message text: €1"));
    message1.setUuid("uu1");
    logger.addMessage(chatId(), message1);

    message1.setContent(QString::fromUtf8("Message text: €2"));
    logger.addMessage(chatId(), message1); // update an existing message 5s later

    TextAutoGenerateText::TextAutoGenerateMessage message2;
    message2.setContent(QString::fromUtf8("Message text: ßĐ"));
    message2.setUuid("uu2");
    logger.addMessage(chatId(), message2);

    TextAutoGenerateText::TextAutoGenerateMessage messageOtherRoom;
    messageOtherRoom.setContent(QString::fromUtf8("Message other chat it"));
    messageOtherRoom.setUuid("uu4");

    logger.addMessage(otherChatId(), messageOtherRoom);

    // WHEN
    auto tableModel = logger.createMessageModel(chatId());

    // THEN
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 2);
    /*
    const QSqlRecord record0 = tableModel->record(0);
    QCOMPARE(record0.value(int(Fields::Json)).toByteArray(), Message::serialize(message1, false));
    QCOMPARE(record0.value(int(Fields::TimeStamp)).toULongLong(), message1.timeStamp());
    const QSqlRecord record1 = tableModel->record(1);
    QCOMPARE(record1.value(int(Fields::Json)).toByteArray(), Message::serialize(message2, false));
    QCOMPARE(record1.value(int(Fields::TimeStamp)).toULongLong(), message2.timeStamp());
    */
}

void TextAutoGenerateLocalMessagesDatabaseTest::shouldDeleteMessages() // this test depends on shouldStoreMessages()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase logger;
    const QString messageId = (QStringLiteral("uu4"));

    // WHEN
    logger.deleteMessage(otherChatId(), messageId);

    // THEN
    auto tableModel = logger.createMessageModel(otherChatId());
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 0);
}

#include "moc_textautogeneratelocalmessagesdatabasetest.cpp"
