/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolnumberschematest.h"
#include "mcpprotocolnumberschema.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolNumberSchemaTest)

McpProtocolNumberSchemaTest::McpProtocolNumberSchemaTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolNumberSchemaTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema w;
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(!w.defaultValue().has_value());
    QVERIFY(!w.maximum().has_value());
    QVERIFY(!w.minimum().has_value());
    QCOMPARE(w.type(), TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema::Type::Unknown);
}
#include "moc_mcpprotocolnumberschematest.cpp"
