/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolinitializerequestparamstest.h"
#include "impl/mcpprotocolinitializerequestparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolInitializeRequestParamsTest)

McpProtocolInitializeRequestParamsTest::McpProtocolInitializeRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolInitializeRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequestParams w;
    QVERIFY(!w.meta().has_value());
    // TODO
}
#include "moc_mcpprotocolinitializerequestparamstest.cpp"
