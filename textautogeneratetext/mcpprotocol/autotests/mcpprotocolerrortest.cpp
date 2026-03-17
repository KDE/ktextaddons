/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolerrortest.h"
#include "mcpprotocolerror.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolErrorTest)

McpProtocolErrorTest::McpProtocolErrorTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolErrorTest::shouldhaveDefaultValues()
{
    const McpProtocol::McpProtocolError w;
    QCOMPARE(w.code(), 0);
    QVERIFY(w.message().isEmpty());
    QVERIFY(!w.data().has_value());
}

#include "moc_mcpprotocolerrortest.cpp"
