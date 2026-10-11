/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextconfiguremcpserverswidgettest.h"
#include "core/mcp/textautogeneratemcptoolsutils.h"
#include "core/textautogeneratemanager.h"
#include "widgets/configure/textautogeneratetextconfiguremcpserverswidget.h"
#include <QLabel>
#include <QListWidget>
#include <QSignalSpy>
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

    auto alwaysAllowedLabel = w.findChild<QLabel *>(u"alwaysAllowedLabel"_s);
    QVERIFY(alwaysAllowedLabel);
    QVERIFY(!alwaysAllowedLabel->text().isEmpty());
    auto mAlwaysAllowedListWidget = w.findChild<QListWidget *>(u"mAlwaysAllowedListWidget"_s);
    QVERIFY(mAlwaysAllowedListWidget);
    QCOMPARE(mAlwaysAllowedListWidget->count(), 0);
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

void TextAutoGenerateTextConfigureMcpServersWidgetTest::shouldEditAlwaysAllowedServers()
{
    TextAutoGenerateText::TextAutoGenerateManager manager;
    auto serverManager = manager.textAutoGenerateTextMcpServerManager();
    const QString configFileName = serverManager->serverConfigFileName();
    TextAutoGenerateTextMcpProtocolCore::McpServer first;
    first.setName(u"first"_s);
    first.createUniqueIdentifier();
    TextAutoGenerateTextMcpProtocolCore::McpServer second;
    second.setName(u"second"_s);
    second.createUniqueIdentifier();
    serverManager->mcpServerModel()->setMcpServers({first, second});
    TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::setAlwaysAllowedServers(configFileName, {first.identifier(), "obsolete"_ba});

    TextAutoGenerateText::TextAutoGenerateTextConfigureMcpServersWidget w(&manager);
    auto listWidget = w.findChild<QListWidget *>(u"mAlwaysAllowedListWidget"_s);
    QVERIFY(listWidget);
    QCOMPARE(listWidget->count(), 2);
    QCOMPARE(listWidget->item(0)->text(), u"first"_s);
    QCOMPARE(listWidget->item(0)->checkState(), Qt::Checked);
    QCOMPARE(listWidget->item(1)->checkState(), Qt::Unchecked);

    // Changing state is a change of settings
    QSignalSpy settingsChangedSpy(&w, &TextAutoGenerateText::TextAutoGenerateTextConfigureMcpServersWidget::settingsChanged);
    listWidget->item(0)->setCheckState(Qt::Unchecked);
    listWidget->item(1)->setCheckState(Qt::Checked);
    QCOMPARE(settingsChangedSpy.count(), 2);

    // Removed server is removed from list, state of others is kept
    auto widgetModel = w.findChild<TextAutoGenerateTextMcpProtocolCore::McpServerModel *>();
    widgetModel->removeMcpServer(first.identifier());
    QCOMPARE(listWidget->count(), 1);
    QCOMPARE(listWidget->item(0)->text(), u"second"_s);
    QCOMPARE(listWidget->item(0)->checkState(), Qt::Checked);

    // Not applied before save(), obsolete servers are removed when saved
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::alwaysAllowedServers(configFileName), (QList<QByteArray>{first.identifier(), "obsolete"_ba}));
    w.save();
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::alwaysAllowedServers(configFileName), QList<QByteArray>{second.identifier()});

    // Clean config
    serverManager->mcpServerModel()->setMcpServers({});
    serverManager->saveServers();
    TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::setAlwaysAllowedServers(configFileName, {});
}

#include "moc_textautogeneratetextconfiguremcpserverswidgettest.cpp"
