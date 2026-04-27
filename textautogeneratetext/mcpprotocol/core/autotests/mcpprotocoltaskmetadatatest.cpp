/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltaskmetadatatest.h"
#include "mcpprotocoltaskmetadata.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolTaskMetadataTest)

McpProtocolTaskMetadataTest::McpProtocolTaskMetadataTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolTaskMetadataTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskMetadata w;
    QVERIFY(!w.ttl().has_value());
}
#include "moc_mcpprotocoltaskmetadatatest.cpp"
