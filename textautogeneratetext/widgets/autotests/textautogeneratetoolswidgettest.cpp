/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolswidgettest.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "core/textautogeneratemanager.h"
#include "fakemcpserver.h"
#include "widgets/toolswidget/textautogeneratetoolswidget.h"
#include <QLabel>
#include <QMenu>
#include <QStandardPaths>
#include <QTest>
#include <QToolButton>
#include <TextAddonsWidgets/TextAddonsWidgetFlowLayout>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>
QTEST_MAIN(TextAutoGenerateToolsWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateToolsWidgetTest::TextAutoGenerateToolsWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateToolsWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateToolsWidget w;
    QVERIFY(w.generateListOfActiveTools().isEmpty());

    auto mainLayout = w.findChild<TextAddonsWidgets::TextAddonsWidgetFlowLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto label = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(label);
    QVERIFY(label->font().bold());
}

void TextAutoGenerateToolsWidgetTest::shouldShowMcpServers()
{
    TextAutoGenerateText::TextAutoGenerateManager manager;
    auto model = manager.textAutoGenerateTextMcpServerManager()->mcpServerModel();
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    server.setName(u"my server"_s);
    server.createUniqueIdentifier();
    server.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    // Nothing listens on this port
    settings.setServerUrl(QUrl(u"http://127.0.0.1:1/mcp"_s));
    server.setSettings(settings);
    model->setMcpServers({server});

    const TextAutoGenerateText::TextAutoGenerateToolsWidget w(&manager);
    QToolButton *button = nullptr;
    const auto buttons = w.findChildren<QToolButton *>();
    for (auto b : buttons) {
        if (b->text() == u"my server"_s) {
            button = b;
        }
    }
    QVERIFY(button);
    QVERIFY(button->isCheckable());
    QVERIFY(!button->toolTip().isEmpty());

    const QByteArray identifier = TextAutoGenerateText::TextAutoGenerateMcpToolsManager::toolIdentifier(server.identifier());
    // Selecting server connects to it
    button->setChecked(true);
    QCOMPARE(w.generateListOfActiveTools(), QList<QByteArray>{identifier});
    QVERIFY(manager.textAutoGenerateMcpToolsManager()->status(server.identifier())
            != TextAutoGenerateText::TextAutoGenerateMcpToolsManager::Status::Disconnected);

    // Server disabled: button is removed
    QVERIFY(model->setData(model->index(0), Qt::Unchecked, Qt::CheckStateRole));
    QVERIFY(w.generateListOfActiveTools().isEmpty());
}

void TextAutoGenerateToolsWidgetTest::shouldRestoreMcpServerSelection()
{
    TextAutoGenerateText::TextAutoGenerateManager manager;
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    server.setName(u"my server"_s);
    server.createUniqueIdentifier();
    server.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setCommand(u"/does/not/exist"_s);
    server.setSettings(settings);
    manager.textAutoGenerateTextMcpServerManager()->mcpServerModel()->setMcpServers({server});

    TextAutoGenerateText::TextAutoGenerateToolsWidget w(&manager);
    const QByteArray identifier = TextAutoGenerateText::TextAutoGenerateMcpToolsManager::toolIdentifier(server.identifier());
    w.setActivatedTools({identifier});
    QCOMPARE(w.generateListOfActiveTools(), QList<QByteArray>{identifier});
}

void TextAutoGenerateToolsWidgetTest::shouldSelectMcpTools()
{
    FakeMcpServer fakeServer;
    TextAutoGenerateText::TextAutoGenerateManager manager;
    const auto server = fakeServer.mcpServer(u"my server"_s);
    manager.textAutoGenerateTextMcpServerManager()->mcpServerModel()->setMcpServers({server});

    TextAutoGenerateText::TextAutoGenerateToolsWidget w(&manager);
    QToolButton *button = nullptr;
    const auto buttons = w.findChildren<QToolButton *>();
    for (auto b : buttons) {
        if (b->text() == u"my server"_s) {
            button = b;
        }
    }
    QVERIFY(button);
    QVERIFY(button->menu());
    QCOMPARE(button->popupMode(), QToolButton::MenuButtonPopup);

    // Tools are shown when server is connected
    manager.textAutoGenerateMcpToolsManager()->connectServer(server.identifier());
    QTRY_COMPARE(button->menu()->actions().count(), 2);
    const auto actions = button->menu()->actions();
    QCOMPARE(actions.at(0)->text(), u"weather"_s);
    QVERIFY(actions.at(0)->isCheckable());
    QVERIFY(actions.at(0)->isChecked());

    // Unselect one tool: server is selected with other tool
    actions.at(0)->setChecked(false);
    QVERIFY(button->isChecked());
    const QByteArray getTime = TextAutoGenerateText::TextAutoGenerateMcpToolsManager::toolIdentifier(server.identifier(), u"get time"_s);
    QCOMPARE(w.generateListOfActiveTools(), QList<QByteArray>{getTime});

    // All tools selected again
    actions.at(0)->setChecked(true);
    const QByteArray allTools = TextAutoGenerateText::TextAutoGenerateMcpToolsManager::toolIdentifier(server.identifier());
    QCOMPARE(w.generateListOfActiveTools(), QList<QByteArray>{allTools});

    // No tool: server is not selected
    actions.at(0)->setChecked(false);
    actions.at(1)->setChecked(false);
    QVERIFY(!button->isChecked());
    QVERIFY(w.generateListOfActiveTools().isEmpty());
    // Selecting server selects all tools
    button->setChecked(true);
    QCOMPARE(w.generateListOfActiveTools(), QList<QByteArray>{allTools});

    // Restore selection of one tool
    w.setActivatedTools({getTime});
    QVERIFY(button->isChecked());
    QCOMPARE(w.generateListOfActiveTools(), QList<QByteArray>{getTime});
    QVERIFY(!button->menu()->actions().at(0)->isChecked());
    QVERIFY(button->menu()->actions().at(1)->isChecked());
}

#include "moc_textautogeneratetoolswidgettest.cpp"
