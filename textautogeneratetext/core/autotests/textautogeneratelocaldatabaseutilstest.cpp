/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratelocaldatabaseutilstest.h"

#include "core/localdatabase/textautogeneratelocaldatabaseutils.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateLocalDatabaseUtilsTest)

TextAutoGenerateLocalDatabaseUtilsTest::TextAutoGenerateLocalDatabaseUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateLocalDatabaseUtilsTest::shouldCheckPath()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::databasePath(
                 TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::DatabasePath::Messages),
             u"messages/"_s);
    QCOMPARE(
        TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::databasePath(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::DatabasePath::Chats),
        u"chats/"_s);
}

void TextAutoGenerateLocalDatabaseUtilsTest::shouldCheckDataBase()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::deleteMessage(), u"DELETE FROM MESSAGES WHERE messageId = ?"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::insertReplaceMessage(), u"INSERT OR REPLACE INTO MESSAGES VALUES (?, ?, ?)"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::deleteChat(), u"DELETE FROM CHATS WHERE chatId = ?"_s);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateLocalDatabaseUtils::insertReplaceChat(), u"INSERT OR REPLACE INTO CHATS VALUES (?, ?)"_s);
}

#include "moc_textautogeneratelocaldatabaseutilstest.cpp"
