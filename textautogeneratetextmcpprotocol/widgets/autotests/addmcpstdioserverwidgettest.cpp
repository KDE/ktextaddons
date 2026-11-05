/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpstdioserverwidgettest.h"
#include "client/addmcpstdioserverenvironmentwidget.h"
#include "client/addmcpstdioserverwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
QTEST_MAIN(AddMcpStdioServerWidgetTest)
using namespace Qt::Literals::StringLiterals;
AddMcpStdioServerWidgetTest::AddMcpStdioServerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AddMcpStdioServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpStdioServerWidget w;
    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mCommandLineEdit = w.findChild<QLineEdit *>(u"mCommandLineEdit"_s);
    QVERIFY(mCommandLineEdit);
    QVERIFY(mCommandLineEdit->text().isEmpty());

    auto mArgumentsLineEdit = w.findChild<QLineEdit *>(u"mArgumentsLineEdit"_s);
    QVERIFY(mArgumentsLineEdit);
    QVERIFY(mArgumentsLineEdit->text().isEmpty());

    auto mEnvironmentWidget = w.findChild<TextAutoGenerateTextMcpProtocolWidgets::AddMcpStdioServerEnvironmentWidget *>(u"mEnvironmentWidget"_s);
    QVERIFY(mEnvironmentWidget);
    QVERIFY(mEnvironmentWidget->environments().isEmpty());
}

void AddMcpStdioServerWidgetTest::shouldLoadAndSaveEnvironments()
{
    TextAutoGenerateTextMcpProtocolWidgets::AddMcpStdioServerWidget w;
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setCommand(u"npx"_s);
    const QMap<QString, QString> envs{{u"GITHUB_TOKEN"_s, QString()}, {u"FOO"_s, u"bar"_s}};
    settings.setEnvironments(envs);
    server.setSettings(settings);
    w.loadSettings(server);

    TextAutoGenerateTextMcpProtocolCore::McpServer saved;
    w.saveSettings(saved);
    QCOMPARE(saved.settings().environments(), envs);
    QCOMPARE(saved.settings().command(), u"npx"_s);
}
#include "moc_addmcpstdioserverwidgettest.cpp"
