/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolgetpromptresulttest.h"
#include "impl/mcpprotocolgetpromptresult.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolGetPromptResultTest)

McpProtocolGetPromptResultTest::McpProtocolGetPromptResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolGetPromptResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.description().has_value());
    QVERIFY(w.messages().isEmpty());
}
void McpProtocolGetPromptResultTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QCOMPARE(McpProtocolGetPromptResult::fromJson(QJsonObject()), McpProtocolGetPromptResult());

    QJsonObject content;
    content["type"_L1] = u"text"_s;
    content["text"_L1] = u"Hello"_s;
    QJsonObject message;
    message["role"_L1] = u"user"_s;
    message["content"_L1] = content;
    QJsonObject invalidMessage = message;
    invalidMessage["role"_L1] = u"foo"_s;
    QJsonObject obj;
    obj["messages"_L1] = QJsonArray{invalidMessage, message};
    // Invalid message is skipped
    QCOMPARE(McpProtocolGetPromptResult::fromJson(obj).messages().count(), 1);
}

#include "moc_mcpprotocolgetpromptresulttest.cpp"
