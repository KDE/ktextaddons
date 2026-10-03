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

#include "moc_mcpprotocoltooltest.cpp"
