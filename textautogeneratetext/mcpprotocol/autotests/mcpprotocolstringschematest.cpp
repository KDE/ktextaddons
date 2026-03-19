/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolstringschematest.h"
#include "mcpprotocolstringschema.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolStringSchemaTest)

McpProtocolStringSchemaTest::McpProtocolStringSchemaTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolStringSchemaTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolStringSchema w;
    QCOMPARE(McpProtocol::McpProtocolStringSchema::type(), "string");
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(!w.defaultValue().has_value());
    QVERIFY(!w.format().has_value());
    QVERIFY(!w.minLength().has_value());
    QVERIFY(!w.maxLength().has_value());
}
#include "moc_mcpprotocolstringschematest.cpp"
