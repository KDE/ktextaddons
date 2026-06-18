/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocalmessagesdatabasetest.h"

#include "core/localdatabase/textautogeneratelocalmessagesdatabase.h"
#include "core/textautogeneratemessage.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QTest>

QTEST_GUILESS_MAIN(TextAutoGenerateLocalMessagesDatabaseTest)

using namespace Qt::Literals::StringLiterals;
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
    qDebug() << "messagesDataBase.dbFileName(QString::fromLatin1(chatId())) " << messagesDataBase.dbFileName(QString::fromLatin1(chatId()));
}

void TextAutoGenerateLocalMessagesDatabaseTest::shouldPersistFirstInsertForFreshConnection()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase logger;
    const QString firstWriteChatId = u"firstWriteChatId"_s;
    const QString dbFileName = logger.dbFileName(firstWriteChatId);
    QFile::remove(dbFileName);
    QFile::remove(dbFileName + u"-wal"_s);
    QFile::remove(dbFileName + u"-shm"_s);

    TextAutoGenerateText::TextAutoGenerateMessage message;
    message.setContent(u"first write message"_s);
    message.setUuid("first-write-id");
    message.setDateTime(QDateTime(QDate(2026, 1, 1), QTime(12, 0, 0)).toMSecsSinceEpoch());
    message.generateHtml();

    // WHEN
    logger.insertOrReplaceMessage(firstWriteChatId.toLatin1(), message);

    const QString sourceConnectionName = u"messages-"_s + firstWriteChatId;
    if (QSqlDatabase::contains(sourceConnectionName)) {
        {
            QSqlDatabase sourceDb = QSqlDatabase::database(sourceConnectionName);
            sourceDb.close();
        }
        QSqlDatabase::removeDatabase(sourceConnectionName);
    }

    const QString freshConnectionName = u"messages-fresh-check"_s;
    {
        QSqlDatabase freshDb = QSqlDatabase::addDatabase(u"QSQLITE"_s, freshConnectionName);
        freshDb.setDatabaseName(dbFileName);
        QVERIFY2(freshDb.open(), qPrintable(freshDb.lastError().text()));

        QSqlQuery countQuery(freshDb);
        QVERIFY2(countQuery.prepare(u"SELECT COUNT(*) FROM MESSAGES WHERE messageId = ?"_s), qPrintable(countQuery.lastError().text()));
        countQuery.addBindValue(u"first-write-id"_s);
        QVERIFY2(countQuery.exec(), qPrintable(countQuery.lastError().text()));
        QVERIFY(countQuery.next());
        QCOMPARE(countQuery.value(0).toInt(), 1);
        freshDb.close();
    }
    QSqlDatabase::removeDatabase(freshConnectionName);
}

void TextAutoGenerateLocalMessagesDatabaseTest::shouldStoreMessages()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalMessagesDatabase logger;

    TextAutoGenerateText::TextAutoGenerateMessage message1;
    message1.setContent(QString::fromUtf8("Message text: €1"));
    message1.setUuid("uu1");
    message1.setDateTime(QDateTime(QDate(2022, 6, 7), QTime(23, 30, 50)).toMSecsSinceEpoch());
    message1.generateHtml();
    logger.insertOrReplaceMessage(chatId(), message1);

    message1.setContent(QString::fromUtf8("Message text: €2"));
    message1.setDateTime(QDateTime(QDate(2022, 6, 7), QTime(23, 30, 55)).toMSecsSinceEpoch());
    message1.generateHtml();
    logger.insertOrReplaceMessage(chatId(), message1); // update an existing message 5s later

    TextAutoGenerateText::TextAutoGenerateMessage message2;
    message2.setContent(QString::fromUtf8("Message text: ßĐ"));
    message2.setUuid("uu2");
    message2.setDateTime(QDateTime(QDate(2023, 6, 7), QTime(23, 30, 55)).toMSecsSinceEpoch());
    message2.generateHtml();
    logger.insertOrReplaceMessage(chatId(), message2);

    TextAutoGenerateText::TextAutoGenerateMessage messageOtherRoom;
    messageOtherRoom.setContent(QString::fromUtf8("Message other chat it"));
    messageOtherRoom.setUuid("uu4");
    messageOtherRoom.generateHtml();

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
