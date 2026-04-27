/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpaginatedrequestparamstest.h"
#include "mcpprotocolpaginatedrequestparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolPaginatedRequestParamsTest)

McpProtocolPaginatedRequestParamsTest::McpProtocolPaginatedRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPaginatedRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.cursor().isEmpty());
}
#include "moc_mcpprotocolpaginatedrequestparamstest.cpp"
