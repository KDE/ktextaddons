/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolgetpromptrequestparamstest.h"
#include "impl/mcpprotocolgetpromptrequestparams.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolGetPromptRequestParamsTest)

McpProtocolGetPromptRequestParamsTest::McpProtocolGetPromptRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolGetPromptRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.arguments().has_value());
    QVERIFY(w.name().isEmpty());
}
void McpProtocolGetPromptRequestParamsTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject obj;
    obj["name"_L1] = u"prompt"_s;
    QVERIFY(McpProtocolGetPromptRequestParams::fromJson(obj).isValid());

    QCOMPARE(McpProtocolGetPromptRequestParams::fromJson(QJsonObject()), McpProtocolGetPromptRequestParams());
}

#include "moc_mcpprotocolgetpromptrequestparamstest.cpp"
