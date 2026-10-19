/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "addmcpsseserverwidgettest.h"
#include "client/addmcpsseserverwidget.h"
#include "client/addmcpstreamablehttpserverheaderwidget.h"
#include <KPasswordLineEdit>
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(AddMcpSseServerWidgetTest)

AddMcpSseServerWidgetTest::AddMcpSseServerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AddMcpSseServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpSseServerWidget w;
    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mServerUrlLineEdit = w.findChild<QLineEdit *>(u"mServerUrlLineEdit"_s);
    QVERIFY(mServerUrlLineEdit);
    QVERIFY(mServerUrlLineEdit->text().isEmpty());
    QVERIFY(mServerUrlLineEdit->isClearButtonEnabled());

    auto mHttpServerHeaderWidget = w.findChild<TextAutoGenerateTextMcpProtocolWidgets::AddMcpStreamableHttpServerHeaderWidget *>(u"mHttpServerHeaderWidget"_s);
    QVERIFY(mHttpServerHeaderWidget);

    auto mAuthTokenLineEdit = w.findChild<KPasswordLineEdit *>(u"mAuthTokenLineEdit"_s);
    QVERIFY(mAuthTokenLineEdit);
    QVERIFY(mAuthTokenLineEdit->password().isEmpty());
    QVERIFY(!mAuthTokenLineEdit->toolTip().isEmpty());

    QVERIFY(!w.isValid());
}

void AddMcpSseServerWidgetTest::shouldLoadSaveAuthToken()
{
    TextAutoGenerateTextMcpProtocolWidgets::AddMcpSseServerWidget w;
    TextAutoGenerateTextMcpProtocolCore::McpServer server;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(QUrl(u"https://example.com/sse"_s));
    settings.setAuthToken("foo"_ba);
    server.setSettings(settings);
    w.loadSettings(server);

    auto mAuthTokenLineEdit = w.findChild<KPasswordLineEdit *>(u"mAuthTokenLineEdit"_s);
    QCOMPARE(mAuthTokenLineEdit->password(), u"foo"_s);

    mAuthTokenLineEdit->setPassword(u" bla "_s);
    TextAutoGenerateTextMcpProtocolCore::McpServer savedServer;
    w.saveSettings(savedServer);
    QCOMPARE(savedServer.settings().authToken(), "bla"_ba);
    QCOMPARE(savedServer.settings().serverUrl(), QUrl(u"https://example.com/sse"_s));
}

#include "moc_addmcpsseserverwidgettest.cpp"
