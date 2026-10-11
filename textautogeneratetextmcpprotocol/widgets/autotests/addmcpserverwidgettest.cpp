/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpserverwidgettest.h"
#include "common/selecttypecombobox.h"
#include "server/addmcpserverrootswidget.h"
#include "server/addmcpserverwidget.h"
#include <KIconButton>
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(AddMcpServerWidgetTest)
using namespace Qt::Literals::StringLiterals;
AddMcpServerWidgetTest::AddMcpServerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AddMcpServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpServerWidget w;
    auto mServerNameLineEdit = w.findChild<QLineEdit *>(u"mServerNameLineEdit"_s);
    QVERIFY(mServerNameLineEdit);
    QVERIFY(mServerNameLineEdit->text().isEmpty());
    QVERIFY(mServerNameLineEdit->isClearButtonEnabled());

    auto mSelectTypeComboBox = w.findChild<TextAutoGenerateTextMcpProtocolWidgets::SelectTypeComboBox *>(u"mSelectTypeComboBox"_s);
    QVERIFY(mSelectTypeComboBox);

    auto mAddMcpServerRootsWidget = w.findChild<TextAutoGenerateTextMcpProtocolWidgets::AddMcpServerRootsWidget *>(u"mAddMcpServerRootsWidget"_s);
    QVERIFY(mAddMcpServerRootsWidget);
    QVERIFY(mAddMcpServerRootsWidget->roots().isEmpty());

    auto mIconName = w.findChild<KIconButton *>(u"mIconName"_s);
    QVERIFY(mIconName);
}

void AddMcpServerWidgetTest::shouldSaveRoots()
{
    TextAutoGenerateTextMcpProtocolWidgets::AddMcpServerWidget w;
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    server.setName(u"test"_s);
    server.createUniqueIdentifier();
    server.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio);
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setCommand(u"command"_s);
    settings.setRoots({u"/home/user/project"_s});
    server.setSettings(settings);
    w.setServerInfo(server);

    auto mAddMcpServerRootsWidget = w.findChild<TextAutoGenerateTextMcpProtocolWidgets::AddMcpServerRootsWidget *>(u"mAddMcpServerRootsWidget"_s);
    QCOMPARE(mAddMcpServerRootsWidget->roots(), QStringList({u"/home/user/project"_s}));
    QCOMPARE(w.serverInfo(), server);

    mAddMcpServerRootsWidget->setRoots({u"/tmp"_s});
    QCOMPARE(w.serverInfo().settings().roots(), QStringList({u"/tmp"_s}));
}

#include "moc_addmcpserverwidgettest.cpp"
