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

#include "moc_textautogeneratelocaldatabaseutilstest.cpp"
