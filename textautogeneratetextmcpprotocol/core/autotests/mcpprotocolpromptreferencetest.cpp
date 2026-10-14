/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpromptreferencetest.h"
#include "impl/mcpprotocolpromptreference.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolPromptReferenceTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolPromptReferenceTest::McpProtocolPromptReferenceTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPromptReferenceTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptReference w;
    QVERIFY(!w.title().has_value());
    QVERIFY(w.name().isEmpty());
}

void McpProtocolPromptReferenceTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptReference;
    QJsonObject obj{{"type"_L1, u"ref/prompt"_s}, {"name"_L1, u"review"_s}};
    const McpProtocolPromptReference reference = McpProtocolPromptReference::fromJson(obj);
    QVERIFY(reference.isValid());
    QCOMPARE(McpProtocolPromptReference::toJson(reference), obj);
    QVERIFY(!McpProtocolPromptReference().isValid());
    obj.remove("name"_L1);
    QCOMPARE(McpProtocolPromptReference::fromJson(obj), McpProtocolPromptReference());
}

#include "moc_mcpprotocolpromptreferencetest.cpp"
