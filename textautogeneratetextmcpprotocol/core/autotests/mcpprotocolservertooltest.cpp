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
#include "moc_mcpprotocolservertooltest.cpp"
