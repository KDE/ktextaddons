/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollisttasksrequesttest.h"
#include "impl/mcpprotocollisttasksrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListTasksRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolListTasksRequestTest::McpProtocolListTasksRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListTasksRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListTasksRequest w;
    QCOMPARE(w.type(), "tasks/list"_ba);
    QVERIFY(!w.params().has_value());
}
#include "moc_mcpprotocollisttasksrequesttest.cpp"
