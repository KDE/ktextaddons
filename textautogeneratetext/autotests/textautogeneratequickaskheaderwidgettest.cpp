/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequickaskheaderwidgettest.h"
#include "widgets/quickask/textautogeneratequickaskheaderwidget.h"
#include <QHBoxLayout>
#include <QTest>
#include <QToolButton>
QTEST_MAIN(TextAutoGenerateQuickAskHeaderWidgetTest)

TextAutoGenerateQuickAskHeaderWidgetTest::TextAutoGenerateQuickAskHeaderWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateQuickAskHeaderWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateQuickAskHeaderWidget w(nullptr);

    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto configureButton = w.findChild<QToolButton *>(QStringLiteral("configureButton"));
    QVERIFY(configureButton);
    QVERIFY(!configureButton->toolTip().isEmpty());
}

#include "moc_textautogeneratequickaskheaderwidgettest.cpp"
