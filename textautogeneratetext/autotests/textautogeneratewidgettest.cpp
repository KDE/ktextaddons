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
QTEST_MAIN(TextAutoGenerateWidgetTest)

TextAutoGenerateWidgetTest::TextAutoGenerateWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTextAutoGenerateResultWidget = w.findChild<TextAutoGenerateText::TextAutoGenerateResultWidget *>(QStringLiteral("mTextAutoGenerateResultWidget"));
    QVERIFY(mTextAutoGenerateResultWidget);

    auto mTextAutoGenerateTextLineEditWidget =
        w.findChild<TextAutoGenerateText::TextAutoGenerateTextLineEditWidget *>(QStringLiteral("mTextAutoGenerateTextLineEditWidget"));
    QVERIFY(mTextAutoGenerateTextLineEditWidget);

    auto mSplitter = w.findChild<QSplitter *>(QStringLiteral("mSplitter"));
    QVERIFY(mSplitter);
    QCOMPARE(mSplitter->orientation(), Qt::Horizontal);

    auto mHeaderWidget = w.findChild<TextAutoGenerateText::TextAutoGenerateHeaderWidget *>(QStringLiteral("mHeaderWidget"));
    QVERIFY(mHeaderWidget);
}

#include "moc_textautogeneratewidgettest.cpp"
