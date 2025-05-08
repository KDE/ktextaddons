/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratewidgettest.h"
#include "widgets/textautogenerateheaderwidget.h"
#include "widgets/textautogenerateresultwidget.h"
#include "widgets/textautogeneratetextlineeditwidget.h"
#include "widgets/textautogeneratewidget.h"
#include <QSplitter>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutogenerateWidgetTest)

TextAutogenerateWidgetTest::TextAutogenerateWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutogenerateWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutogenerateWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextAutogenerateResultWidget = w.findChild<TextAutoGenerateText::TextAutogenerateResultWidget *>(QStringLiteral("mTextAutogenerateResultWidget"));
    QVERIFY(mTextAutogenerateResultWidget);

    auto mTextAutoGenerateTextLineEditWidget =
        w.findChild<TextAutoGenerateText::TextAutoGenerateTextLineEditWidget *>(QStringLiteral("mTextAutoGenerateTextLineEditWidget"));
    QVERIFY(mTextAutoGenerateTextLineEditWidget);

    auto mSplitter = w.findChild<QSplitter *>(QStringLiteral("mSplitter"));
    QVERIFY(mSplitter);
    QCOMPARE(mSplitter->orientation(), Qt::Horizontal);

    auto mHeaderWidget = w.findChild<TextAutoGenerateText::TextAutogenerateHeaderWidget *>(QStringLiteral("mHeaderWidget"));
    QVERIFY(mHeaderWidget);
}

#include "moc_textautogeneratewidgettest.cpp"
