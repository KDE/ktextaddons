/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancesmanagerwidgettest.h"
#include "widgets/instancesmanager/textautogeneratetextinstancesmanagerlistview.h"
#include "widgets/instancesmanager/textautogeneratetextinstancesmanagerwidget.h"
#include <QLineEdit>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateTextInstancesManagerWidgetTest)
TextAutoGenerateTextInstancesManagerWidgetTest::TextAutoGenerateTextInstancesManagerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextInstancesManagerWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextInstancesManagerWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mInstancesManagerListView =
        w.findChild<TextAutoGenerateText::TextAutoGenerateTextInstancesManagerListView *>(QStringLiteral("mInstancesManagerListView"));
    QVERIFY(mInstancesManagerListView);

    auto mSearchLineEdit = w.findChild<QLineEdit *>(QStringLiteral("mSearchLineEdit"));
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(mSearchLineEdit->text().isEmpty());

    auto addInstanceButton = w.findChild<QToolButton *>(QStringLiteral("addInstanceButton"));
    QVERIFY(addInstanceButton);
    QVERIFY(!addInstanceButton->toolTip().isEmpty());
    QVERIFY(addInstanceButton->autoRaise());
}

#include "moc_textautogeneratetextinstancesmanagerwidgettest.cpp"
