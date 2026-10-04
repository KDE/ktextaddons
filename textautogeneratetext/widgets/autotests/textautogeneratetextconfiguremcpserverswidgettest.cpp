/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextconfiguremcpserverswidgettest.h"
#include "core/textautogeneratemanager.h"
#include "widgets/configure/textautogeneratetextconfiguremcpserverswidget.h"
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>
#include <TextAutoGenerateTextMcpProtocolWidgets/McpServerWidget>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(TextAutoGenerateTextConfigureMcpServersWidgetTest)

TextAutoGenerateTextConfigureMcpServersWidgetTest::TextAutoGenerateTextConfigureMcpServersWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateTextConfigureMcpServersWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextConfigureMcpServersWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
    QVERIFY(w.findChild<TextAutoGenerateTextMcpProtocolWidgets::McpServerWidget *>(u"mMcpServerWidget"_s));
}

void TextAutoGenerateTextConfigureMcpServersWidgetTest::shouldApplyChangesWhenSaved()
{
    TextAutoGenerateText::TextAutoGenerateManager manager;
    auto managerModel = manager.textAutoGenerateTextMcpServerManager()->mcpServerModel();
    managerModel->setMcpServers({});
    TextAutoGenerateText::TextAutoGenerateTextConfigureMcpServersWidget w(&manager);

    // Edit list of servers in widget
    auto widgetModel = w.findChild<TextAutoGenerateTextMcpProtocolCore::McpServerModel *>();
    QVERIFY(widgetModel);
    QVERIFY(widgetModel != managerModel);
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    server.setName(u"foo"_s);
    server.createUniqueIdentifier();
    server.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(QUrl(u"http://localhost/mcp"_s));
    server.setSettings(settings);
    widgetModel->addMcpServer(server);
    // Not applied yet
    QVERIFY(managerModel->mcpServers().isEmpty());

    w.save();
    QCOMPARE(managerModel->mcpServers().count(), 1);
    QCOMPARE(managerModel->mcpServers().at(0), server);

    // Saved in config
    TextAutoGenerateTextMcpProtocolCore::McpServerManager otherManager;
    otherManager.loadServers();
    QCOMPARE(otherManager.mcpServerModel()->mcpServers().count(), 1);

    // Changes are discarded by load()
    widgetModel->removeMcpServer(server.identifier());
    w.load();
    QCOMPARE(widgetModel->mcpServers().count(), 1);

    // Clean config
    managerModel->setMcpServers({});
    manager.textAutoGenerateTextMcpServerManager()->saveServers();
}

#include "moc_textautogeneratetextconfiguremcpserverswidgettest.cpp"
