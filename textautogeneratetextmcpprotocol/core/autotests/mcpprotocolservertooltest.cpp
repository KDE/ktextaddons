/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolservertooltest.h"
#include "server/mcpprotocolservertool.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolServerToolTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

McpProtocolServerToolTest::McpProtocolServerToolTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolServerToolTest::shouldCreateSchemaProperty()
{
    const QJsonObject property = McpProtocolServerTool::schemaProperty(u"string"_s, u"Name"_s);
    QCOMPARE(property, (QJsonObject{{"type"_L1, u"string"_s}, {"description"_L1, u"Name"_s}}));
}

void McpProtocolServerToolTest::shouldCreateSchemaEnumProperty()
{
    const QJsonObject property = McpProtocolServerTool::schemaEnumProperty({u"location"_s, u"birthday"_s}, u"Field"_s);
    QCOMPARE(property, (QJsonObject{{"type"_L1, u"string"_s}, {"enum"_L1, QJsonArray{u"location"_s, u"birthday"_s}}, {"description"_L1, u"Field"_s}}));

    const QJsonObject withoutDescription = McpProtocolServerTool::schemaEnumProperty({u"location"_s}, {});
    QVERIFY(!withoutDescription.contains("description"_L1));
}

void McpProtocolServerToolTest::shouldCreateSchemaArrayProperty()
{
    const QJsonObject items = McpProtocolServerTool::schemaEnumProperty({u"location"_s, u"birthday"_s}, {});
    const QJsonObject property = McpProtocolServerTool::schemaArrayProperty(items, u"Fields"_s);
    QCOMPARE(property, (QJsonObject{{"type"_L1, u"array"_s}, {"items"_L1, items}, {"description"_L1, u"Fields"_s}}));

    const QJsonObject withoutDescription = McpProtocolServerTool::schemaArrayProperty(items, {});
    QVERIFY(!withoutDescription.contains("description"_L1));
}

void McpProtocolServerToolTest::shouldCreateToolWithAnnotations()
{
    const McpProtocolTool tool = McpProtocolServerTool::createTool(u"delete_item"_s,
                                                                   u"Delete Item"_s,
                                                                   u"Delete an item"_s,
                                                                   McpProtocolServerTool::ToolKind::Destructive,
                                                                   {{u"id"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Item"_s)}},
                                                                   {u"id"_s});
    QCOMPARE(tool.name(), u"delete_item"_s);
    QCOMPARE(tool.title(), u"Delete Item"_s);
    QCOMPARE(tool.description(), u"Delete an item"_s);
    QCOMPARE(tool.inputSchema().mRequired, QStringList{u"id"_s});
    QVERIFY(tool.inputSchema().mProperties->contains(u"id"_s));
    QVERIFY(tool.annotations().has_value());
    QCOMPARE(tool.annotations()->destructiveHint(), true);
}

void McpProtocolServerToolTest::shouldCreateAnnotations_data()
{
    QTest::addColumn<McpProtocolServerTool::ToolKind>("kind");
    QTest::addColumn<bool>("readOnly");
    QTest::addColumn<std::optional<bool>>("destructive");
    QTest::newRow("readonly") << McpProtocolServerTool::ToolKind::ReadOnly << true << std::optional<bool>{};
    QTest::newRow("modify") << McpProtocolServerTool::ToolKind::Modify << false << std::optional<bool>{false};
    QTest::newRow("destructive") << McpProtocolServerTool::ToolKind::Destructive << false << std::optional<bool>{true};
}

void McpProtocolServerToolTest::shouldCreateAnnotations()
{
    QFETCH(McpProtocolServerTool::ToolKind, kind);
    QFETCH(bool, readOnly);
    QFETCH(std::optional<bool>, destructive);
    const McpProtocolToolAnnotations annotations = McpProtocolServerTool::annotations(kind);
    QCOMPARE(annotations.readOnlyHint(), readOnly);
    QCOMPARE(annotations.destructiveHint(), destructive);
    QCOMPARE(annotations.openWorldHint(), false);
    QVERIFY(!annotations.idempotentHint().has_value());
}

#include "moc_mcpprotocolservertooltest.cpp"
