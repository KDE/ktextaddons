/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateblockcmarksupporttest.h"
#include "core/textautogenerateblockcmarksupport.h"

#include <QTest>

using namespace Qt::Literals::StringLiterals;

QTEST_GUILESS_MAIN(TextAutoGenerateBlockCMarkSupportTest)

TextAutoGenerateBlockCMarkSupportTest::TextAutoGenerateBlockCMarkSupportTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateBlockCMarkSupportTest::shouldHighlightLiteralSearchText()
{
    TextAutoGenerateText::TextAutoGenerateBlockCMarkSupport support;
    int numberOfTextSearched = 0;
    const QString sourceText = u"A.B"_s;
    const QString searchText = u"."_s;

    const QString converted = support.convertMessageText(sourceText, "uuid"_ba, searchText, numberOfTextSearched, -1);

    QCOMPARE(numberOfTextSearched, 1);
    QVERIFY(converted.contains(u"A"_s));
    QVERIFY(converted.contains(u"B"_s));
}

#include "moc_textautogenerateblockcmarksupporttest.cpp"
