/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistresourcesresulttest.h"
#include "mcpprotocollistresourcesresult.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListResourcesResultTest)

McpProtocolListResourcesResultTest::McpProtocolListResourcesResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListResourcesResultTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolListResourcesResult w;
    QVERIFY(!w.nextCursor().has_value());
    QVERIFY(!w.meta().has_value());
}
#include "moc_mcpprotocollistresourcesresulttest.cpp"
