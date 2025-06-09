/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancemanagerwidgettest.h"
#include "widgets/instancesmanager/textautogeneratetextinstancemanagerwidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateTextInstanceManagerWidgetTest)
TextAutoGenerateTextInstanceManagerWidgetTest::TextAutoGenerateTextInstanceManagerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextInstanceManagerWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextInstanceManagerWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
}

#include "moc_textautogeneratetextinstancemanagerwidgettest.cpp"
