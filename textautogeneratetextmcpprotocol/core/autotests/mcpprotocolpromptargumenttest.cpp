/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpromptargumenttest.h"
#include "impl/mcpprotocolpromptargument.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolPromptArgumentTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolPromptArgumentTest::McpProtocolPromptArgumentTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPromptArgumentTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptArgument w;
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.required().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(w.name().isEmpty());
}

void McpProtocolPromptArgumentTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolPromptArgument;
    const QJsonObject obj{{"name"_L1, u"city"_s}};
    const McpProtocolPromptArgument argument = McpProtocolPromptArgument::fromJson(obj);
    QVERIFY(argument.isValid());
    QCOMPARE(McpProtocolPromptArgument::toJson(argument), obj);
    QVERIFY(!McpProtocolPromptArgument().isValid());
    QCOMPARE(McpProtocolPromptArgument::fromJson(QJsonObject()), McpProtocolPromptArgument());
    QCOMPARE(McpProtocolPromptArgument::fromJson(QJsonObject{{"name"_L1, 1}}), McpProtocolPromptArgument());
}

#include "moc_mcpprotocolpromptargumenttest.cpp"
