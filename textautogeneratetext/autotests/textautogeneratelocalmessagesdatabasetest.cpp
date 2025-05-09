/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelocalmessagesdatabasetest.h"
#include "core/localdatabase/textautogeneratelocalmessagesdatabase.h"
#include <QStandardPaths>
#include <QTest>

QTEST_GUILESS_MAIN(TextAutoGenerateLocalMessagesDatabaseTest)

static QString chatId()
{
    return QStringLiteral("myChatId");
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

#include "moc_textautogeneratelocalmessagesdatabasetest.cpp"
