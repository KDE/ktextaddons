/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolroottest.h"
#include "mcpprotocolroot.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolRootTest)

McpProtocolRootTest::McpProtocolRootTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolRootTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolRoot w;
    QVERIFY(w.uri().isEmpty());
    QVERIFY(!w.name().has_value());
    QVERIFY(!w.meta().has_value());
}
#include "moc_mcpprotocolroottest.cpp"
