/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltextresourcecontentstest.h"
#include "mcpprotocoltextresourcecontents.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolTextResourceContentsTest)

McpProtocolTextResourceContentsTest::McpProtocolTextResourceContentsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolTextResourceContentsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolTextResourceContents w;
    QVERIFY(w.text().isEmpty());
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.mimeType().has_value());
    QVERIFY(w.uri().isEmpty());
}
#include "moc_mcpprotocoltextresourcecontentstest.cpp"
