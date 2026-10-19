/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverutilstest.h"
#include <QStandardPaths>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerUtils>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
QTEST_GUILESS_MAIN(McpProtocolServerUtilsTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolServerUtilsTest::McpProtocolServerUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolServerUtilsTest::initTestCase()
{
    QStandardPaths::setTestModeEnabled(true);
}

void McpProtocolServerUtilsTest::shouldHaveDefaultValues()
{
    const QUrl url = McpProtocolServerUtils::defaultServerUrl();
    QCOMPARE(url.scheme(), u"http"_s);
    QVERIFY(url.port() > 0);
    QVERIFY(!McpProtocolServerUtils::authTokenIdentifier().isEmpty());
    QCOMPARE(McpProtocolServerUtils::generateAuthToken().size(), 43);
}

void McpProtocolServerUtilsTest::shouldSaveAndLoadSettings()
{
    // Without token: no access to system wallet, callback is called synchronously
    McpProtocolSettings settings;
    settings.setServerUrl(QUrl(u"http://127.0.0.1:9000/mcp"_s));
    McpProtocolServerUtils::saveSettings(settings);

    bool called = false;
    McpProtocolServerUtils::loadSettings(this, [&called, &settings](const McpProtocolSettings &result) {
        called = true;
        QCOMPARE(result.serverUrl(), settings.serverUrl());
        QVERIFY(result.authToken().isEmpty());
    });
    QVERIFY(called);
}

#include "moc_mcpprotocolserverutilstest.cpp"
