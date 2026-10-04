/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpserverwidgettest.h"

#include "server/mcpserverlistview.h"
#include "server/mcpserverwidget.h"
#include <QLineEdit>
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>
#include <QToolButton>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(McpServerWidgetTest)
McpServerWidgetTest::McpServerWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void McpServerWidgetTest::shouldHaveDefaultValues()
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

void McpServerWidgetTest::shouldEmitSettingsChangedWhenServerIsEnabled()
{
    TextAutoGenerateTextMcpProtocolCore::McpServerModel model;
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    server.setName(u"foo"_s);
    server.setEnabled(true);
    model.addMcpServer(server);
    const TextAutoGenerateTextMcpProtocolWidgets::McpServerWidget w(&model);
    QSignalSpy settingsChangedSpy(&w, &TextAutoGenerateTextMcpProtocolWidgets::McpServerWidget::settingsChanged);
    QVERIFY(model.setData(model.index(0), Qt::Unchecked, Qt::CheckStateRole));
    QCOMPARE(settingsChangedSpy.count(), 1);
    // Same value: nothing changed
    QVERIFY(model.setData(model.index(0), Qt::Unchecked, Qt::CheckStateRole));
    QCOMPARE(settingsChangedSpy.count(), 1);
}

#include "moc_mcpserverwidgettest.cpp"
