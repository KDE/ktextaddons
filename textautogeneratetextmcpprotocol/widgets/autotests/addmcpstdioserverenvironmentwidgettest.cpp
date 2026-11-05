/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpstdioserverenvironmentwidgettest.h"
#include "client/addmcpstdioserverenvironmentwidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QTest>
QTEST_MAIN(AddMcpStdioServerEnvironmentWidgetTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
AddMcpStdioServerEnvironmentWidgetTest::AddMcpStdioServerEnvironmentWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AddMcpStdioServerEnvironmentWidgetTest::shouldHaveDefaultValues()
{
    const AddMcpStdioServerEnvironmentWidget w;
    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTableWidget = w.findChild<QTableWidget *>(u"mTableWidget"_s);
    QVERIFY(mTableWidget);
    QCOMPARE(mTableWidget->rowCount(), 0);
    QCOMPARE(mTableWidget->columnCount(), 2);

    auto addButton = w.findChild<QPushButton *>(u"addButton"_s);
    QVERIFY(addButton);
    QVERIFY(addButton->isEnabled());

    auto mRemoveButton = w.findChild<QPushButton *>(u"mRemoveButton"_s);
    QVERIFY(mRemoveButton);
    QVERIFY(!mRemoveButton->isEnabled());

    QVERIFY(w.environments().isEmpty());
}

void AddMcpStdioServerEnvironmentWidgetTest::shouldSetEnvironments()
{
    AddMcpStdioServerEnvironmentWidget w;
    const QMap<QString, QString> envs{{u"GITHUB_TOKEN"_s, QString()}, {u"FOO"_s, u"bar baz"_s}};
    w.setEnvironments(envs);
    auto mTableWidget = w.findChild<QTableWidget *>(u"mTableWidget"_s);
    QCOMPARE(mTableWidget->rowCount(), 2);
    QCOMPARE(w.environments(), envs);

    w.setEnvironments({});
    QCOMPARE(mTableWidget->rowCount(), 0);
    QVERIFY(w.environments().isEmpty());
}

void AddMcpStdioServerEnvironmentWidgetTest::shouldIgnoreInvalidNames()
{
    AddMcpStdioServerEnvironmentWidget w;
    w.setEnvironments({{u"FOO"_s, u"bar"_s}});
    auto mTableWidget = w.findChild<QTableWidget *>(u"mTableWidget"_s);
    mTableWidget->item(0, 0)->setText(u"  "_s);
    QVERIFY(w.environments().isEmpty());
    mTableWidget->item(0, 0)->setText(u"A=B"_s);
    QVERIFY(w.environments().isEmpty());
    mTableWidget->item(0, 0)->setText(u" FOO "_s);
    QCOMPARE(w.environments(), (QMap<QString, QString>{{u"FOO"_s, u"bar"_s}}));
}
#include "moc_addmcpstdioserverenvironmentwidgettest.cpp"
