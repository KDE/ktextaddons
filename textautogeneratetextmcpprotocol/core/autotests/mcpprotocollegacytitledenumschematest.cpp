/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollegacytitledenumschematest.h"
#include "impl/mcpprotocollegacytitledenumschema.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolLegacyTitledEnumSchemaTest)

McpProtocolLegacyTitledEnumSchemaTest::McpProtocolLegacyTitledEnumSchemaTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolLegacyTitledEnumSchemaTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolLegacyTitledEnumSchema w;
    // TODO
}

void McpProtocolLegacyTitledEnumSchemaTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolLegacyTitledEnumSchema;
    using namespace Qt::Literals::StringLiterals;
    QJsonObject valid;
    valid["type"_L1] = u"string"_s;
    valid["enum"_L1] = QJsonArray{u"a"_s, u"b"_s};
    const McpProtocolLegacyTitledEnumSchema schema = McpProtocolLegacyTitledEnumSchema::fromJson(valid);
    QCOMPARE(schema.enums(), QStringList({u"a"_s, u"b"_s}));

    QJsonObject obj = valid;
    obj.remove(u"enum"_s);
    QCOMPARE(McpProtocolLegacyTitledEnumSchema::fromJson(obj), McpProtocolLegacyTitledEnumSchema());
}

#include "moc_mcpprotocollegacytitledenumschematest.cpp"
