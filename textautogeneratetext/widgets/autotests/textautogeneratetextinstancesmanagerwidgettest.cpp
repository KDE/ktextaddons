/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancesmanagerwidgettest.h"
using namespace Qt::Literals::StringLiterals;

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

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mInstancesManagerListView = w.findChild<TextAutoGenerateText::TextAutoGenerateTextInstancesManagerListView *>(u"mInstancesManagerListView"_s);
    QVERIFY(mInstancesManagerListView);

    auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(mSearchLineEdit->text().isEmpty());

    auto addInstanceButton = w.findChild<QToolButton *>(u"addInstanceButton"_s);
    QVERIFY(addInstanceButton);
    QVERIFY(!addInstanceButton->toolTip().isEmpty());
    QVERIFY(addInstanceButton->autoRaise());
}

#include "moc_textautogeneratetextinstancesmanagerwidgettest.cpp"
