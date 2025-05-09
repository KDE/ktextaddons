/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocaldatabaseutilstest.h"
#include "core/localdatabase/textautogeneratelocaldatabaseutils.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateLocalDatabaseUtilsTest)

TextAutoGenerateLocalDatabaseUtilsTest::TextAutoGenerateLocalDatabaseUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateLocalDatabaseUtilsTest::shouldCheckPath()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::databasePath(
                 TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::DatabasePath::Messages),
             QStringLiteral("messages/"));
    QCOMPARE(
        TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::DatabasePath::Chats),
        QStringLiteral("chats/"));
}

void TextAutoGenerateLocalDatabaseUtilsTest::shouldCheckDataBase()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::deleteMessage(), QStringLiteral("DELETE FROM MESSAGES WHERE messageId = ?"));
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::insertReplaceMessage(), QStringLiteral("INSERT OR REPLACE INTO MESSAGES VALUES (?, ?)"));
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::deleteChat(), QStringLiteral("DELETE FROM CHATS WHERE chatId = ?"));
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::insertReplaceChat(), QStringLiteral("INSERT OR REPLACE INTO CHATS VALUES (?, ?)"));
}

#include "moc_textautogeneratelocaldatabaseutilstest.cpp"
