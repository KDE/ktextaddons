/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextmcpserverwidgettest.h"

#include "mcpserverlistview.h"
#include "mcpserverwidget.h"
#include <QLineEdit>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(TextAutoGenerateTextMcpServerWidgetTest)
TextAutoGenerateTextMcpServerWidgetTest::TextAutoGenerateTextMcpServerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextMcpServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::McpServerWidget w(nullptr);

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mMcpServerListView = w.findChild<TextAutoGenerateTextMcpProtocolWidgets::McpServerListView *>(u"mMcpServerListView"_s);
    QVERIFY(mMcpServerListView);

    auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(mSearchLineEdit->text().isEmpty());

    auto addMcpServerButton = w.findChild<QToolButton *>(u"addMcpServerButton"_s);
    QVERIFY(addMcpServerButton);
    QVERIFY(!addMcpServerButton->toolTip().isEmpty());
    QVERIFY(addMcpServerButton->autoRaise());
}

#include "moc_textautogeneratetextmcpserverwidgettest.cpp"
