/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcreatetaskresulttest.h"
#include "impl/mcpprotocolcreatetaskresult.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCreateTaskResultTest)

McpProtocolCreateTaskResultTest::McpProtocolCreateTaskResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCreateTaskResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateTaskResult w;
    QVERIFY(!w.meta().has_value());
    // TODO QVERIFY(w.task().isEmpty());
}
void McpProtocolCreateTaskResultTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QCOMPARE(McpProtocolCreateTaskResult::fromJson(QJsonObject()), McpProtocolCreateTaskResult());

    QJsonObject obj;
    obj["task"_L1] = QJsonObject();
    QCOMPARE(McpProtocolCreateTaskResult::fromJson(obj), McpProtocolCreateTaskResult());
}

#include "moc_mcpprotocolcreatetaskresulttest.cpp"
