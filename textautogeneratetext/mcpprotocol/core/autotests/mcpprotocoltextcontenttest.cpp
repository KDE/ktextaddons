/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltextcontenttest.h"
#include "mcpprotocoltextcontent.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolTextContentTest)

McpProtocolTextContentTest::McpProtocolTextContentTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolTextContentTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolTextContent w;
    QVERIFY(w.text().isEmpty());
    QVERIFY(!w.annotations().has_value());
    QVERIFY(!w.meta().has_value());
}
#include "moc_mcpprotocoltextcontenttest.cpp"
