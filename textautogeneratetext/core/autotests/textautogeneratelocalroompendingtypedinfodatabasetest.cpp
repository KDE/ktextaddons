/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratelocalroompendingtypedinfodatabasetest.h"
#include "core/localdatabase/textautogeneratelocalroompendingtypedinfodatabase.h"
#include <QJsonObject>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QStandardPaths>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest)
using namespace Qt::Literals::StringLiterals;
static QString accountName()
{
    return u"myAccount"_s;
}

static QString otherAccountName()
{
    return u"myOtherAccount"_s;
}

enum class RoomPendingTypedFields {
    RoomId,
    Json,
}; // in the same order as the table

TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest::TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);

    // Clean up after previous runs
    TextAutoGenerateText::TextAutoGenerateLocalRoomPendingTypedInfoDatabase roomPendingTypedInfoDataBase;
    QFile::remove(roomPendingTypedInfoDataBase.dbFileName(accountName()));
    QFile::remove(roomPendingTypedInfoDataBase.dbFileName(otherAccountName()));
}

void TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest::shouldDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateLocalRoomPendingTypedInfoDatabase roomPendingTypedInfoDataBase;
    QCOMPARE(roomPendingTypedInfoDataBase.schemaDatabaseStr(), u"CREATE TABLE ROOMPENDINGTYPED (roomId TEXT PRIMARY KEY NOT NULL, json TEXT)"_s);
}

void TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest::shouldVerifyDbFileName()
{
    TextAutoGenerateText::TextAutoGenerateLocalRoomPendingTypedInfoDatabase roomPendingTypedInfoDataBase;
    QCOMPARE(roomPendingTypedInfoDataBase.dbFileName(accountName()),
             QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + u"/ai-database/roompendingtypedinfo/myAccount.sqlite"_s);
}

void TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest::shouldStoreRoomPendingTypedInfo()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalRoomPendingTypedInfoDatabase logger;

    QByteArray roomId = "foo1"_ba;
    TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info1;
    info1.text = u"foo"_s;
    logger.updateRoomPendingTypedInfo(otherAccountName(), roomId, info1);

    // Update PendingTypedInfo
    info1.scrollbarPosition = 5;
    logger.updateRoomPendingTypedInfo(otherAccountName(), roomId, info1);

    QByteArray roomId2 = "foo2"_ba;
    TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info2;
    info2.scrollbarPosition = 5;
    logger.updateRoomPendingTypedInfo(otherAccountName(), roomId2, info2);

    QByteArray roomId3 = "foo3"_ba;
    TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info3;
    info3.scrollbarPosition = 5;
    logger.updateRoomPendingTypedInfo(otherAccountName(), roomId3, info2);

    // WHEN
    auto tableModel = logger.createRoomsModel(otherAccountName());

    // THEN
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 3);
    const QSqlRecord record0 = tableModel->record(0);
    QCOMPARE(record0.value(int(RoomPendingTypedFields::Json)).toByteArray(),
             QJsonDocument(TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo::serialize(info1)).toJson(QJsonDocument::Compact));
    QCOMPARE(record0.value(int(RoomPendingTypedFields::RoomId)).toByteArray(), roomId);

    const QSqlRecord record1 = tableModel->record(1);
    QCOMPARE(record1.value(int(RoomPendingTypedFields::Json)).toByteArray(),
             QJsonDocument(TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo::serialize(info2)).toJson(QJsonDocument::Compact));
    QCOMPARE(record1.value(int(RoomPendingTypedFields::RoomId)).toByteArray(), roomId2);
}

void TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest::shouldDeleteRoomPendingTypedInfo() // this test depends on shouldStoreRoomPendingTypedInfo()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalRoomPendingTypedInfoDatabase logger;
    const QByteArray roomId = "foo2"_ba;

    // WHEN
    logger.deleteRoomPendingTypedInfo(otherAccountName(), roomId);

    // THEN
    auto tableModel = logger.createRoomsModel(otherAccountName());
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 2);
}

void TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest::shouldDeleteRoomPendingTypedInfoInvalidRoomId() // this test depends on
                                                                                                            // shouldStoreRoomPendingTypedInfo()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalRoomPendingTypedInfoDatabase logger;
    const QByteArray roomId = "foo2"_ba;

    // WHEN
    logger.deleteRoomPendingTypedInfo(otherAccountName(), roomId);

    // THEN
    auto tableModel = logger.createRoomsModel(otherAccountName());
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 2);
}

void TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest::shouldExtractJsonFromDatabase()
{
    {
        TextAutoGenerateText::TextAutoGenerateLocalRoomPendingTypedInfoDatabase logger;
        QCOMPARE(logger.loadRoomPendingTypedInfo(otherAccountName()).count(), 2);
    }
    {
        TextAutoGenerateText::TextAutoGenerateLocalRoomPendingTypedInfoDatabase logger;
        QCOMPARE(logger.loadRoomPendingTypedInfo(accountName()).count(), 0);
    }
}

#include "moc_textautogeneratelocalroompendingtypedinfodatabasetest.cpp"
