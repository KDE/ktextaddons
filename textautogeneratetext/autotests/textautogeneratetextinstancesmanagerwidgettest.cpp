/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancesmanagerwidgettest.h"
#include "widgets/instancesmanager/textautogeneratetextinstancesmanagerwidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateTextInstancesManagerWidgetTest)
TextAutoGenerateTextInstancesManagerWidgetTest::TextAutoGenerateTextInstancesManagerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextInstancesManagerWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextInstancesManagerWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
}

#include "moc_textautogeneratetextinstancesmanagerwidgettest.cpp"
