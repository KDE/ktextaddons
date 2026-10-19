/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverconfigurewidgettest.h"
#include "server/mcpprotocolserverconfiguretokenwidget.h"
#include "server/mcpprotocolserverconfigurewidget.h"
#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(McpProtocolServerConfigureWidgetTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolWidgets;
McpProtocolServerConfigureWidgetTest::McpProtocolServerConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolServerConfigureWidgetTest::shouldHaveDefaultValues()
{
    const McpProtocolServerConfigureWidget w;

    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mServerUrlLineEdit = w.findChild<QLineEdit *>(u"mServerUrlLineEdit"_s);
    QVERIFY(mServerUrlLineEdit);
    QVERIFY(mServerUrlLineEdit->text().isEmpty());
    QVERIFY(!mServerUrlLineEdit->placeholderText().isEmpty());
    QVERIFY(mServerUrlLineEdit->isClearButtonEnabled());

    auto mRequireAuthenticationCheckBox = w.findChild<QCheckBox *>(u"mRequireAuthenticationCheckBox"_s);
    QVERIFY(mRequireAuthenticationCheckBox);
    QVERIFY(!mRequireAuthenticationCheckBox->text().isEmpty());
    QVERIFY(!mRequireAuthenticationCheckBox->isChecked());

    auto mTokenWidget = w.findChild<McpProtocolServerConfigureTokenWidget *>(u"mTokenWidget"_s);
    QVERIFY(mTokenWidget);
    QVERIFY(!mTokenWidget->isEnabled());
    QVERIFY(mTokenWidget->authToken().isEmpty());

    QVERIFY(!w.isValid());
}

void McpProtocolServerConfigureWidgetTest::shouldGenerateTokenWhenRequireAuthentication()
{
    McpProtocolServerConfigureWidget w;
    auto mServerUrlLineEdit = w.findChild<QLineEdit *>(u"mServerUrlLineEdit"_s);
    auto mRequireAuthenticationCheckBox = w.findChild<QCheckBox *>(u"mRequireAuthenticationCheckBox"_s);
    auto mTokenWidget = w.findChild<McpProtocolServerConfigureTokenWidget *>(u"mTokenWidget"_s);

    mServerUrlLineEdit->setText(u"http://127.0.0.1:8765/mcp"_s);
    QVERIFY(w.isValid());
    QVERIFY(w.settings().authToken().isEmpty());

    mRequireAuthenticationCheckBox->setChecked(true);
    QVERIFY(mTokenWidget->isEnabled());
    const QByteArray token = mTokenWidget->authToken();
    QVERIFY(!token.isEmpty());
    QCOMPARE(w.settings().authToken(), token);
    QVERIFY(w.isValid());

    // Unchecked => no token in settings, but keep it if user checks again
    mRequireAuthenticationCheckBox->setChecked(false);
    QVERIFY(!mTokenWidget->isEnabled());
    QVERIFY(w.settings().authToken().isEmpty());
    mRequireAuthenticationCheckBox->setChecked(true);
    QCOMPARE(w.settings().authToken(), token);
}

void McpProtocolServerConfigureWidgetTest::shouldLoadSettings()
{
    McpProtocolServerConfigureWidget w;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(QUrl(u"http://127.0.0.1:9000/mcp"_s));
    settings.setAuthToken("foo"_ba);
    w.setSettings(settings);

    auto mRequireAuthenticationCheckBox = w.findChild<QCheckBox *>(u"mRequireAuthenticationCheckBox"_s);
    QVERIFY(mRequireAuthenticationCheckBox->isChecked());
    // Loaded token must not be regenerated
    QCOMPARE(w.settings().authToken(), "foo"_ba);
    QCOMPARE(w.settings().serverUrl(), settings.serverUrl());

    settings.setAuthToken({});
    w.setSettings(settings);
    QVERIFY(!mRequireAuthenticationCheckBox->isChecked());
    QVERIFY(w.settings().authToken().isEmpty());
}

void McpProtocolServerConfigureWidgetTest::shouldValidateUrl_data()
{
    QTest::addColumn<QString>("url");
    QTest::addColumn<bool>("valid");
    QTest::newRow("empty") << QString() << false;
    QTest::newRow("no-port") << u"http://127.0.0.1/mcp"_s << false;
    QTest::newRow("https") << u"https://127.0.0.1:8765/mcp"_s << false;
    QTest::newRow("valid") << u"http://127.0.0.1:8765/mcp"_s << true;
    QTest::newRow("localhost") << u"http://localhost:8765/mcp"_s << true;
}

void McpProtocolServerConfigureWidgetTest::shouldValidateUrl()
{
    QFETCH(QString, url);
    QFETCH(bool, valid);
    McpProtocolServerConfigureWidget w;
    w.findChild<QLineEdit *>(u"mServerUrlLineEdit"_s)->setText(url);
    QCOMPARE(w.isValid(), valid);
}
#include "moc_mcpprotocolserverconfigurewidgettest.cpp"
