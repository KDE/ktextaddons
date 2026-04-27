/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolreadresourcerequestparamstest.h"
#include "mcpprotocolreadresourcerequestparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolReadResourceRequestParamsTest)

McpProtocolReadResourceRequestParamsTest::McpProtocolReadResourceRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolReadResourceRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.uri().isEmpty());
}
#include "moc_mcpprotocolreadresourcerequestparamstest.cpp"
