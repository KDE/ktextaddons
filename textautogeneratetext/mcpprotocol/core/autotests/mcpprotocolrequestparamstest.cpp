/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolrequestparamstest.h"
#include "mcpprotocolrequestparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolRequestParamsTest)

McpProtocolRequestParamsTest::McpProtocolRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.uri().isEmpty());
}
#include "moc_mcpprotocolrequestparamstest.cpp"
