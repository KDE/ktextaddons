/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratelocalchatpendingtypedinfodatabasetest.h"
#include "core/localdatabase/textautogeneratelocalchatpendingtypedinfodatabase.h"
#include <QJsonObject>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QStandardPaths>
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest)
using namespace Qt::Literals::StringLiterals;
enum class RoomPendingTypedFields {
    RoomId,
    Json,
}; // in the same order as the table

TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest::TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);

    // Clean up after previous runs
    TextAutoGenerateText::TextAutoGenerateLocalChatPendingTypedInfoDatabase roomPendingTypedInfoDataBase;
    QFile::remove(roomPendingTypedInfoDataBase.dbFileName({}));
}

void TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest::shouldDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateLocalChatPendingTypedInfoDatabase roomPendingTypedInfoDataBase;
    QCOMPARE(roomPendingTypedInfoDataBase.schemaDatabaseStr(), u"CREATE TABLE ROOMPENDINGTYPED (roomId TEXT PRIMARY KEY NOT NULL, json TEXT)"_s);
}

void TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest::shouldVerifyDbFileName()
{
    TextAutoGenerateText::TextAutoGenerateLocalChatPendingTypedInfoDatabase roomPendingTypedInfoDataBase;
    QCOMPARE(roomPendingTypedInfoDataBase.dbFileName({}),
             QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + u"/ai-database/roompendingtypedinfo/pendingtypedinfo.sqlite"_s);
}

void TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest::shouldStoreRoomPendingTypedInfo()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalChatPendingTypedInfoDatabase logger;

    QByteArray roomId = "foo1"_ba;
    TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info1;
    info1.text = u"foo"_s;
    logger.updateChatPendingTypedInfo(roomId, info1);

    // Update PendingTypedInfo
    info1.scrollbarPosition = 5;
    logger.updateChatPendingTypedInfo(roomId, info1);

    QByteArray roomId2 = "foo2"_ba;
    TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info2;
    info2.scrollbarPosition = 5;
    logger.updateChatPendingTypedInfo(roomId2, info2);

    QByteArray roomId3 = "foo3"_ba;
    TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo info3;
    info3.scrollbarPosition = 5;
    logger.updateChatPendingTypedInfo(roomId3, info2);

    // WHEN
    auto tableModel = logger.createRoomsModel();

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

void TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest::shouldDeleteRoomPendingTypedInfo() // this test depends on shouldStoreRoomPendingTypedInfo()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalChatPendingTypedInfoDatabase logger;
    const QByteArray roomId = "foo2"_ba;

    // WHEN
    logger.deleteChatPendingTypedInfo(roomId);

    // THEN
    auto tableModel = logger.createRoomsModel();
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 2);
}

void TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest::shouldDeleteRoomPendingTypedInfoInvalidRoomId() // this test depends on
                                                                                                            // shouldStoreRoomPendingTypedInfo()
{
    // GIVEN
    TextAutoGenerateText::TextAutoGenerateLocalChatPendingTypedInfoDatabase logger;
    const QByteArray roomId = "foo2"_ba;

    // WHEN
    logger.deleteChatPendingTypedInfo(roomId);

    // THEN
    auto tableModel = logger.createRoomsModel();
    QVERIFY(tableModel);
    QCOMPARE(tableModel->rowCount(), 2);
}

void TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest::shouldExtractJsonFromDatabase()
{
    {
        TextAutoGenerateText::TextAutoGenerateLocalChatPendingTypedInfoDatabase logger;
        QCOMPARE(logger.loadChatPendingTypedInfo().count(), 2);
    }
}

#include "moc_textautogeneratelocalchatpendingtypedinfodatabasetest.cpp"
