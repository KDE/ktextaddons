/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolnumberschematest.h"
#include "impl/mcpprotocolnumberschema.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
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

void McpProtocolNumberSchemaTest::shouldLoadAndSaveDecimalValues()
{
    QJsonObject obj;
    obj["type"_L1] = u"number"_s;
    obj["default"_L1] = 0.25;
    obj["minimum"_L1] = 0.5;
    obj["maximum"_L1] = 1.5;
    const auto schema = TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema::fromJson(obj);
    QCOMPARE(schema.type(), TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema::Type::Number);
    QCOMPARE(*schema.defaultValue(), 0.25);
    QCOMPARE(*schema.minimum(), 0.5);
    QCOMPARE(*schema.maximum(), 1.5);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema::toJson(schema), obj);

    QJsonObject invalid;
    invalid["type"_L1] = u"foo"_s;
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema::fromJson(invalid).type(),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolNumberSchema::Type::Unknown);
}

#include "moc_mcpprotocolnumberschematest.cpp"
