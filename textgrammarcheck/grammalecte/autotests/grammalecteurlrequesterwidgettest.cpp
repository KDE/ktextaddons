/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "grammalecteurlrequesterwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "grammalecte/grammalecteurlrequesterwidget.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTest>
#include <QToolButton>

QTEST_MAIN(GrammalecteUrlRequesterWidgetTest)

GrammalecteUrlRequesterWidgetTest::GrammalecteUrlRequesterWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void GrammalecteUrlRequesterWidgetTest::shouldHaveDefaultValues()
{
    TextGrammarCheck::GrammalecteUrlRequesterWidget w;

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mLineEdit = w.findChild<QLineEdit *>(u"mLineEdit"_s);
    QVERIFY(mLineEdit);
    QVERIFY(mLineEdit->text().isEmpty());

    auto selectUrlButton = w.findChild<QToolButton *>(u"selectUrlButton"_s);
    QVERIFY(selectUrlButton);
    QVERIFY(!selectUrlButton->text().isEmpty());
}

#include "moc_grammalecteurlrequesterwidgettest.cpp"
