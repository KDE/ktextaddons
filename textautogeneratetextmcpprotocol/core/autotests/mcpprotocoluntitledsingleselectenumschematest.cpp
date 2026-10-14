/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoluntitledsingleselectenumschematest.h"
#include "impl/mcpprotocoluntitledsingleselectenumschema.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolUntitledSingleSelectEnumSchemaTest)

McpProtocolUntitledSingleSelectEnumSchemaTest::McpProtocolUntitledSingleSelectEnumSchemaTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolUntitledSingleSelectEnumSchemaTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolUntitledSingleSelectEnumSchema w;
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUntitledSingleSelectEnumSchema::type(), "string");
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(!w.defaultValue().has_value());
    QVERIFY(w.enums().isEmpty());
}

void McpProtocolUntitledSingleSelectEnumSchemaTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    const QJsonObject obj{{"type"_L1, u"string"_s}, {"enum"_L1, QJsonArray{u"a"_s, u"b"_s}}};
    const auto schema = McpProtocolUntitledSingleSelectEnumSchema::fromJson(obj);
    QCOMPARE(schema.enums(), QStringList({u"a"_s, u"b"_s}));
    QCOMPARE(McpProtocolUntitledSingleSelectEnumSchema::toJson(schema), obj);
    // Missing enum
    QCOMPARE(McpProtocolUntitledSingleSelectEnumSchema::fromJson(QJsonObject{{"type"_L1, u"string"_s}}), McpProtocolUntitledSingleSelectEnumSchema());
}

#include "moc_mcpprotocoluntitledsingleselectenumschematest.cpp"
