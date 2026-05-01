/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltoolresultcontenttest.h"
#include "impl/mcpprotocolaudiocontent.h"
#include "impl/mcpprotocolembeddedresource.h"
#include "impl/mcpprotocolimagecontent.h"
#include "impl/mcpprotocolresourcelink.h"
#include "impl/mcpprotocoltextcontent.h"
#include "impl/mcpprotocoltoolresultcontent.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolToolResultContentTest)

McpProtocolToolResultContentTest::McpProtocolToolResultContentTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolResultContentTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolResultContent w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.content().isEmpty());
    QVERIFY(!w.isError().has_value());
    QVERIFY(!w.structuredContent().has_value());
    QVERIFY(w.toolUseId().isEmpty());
}
#include "moc_mcpprotocoltoolresultcontenttest.cpp"
