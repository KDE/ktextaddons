/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcreatemessageresulttest.h"
#include "impl/mcpprotocolcreatemessageresult.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCreateMessageResultTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolCreateMessageResultTest::McpProtocolCreateMessageResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCreateMessageResultTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.model().isEmpty());
    QVERIFY(!w.stopReason().has_value());
    QCOMPARE(w.role(), TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::Unknown);
}

void McpProtocolCreateMessageResultTest::shouldConvertJson()
{
    QJsonObject content;
    content["type"_L1] = u"text"_s;
    content["text"_L1] = u"Hello"_s;

    QJsonObject obj;
    obj["content"_L1] = content;
    obj["model"_L1] = u"my-model"_s;
    obj["role"_L1] = u"assistant"_s;
    obj["stopReason"_L1] = u"endTurn"_s;

    const auto result = TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageResult::fromJson(obj);
    QCOMPARE(result.model(), u"my-model"_s);
    QCOMPARE(result.role(), TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::Assistant);
    QCOMPARE(result.stopReason(), u"endTurn"_s);
    const auto resultContent = result.content();
    const auto textContent = std::get_if<TextAutoGenerateTextMcpProtocolCore::McpProtocolTextContent>(&resultContent);
    QVERIFY(textContent);
    QCOMPARE(textContent->text(), u"Hello"_s);

    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageResult::toJson(result), obj);
}

#include "moc_mcpprotocolcreatemessageresulttest.cpp"
