/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolbooleanschematest.h"
#include "mcpprotocolbooleanschema.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolBooleanSchemaTest)

McpProtocolBooleanSchemaTest::McpProtocolBooleanSchemaTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolBooleanSchemaTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolBooleanSchema w;
    QCOMPARE(McpProtocol::McpProtocolBooleanSchema::type(), "boolean");
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(!w.defaultValue().has_value());
}
#include "moc_mcpprotocolbooleanschematest.cpp"
