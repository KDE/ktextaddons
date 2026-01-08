/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskwidgettest.h"
using namespace Qt::Literals::StringLiterals;

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
    const TextAutoGenerateText::TextAutoGenerateQuickAskWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mStackedWidget = w.findChild<QStackedWidget *>(u"mStackedWidget"_s);
    QVERIFY(mStackedWidget);
}

#include "moc_textautogeneratequickaskwidgettest.cpp"
