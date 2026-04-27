/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolbasemetadatatest.h"
#include "mcpprotocolbasemetadata.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolBaseMetadataTest)

McpProtocolBaseMetadataTest::McpProtocolBaseMetadataTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolBaseMetadataTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolBaseMetadata w;
    QVERIFY(!w.title().has_value());
    QVERIFY(w.name().isEmpty());
}
#include "moc_mcpprotocolbasemetadatatest.cpp"
