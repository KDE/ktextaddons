/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollegacytitledenumschematest.h"
#include "mcpprotocollegacytitledenumschema.h"
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
#include "moc_mcpprotocollegacytitledenumschematest.cpp"
