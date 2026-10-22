/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpregistryserverwidgettest.h"
#include "client/addmcpregistryserverwidget.h"
#include "client/mcpregistryserverinfowidget.h"
#include "client/mcpregistryserverlistview.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(AddMcpRegistryServerWidgetTest)

using namespace Qt::Literals::StringLiterals;
AddMcpRegistryServerWidgetTest::AddMcpRegistryServerWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void AddMcpRegistryServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpRegistryServerWidget w;
    QVERIFY(!w.currentServerInfo().isValid());

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mSearchLineEdit = w.findChild<QLineEdit *>(u"mSearchLineEdit"_s);
    QVERIFY(mSearchLineEdit);
    QVERIFY(mSearchLineEdit->text().isEmpty());
    QVERIFY(mSearchLineEdit->isClearButtonEnabled());
    QVERIFY(!mSearchLineEdit->placeholderText().isEmpty());

    auto splitter = w.findChild<QSplitter *>(u"splitter"_s);
    QVERIFY(splitter);
    QVERIFY(!splitter->childrenCollapsible());

    auto mListView = w.findChild<TextAutoGenerateTextMcpProtocolWidgets::McpRegistryServerListView *>(u"mListView"_s);
    QVERIFY(mListView);

    auto mInfoWidget = w.findChild<TextAutoGenerateTextMcpProtocolWidgets::McpRegistryServerInfoWidget *>(u"mInfoWidget"_s);
    QVERIFY(mInfoWidget);

    auto mStatusLabel = w.findChild<QLabel *>(u"mStatusLabel"_s);
    QVERIFY(mStatusLabel);
    QVERIFY(mStatusLabel->text().isEmpty());

    auto mLoadMoreButton = w.findChild<QPushButton *>(u"mLoadMoreButton"_s);
    QVERIFY(mLoadMoreButton);
    QVERIFY(!mLoadMoreButton->isEnabled());
    QVERIFY(!mLoadMoreButton->text().isEmpty());
}
#include "moc_addmcpregistryserverwidgettest.cpp"
