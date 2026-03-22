/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolunsubscriberequestparamstest.h"
#include "mcpprotocolunsubscriberequestparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolUnsubscribeRequestParamsTest)

McpProtocolUnsubscribeRequestParamsTest::McpProtocolUnsubscribeRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolUnsubscribeRequestParamsTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolUnsubscribeRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.uri().isEmpty());
}
#include "moc_mcpprotocolunsubscriberequestparamstest.cpp"
