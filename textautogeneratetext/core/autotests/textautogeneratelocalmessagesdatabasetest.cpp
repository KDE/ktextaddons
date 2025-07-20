/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocalmessagesdatabasetest.h"
using namespace Qt::Literals::StringLiterals;

#include "core/localdatabase/textautogeneratelocalmessagesdatabase.h"
#include "core/textautogeneratemessage.h"
#include <QSqlRecord>
#include <QStandardPaths>
#include <QTest>

QTEST_GUILESS_MAIN(TextAutoGenerateLocalMessagesDatabaseTest)

static QByteArray chatId()
{
    return QByteArrayLiteral("myChatId");
}

static QByteArray otherChatId()
{
    return QByteArrayLiteral("otherChatId");
}

enum class Fields {
    MessageId,
    TimeStamp,
    Json,
}; // in the same order as the table

TextAutoGenerateLocalMessagesDatabaseTest::TextAutoGenerateLocalMessagesDatabaseTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateLocalMessagesDatabaseTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);

    // Clean up after previous runs
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase chatsDatabase;
    QFile::remove(chatsDatabase.dbFileName(QString::fromLatin1(chatId())));
    QFile::remove(chatsDatabase.dbFileName(QString::fromLatin1(otherChatId())));
}

void TextAutoGenerateLocalMessagesDatabaseTest::shouldDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase messagesDatabase;
    QCOMPARE(messagesDatabase.schemaDatabaseStr(), u"CREATE TABLE MESSAGES (messageId TEXT PRIMARY KEY NOT NULL, timestamp INTEGER, json TEXT)"_s);
}

void TextAutoGenerateLocalMessagesDatabaseTest::shouldVerifyDbFileName()
{
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase messagesDataBase;
    QCOMPARE(messagesDataBase.dbFileName(QString::fromLatin1(chatId())),
             QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + u"/ai-database/messages/myChatId.sqlite"_s);
}

void TextAutoGenerateLocalMessagesDatabaseTest::shouldStoreMessages()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase logger;

    TextAutoGenerateText::TextAutoGenerateMessage message1;
    message1.setContent(QString::fromUtf8("Message text: €1"));
    message1.setUuid("uu1");
    message1.setDateTime(QDateTime(QDate(2022, 6, 7), QTime(23, 30, 50)).toMSecsSinceEpoch());
    logger.insertOrReplaceMessage(chatId(), message1);

    message1.setContent(QString::fromUtf8("Message text: €2"));
    message1.setDateTime(QDateTime(QDate(2022, 6, 7), QTime(23, 30, 55)).toMSecsSinceEpoch());
    logger.insertOrReplaceMessage(chatId(), message1); // update an existing message 5s later

    TextAutoGenerateText::TextAutoGenerateMessage message2;
    message2.setContent(QString::fromUtf8("Message text: ßĐ"));
    message2.setUuid("uu2");
    message2.setDateTime(QDateTime(QDate(2023, 6, 7), QTime(23, 30, 55)).toMSecsSinceEpoch());
    logger.insertOrReplaceMessage(chatId(), message2);

    TextAutoGenerateText::TextAutoGenerateMessage messageOtherRoom;
    messageOtherRoom.setContent(QString::fromUtf8("Message other chat it"));
    messageOtherRoom.setUuid("uu4");

    logger.insertOrReplaceMessage(otherChatId(), messageOtherRoom);

    // WHEN
    auto tableModel = logger.createMessageModel(QString::fromLatin1(chatId()));

    // THEN
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 2);
    const QSqlRecord record0 = tableModel->record(0);
    QCOMPARE(record0.value(int(Fields::Json)).toByteArray(), TextAutoGenerateText::TextAutoGenerateMessage::serialize(message1, false));
    QCOMPARE(record0.value(int(Fields::TimeStamp)).toULongLong(), message1.dateTime());
    const QSqlRecord record1 = tableModel->record(1);
    QCOMPARE(record1.value(int(Fields::Json)).toByteArray(), TextAutoGenerateText::TextAutoGenerateMessage::serialize(message2, false));
    QCOMPARE(record1.value(int(Fields::TimeStamp)).toULongLong(), message2.dateTime());
}

void TextAutoGenerateLocalMessagesDatabaseTest::shouldDeleteMessages() // this test depends on shouldStoreMessages()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase logger;
    const QString messageId = (u"uu4"_s);

    // WHEN
    logger.deleteMessage(otherChatId(), messageId);

    // THEN
    auto tableModel = logger.createMessageModel(QString::fromLatin1(otherChatId()));
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 0);
}

void TextAutoGenerateLocalMessagesDatabaseTest::shouldReturnNullIfDoesNotExist()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase logger;
    // WHEN
    auto tableModel = logger.createMessageModel(u"does not exist"_s);
    // THEN
    QVERIFY(!tableModel);
}
#include "moc_textautogeneratelocalmessagesdatabasetest.cpp"
