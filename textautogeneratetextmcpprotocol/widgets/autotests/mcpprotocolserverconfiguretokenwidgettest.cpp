/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverconfiguretokenwidgettest.h"
#include "server/mcpprotocolserverconfiguretokenwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSignalSpy>
#include <QTest>
QTEST_MAIN(McpProtocolServerConfigureTokenWidgetTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolServerConfigureTokenWidgetTest::McpProtocolServerConfigureTokenWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolServerConfigureTokenWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureTokenWidget w;

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto label = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    auto resultToken = w.findChild<QLabel *>(u"resultToken"_s);
    QVERIFY(resultToken);
    QVERIFY(resultToken->text().isEmpty());
    QCOMPARE(resultToken->textInteractionFlags(), Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);

    auto regenerateTokenButton = w.findChild<QPushButton *>(u"regenerateTokenButton"_s);
    QVERIFY(regenerateTokenButton);
    QVERIFY(!regenerateTokenButton->text().isEmpty());

    auto copyTokenButton = w.findChild<QPushButton *>(u"copyTokenButton"_s);
    QVERIFY(copyTokenButton);
    QVERIFY(!copyTokenButton->text().isEmpty());
    QVERIFY(!copyTokenButton->isEnabled());

    QVERIFY(w.authToken().isEmpty());
}

void McpProtocolServerConfigureTokenWidgetTest::shouldSetAuthToken()
{
    TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureTokenWidget w;
    QSignalSpy spy(&w, &TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureTokenWidget::authTokenChanged);
    auto resultToken = w.findChild<QLabel *>(u"resultToken"_s);
    auto copyTokenButton = w.findChild<QPushButton *>(u"copyTokenButton"_s);

    w.setAuthToken("foo"_ba);
    QCOMPARE(w.authToken(), "foo"_ba);
    QCOMPARE(resultToken->text(), u"foo"_s);
    QVERIFY(copyTokenButton->isEnabled());
    QCOMPARE(spy.count(), 1);

    // Same token => no signal
    w.setAuthToken("foo"_ba);
    QCOMPARE(spy.count(), 1);

    w.setAuthToken({});
    QVERIFY(resultToken->text().isEmpty());
    QVERIFY(!copyTokenButton->isEnabled());
    QCOMPARE(spy.count(), 2);
}

void McpProtocolServerConfigureTokenWidgetTest::shouldGenerateToken()
{
    TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureTokenWidget w;
    QSignalSpy spy(&w, &TextAutoGenerateTextMcpProtocolWidgets::McpProtocolServerConfigureTokenWidget::authTokenChanged);
    auto regenerateTokenButton = w.findChild<QPushButton *>(u"regenerateTokenButton"_s);
    const QString generateText = regenerateTokenButton->text();

    // No token yet => no confirmation
    QTest::mouseClick(regenerateTokenButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(w.authToken().size(), 43);
    QVERIFY(regenerateTokenButton->text() != generateText);
}
#include "moc_mcpprotocolserverconfiguretokenwidgettest.cpp"
