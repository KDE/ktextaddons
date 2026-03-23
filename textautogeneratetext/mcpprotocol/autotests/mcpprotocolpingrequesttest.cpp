/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpingrequesttest.h"
#include "mcpprotocolpingrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolPingRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolPingRequestTest::McpProtocolPingRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPingRequestTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolPingRequest w;
    QCOMPARE(w.type(), "ping"_ba);
    QVERIFY(!w.params().has_value());
    // TODO
}
#include "moc_mcpprotocolpingrequesttest.cpp"
