/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "widgets/common/textautogenerateresultwidget.h"
#include "widgets/common/textautogeneratetextlineeditwidget.h"
#include "widgets/textautogenerateheaderwidget.h"
#include "widgets/textautogeneratewidget.h"
#include <QSplitter>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateWidgetTest)

TextAutoGenerateWidgetTest::TextAutoGenerateWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextAutoGenerateResultWidget = w.findChild<TextAutoGenerateText::TextAutoGenerateResultWidget *>(u"mTextAutoGenerateResultWidget"_s);
    QVERIFY(mTextAutoGenerateResultWidget);

    auto mTextAutoGenerateTextLineEditWidget =
        w.findChild<TextAutoGenerateText::TextAutoGenerateTextLineEditWidget *>(u"mTextAutoGenerateTextLineEditWidget"_s);
    QVERIFY(mTextAutoGenerateTextLineEditWidget);

    auto mSplitter = w.findChild<QSplitter *>(u"mSplitter"_s);
    QVERIFY(mSplitter);
    QCOMPARE(mSplitter->orientation(), Qt::Horizontal);

    auto mHeaderWidget = w.findChild<TextAutoGenerateText::TextAutoGenerateHeaderWidget *>(u"mHeaderWidget"_s);
    QVERIFY(mHeaderWidget);
}

#include "moc_textautogeneratewidgettest.cpp"
