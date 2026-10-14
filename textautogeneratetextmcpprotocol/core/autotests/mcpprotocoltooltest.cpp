/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltooltest.h"
#include "impl/mcpprotocoltool.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolToolTest)

namespace
{
QJsonObject schemaWithDefs()
{
    const QJsonObject address{{"type"_L1, u"object"_s}, {"properties"_L1, QJsonObject{{"city"_L1, QJsonObject{{"type"_L1, u"string"_s}}}}}};
    return QJsonObject{
        {"type"_L1, u"object"_s},
        {"properties"_L1, QJsonObject{{"address"_L1, QJsonObject{{"$ref"_L1, u"#/$defs/Address"_s}}}}},
        {"required"_L1, QJsonArray{u"address"_s}},
        {"$defs"_L1, QJsonObject{{"Address"_L1, address}}},
        {"additionalProperties"_L1, false},
        {"description"_L1, u"Tool input"_s},
    };
}
}

McpProtocolToolTest::McpProtocolToolTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolTest::shouldKeepAllInputSchemaKeywords()
{
    const QJsonObject obj = schemaWithDefs();
    const auto schema = TextAutoGenerateTextMcpProtocolCore::McpProtocolTool::InputSchema::fromJson(obj);
    QCOMPARE(schema.additionalProperties().value("additionalProperties"_L1), QJsonValue(false));
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolTool::InputSchema::toJson(schema), obj);
}

void McpProtocolToolTest::shouldKeepAllOutputSchemaKeywords()
{
    const QJsonObject obj = schemaWithDefs();
    const auto schema = TextAutoGenerateTextMcpProtocolCore::McpProtocolTool::OutputSchema::fromJson(obj);
    QVERIFY(schema.additionalProperties().contains("$defs"_L1));
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolTool::OutputSchema::toJson(schema), obj);
}

void McpProtocolToolTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    const QJsonObject obj{{"name"_L1, u"foo"_s}, {"inputSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}}}};
    QVERIFY(McpProtocolTool::fromJson(obj).isValid());
    // Missing name
    QJsonObject withoutName = obj;
    withoutName.remove("name"_L1);
    QCOMPARE(McpProtocolTool::fromJson(withoutName), McpProtocolTool());
    // Missing inputSchema
    QJsonObject withoutInputSchema = obj;
    withoutInputSchema.remove("inputSchema"_L1);
    QCOMPARE(McpProtocolTool::fromJson(withoutInputSchema), McpProtocolTool());
    // Invalid inputSchema
    QJsonObject invalidInputSchema = obj;
    invalidInputSchema["inputSchema"_L1] = QJsonObject{{"type"_L1, u"string"_s}};
    QCOMPARE(McpProtocolTool::fromJson(invalidInputSchema), McpProtocolTool());
    // Invalid icons are skipped
    QJsonObject withIcons = obj;
    withIcons["icons"_L1] = QJsonArray{QJsonObject{{"src"_L1, u"https://example.com/icon.png"_s}}, QJsonObject{{"mimeType"_L1, u"image/png"_s}}};
    QCOMPARE(McpProtocolTool::fromJson(withIcons).icons()->count(), 1);
}

#include "moc_mcpprotocoltooltest.cpp"
