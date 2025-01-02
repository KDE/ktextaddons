/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteresultwidgettest.h"
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
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins());

    auto mResult = w.findChild<TextGrammarCheck::GrammarResultTextEdit *>(QStringLiteral("grammarResult"));
    QVERIFY(mResult);

    auto closeBtn = w.findChild<QToolButton *>(QStringLiteral("close-button"));
    QVERIFY(closeBtn);
    // QVERIFY(!closeBtn->icon().isNull());
    QVERIFY(!closeBtn->toolTip().isEmpty());
}

#include "moc_grammalecteresultwidgettest.cpp"
