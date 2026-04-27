/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolicontest.h"
#include "mcpprotocolicon.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolIconTest)

McpProtocolIconTest::McpProtocolIconTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolIconTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolIcon w;
    QVERIFY(w.src().isEmpty());
    QVERIFY(!w.mimeType());
    QVERIFY(!w.sizes());
    QVERIFY(!w.theme());
}

#include "moc_mcpprotocolicontest.cpp"
