/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languageinfotest.h"
#include "languagetool/languageinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(LanguageInfoTest)

LanguageInfoTest::LanguageInfoTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageInfoTest::shouldHaveDefaultValues()
{
    TextGrammarCheck::LanguageInfo w;
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.code().isEmpty());
    QVERIFY(w.longCode().isEmpty());
    QVERIFY(!w.isValid());
}

#include "moc_languageinfotest.cpp"
