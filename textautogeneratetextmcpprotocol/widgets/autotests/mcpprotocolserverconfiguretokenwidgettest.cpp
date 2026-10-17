/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverconfiguretokenwidgettest.h"
#include "server/mcpprotocolserverconfiguretokenwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
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
}
#include "moc_mcpprotocolserverconfiguretokenwidgettest.cpp"
