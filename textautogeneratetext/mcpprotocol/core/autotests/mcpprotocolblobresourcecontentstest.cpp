/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolblobresourcecontentstest.h"
#include "mcpprotocolblobresourcecontents.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolBlobResourceContentsTest)

McpProtocolBlobResourceContentsTest::McpProtocolBlobResourceContentsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolBlobResourceContentsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolBlobResourceContents w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.mimeType().has_value());
    QVERIFY(w.uri().isEmpty());
    QVERIFY(w.blob().isEmpty());
}
#include "moc_mcpprotocolblobresourcecontentstest.cpp"
