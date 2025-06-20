/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskwidgettest.h"
#include "widgets/quickask/textautogeneratequickaskwidget.h"
#include <QStackedWidget>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateQuickAskWidgetTest)
TextAutoGenerateQuickAskWidgetTest::TextAutoGenerateQuickAskWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateQuickAskWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateQuickAskWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mStackedWidget = w.findChild<QStackedWidget *>(QStringLiteral("mStackedWidget"));
    QVERIFY(mStackedWidget);
}

#include "moc_textautogeneratequickaskwidgettest.cpp"
