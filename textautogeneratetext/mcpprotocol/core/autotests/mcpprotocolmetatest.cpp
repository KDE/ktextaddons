/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolmetatest.h"
#include "mcpprotocolmeta.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolMetaTest)

McpProtocolMetaTest::McpProtocolMetaTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolMetaTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolMeta w;
    QVERIFY(!w.meta().has_value());
}
#include "moc_mcpprotocolmetatest.cpp"
