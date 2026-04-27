/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoluntitledsingleselectenumschematest.h"
#include "mcpprotocoluntitledsingleselectenumschema.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolUntitledSingleSelectEnumSchemaTest)

McpProtocolUntitledSingleSelectEnumSchemaTest::McpProtocolUntitledSingleSelectEnumSchemaTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolUntitledSingleSelectEnumSchemaTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolUntitledSingleSelectEnumSchema w;
    QCOMPARE(McpProtocol::McpProtocolUntitledSingleSelectEnumSchema::type(), "string");
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(!w.defaultValue().has_value());
    QVERIFY(w.enums().isEmpty());
}
#include "moc_mcpprotocoluntitledsingleselectenumschematest.cpp"
