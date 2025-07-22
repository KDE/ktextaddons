/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocalchatsdatabasetest.h"

#include "core/localdatabase/textautogeneratelocalchatsdatabase.h"
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateLocalChatsDatabaseTest)
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
}

#include "moc_textautogeneratelocalchatsdatabasetest.cpp"
