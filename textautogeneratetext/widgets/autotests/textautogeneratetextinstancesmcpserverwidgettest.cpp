/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextinstancesmcpserverwidgettest.h"

// #include "widgets/instancesmanager/textautogeneratetextinstancesmanagerlistview.h"
#include "widgets/mcpserver/textautogeneratetextinstancesmcpserverwidget.h"
#include <QLineEdit>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(TextAutoGenerateTextInstancesMcpServerWidgetTest)
TextAutoGenerateTextInstancesMcpServerWidgetTest::TextAutoGenerateTextInstancesMcpServerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextInstancesMcpServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextInstancesMcpServerWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    // auto mInstancesManagerListView = w.findChild<TextAutoGenerateText::TextAutoGenerateTextInstancesManagerListView *>(u"mInstancesManagerListView"_s);
    // QVERIFY(mInstancesManagerListView);

    auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(mSearchLineEdit->text().isEmpty());

    auto addMcpServerButton = w.findChild<QToolButton *>(u"addMcpServerButton"_s);
    QVERIFY(addMcpServerButton);
    QVERIFY(!addMcpServerButton->toolTip().isEmpty());
    QVERIFY(addMcpServerButton->autoRaise());
}

#include "moc_textautogeneratetextinstancesmcpserverwidgettest.cpp"
