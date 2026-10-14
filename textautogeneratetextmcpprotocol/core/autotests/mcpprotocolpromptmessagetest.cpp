/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpromptmessagetest.h"
#include "impl/mcpprotocolpromptmessage.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolPromptMessageTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolPromptMessageTest::McpProtocolPromptMessageTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPromptMessageTest::shouldhaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptMessage w;
    QCOMPARE(w.role(), TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::Unknown);
}

void McpProtocolPromptMessageTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptMessage;
    const QJsonObject content{{"type"_L1, u"text"_s}, {"text"_L1, u"Hello"_s}};
    QJsonObject obj{{"role"_L1, u"user"_s}, {"content"_L1, content}};
    QVERIFY(McpProtocolPromptMessage::fromJson(obj).isValid());
    QVERIFY(!McpProtocolPromptMessage().isValid());

    obj["role"_L1] = u"foo"_s;
    QCOMPARE(McpProtocolPromptMessage::fromJson(obj), McpProtocolPromptMessage());
    obj.remove("role"_L1);
    QCOMPARE(McpProtocolPromptMessage::fromJson(obj), McpProtocolPromptMessage());

    const QJsonObject missingContent{{"role"_L1, u"user"_s}};
    QCOMPARE(McpProtocolPromptMessage::fromJson(missingContent), McpProtocolPromptMessage());
}

#include "moc_mcpprotocolpromptmessagetest.cpp"
