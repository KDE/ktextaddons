/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolresultwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "common/grammarresulttextedit.h"
#include "languagetool/languagetoolresultwidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(LanguageToolResultWidgetTest)
LanguageToolResultWidgetTest::LanguageToolResultWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolResultWidgetTest::shouldHaveDefaultValue()
{
    TextGrammarCheck::LanguageToolResultWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mResult = w.findChild<TextGrammarCheck::GrammarResultTextEdit *>(u"grammarResult"_s);
    QVERIFY(mResult);
}

#include "moc_languagetoolresultwidgettest.cpp"
