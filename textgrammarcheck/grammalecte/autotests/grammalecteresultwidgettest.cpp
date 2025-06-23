/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteresultwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "common/grammarresulttextedit.h"
#include "grammalecte/grammalecteresultwidget.h"
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
QTEST_MAIN(GrammarResultWidgetTest)

GrammarResultWidgetTest::GrammarResultWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void GrammarResultWidgetTest::shouldHaveDefaultValue()
{
    TextGrammarCheck::GrammalecteResultWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mResult = w.findChild<TextGrammarCheck::GrammarResultTextEdit *>(u"grammarResult"_s);
    QVERIFY(mResult);

    auto closeBtn = w.findChild<QToolButton *>(u"close-button"_s);
    QVERIFY(closeBtn);
    // QVERIFY(!closeBtn->icon().isNull());
    QVERIFY(!closeBtn->toolTip().isEmpty());
}

#include "moc_grammalecteresultwidgettest.cpp"
