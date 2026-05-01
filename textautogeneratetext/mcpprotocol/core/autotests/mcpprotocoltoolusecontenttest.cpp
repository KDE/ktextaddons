/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltoolusecontenttest.h"
#include "impl/mcpprotocolaudiocontent.h"
#include "impl/mcpprotocolembeddedresource.h"
#include "impl/mcpprotocolimagecontent.h"
#include "impl/mcpprotocolresourcelink.h"
#include "impl/mcpprotocoltextcontent.h"
#include "impl/mcpprotocoltoolusecontent.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolToolUseContentTest)

McpProtocolToolUseContentTest::McpProtocolToolUseContentTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolUseContentTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolUseContent w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.input().isEmpty());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.id().isEmpty());
}
#include "moc_mcpprotocoltoolusecontenttest.cpp"
