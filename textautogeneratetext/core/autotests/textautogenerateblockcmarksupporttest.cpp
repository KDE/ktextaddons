/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateblockcmarksupporttest.h"
#include "core/textautogenerateblockcmarksupport.h"

#include <QTest>

QTEST_GUILESS_MAIN(TextAutoGenerateBlockCMarkSupportTest)

TextAutoGenerateBlockCMarkSupportTest::TextAutoGenerateBlockCMarkSupportTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateBlockCMarkSupportTest::shouldHighlightLiteralSearchText()
{
    TextAutoGenerateText::TextAutoGenerateBlockCMarkSupport support;
    int numberOfTextSearched = 0;
    const QString sourceText = QStringLiteral("A.B");
    const QString searchText = QStringLiteral(".");

    const QString converted = support.convertMessageText(sourceText, QByteArrayLiteral("uuid"), searchText, numberOfTextSearched, -1);

    QCOMPARE(numberOfTextSearched, 1);
    QVERIFY(converted.contains(QStringLiteral("A")));
    QVERIFY(converted.contains(QStringLiteral("B")));
}

#include "moc_textautogenerateblockcmarksupporttest.cpp"
