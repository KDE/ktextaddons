/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticonunicodeutilstest.h"
using namespace Qt::Literals::StringLiterals;

#include "emoticonunicodeutils.h"
#include <QTest>

QTEST_GUILESS_MAIN(EmoticonUnicodeUtilsTest)

EmoticonUnicodeUtilsTest::EmoticonUnicodeUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void EmoticonUnicodeUtilsTest::shouldHaveDefaultValues()
{
    QCOMPARE(TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier(), u"recents"_s);
    QCOMPARE(TextEmoticonsCore::EmoticonUnicodeUtils::customIdentifier(), u"customs"_s);
}

#include "moc_emoticonunicodeutilstest.cpp"
