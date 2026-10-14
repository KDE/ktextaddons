/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltoolexecutiontest.h"
#include "impl/mcpprotocoltoolexecution.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolToolExecutionTest)

McpProtocolToolExecutionTest::McpProtocolToolExecutionTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolExecutionTest::shouldhaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolExecution w;
    QVERIFY(!w.taskSupport().has_value());
}

void McpProtocolToolExecutionTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QCOMPARE(McpProtocolToolExecution::fromJson(QJsonObject{{"taskSupport"_L1, u"optional"_s}}).taskSupport(), McpProtocolToolExecution::TaskSupport::Optional);
    // Unknown optional taskSupport is ignored
    const McpProtocolToolExecution execution = McpProtocolToolExecution::fromJson(QJsonObject{{"taskSupport"_L1, u"foo"_s}});
    QVERIFY(!execution.taskSupport().has_value());
    QVERIFY(!McpProtocolToolExecution::toJson(execution).contains("taskSupport"_L1));
}

#include "moc_mcpprotocoltoolexecutiontest.cpp"
