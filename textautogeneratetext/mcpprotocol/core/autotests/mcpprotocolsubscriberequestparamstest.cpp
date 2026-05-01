/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsubscriberequestparamstest.h"
#include "impl/mcpprotocolsubscriberequestparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSubscribeRequestParamsTest)

McpProtocolSubscribeRequestParamsTest::McpProtocolSubscribeRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSubscribeRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscribeRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.uri().isEmpty());
}
#include "moc_mcpprotocolsubscriberequestparamstest.cpp"
