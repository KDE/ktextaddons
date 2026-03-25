/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsetlevelrequestparamstest.h"
#include "mcpprotocolsetlevelrequestparams.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSetLevelRequestParamsTest)

McpProtocolSetLevelRequestParamsTest::McpProtocolSetLevelRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSetLevelRequestParamsTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolSetLevelRequestParams w;
    QVERIFY(!w.meta().has_value());
    QCOMPARE(w.level(), McpProtocol::McpProtocolUtils::LoggingLevel::Unknown);
}
#include "moc_mcpprotocolsetlevelrequestparamstest.cpp"
