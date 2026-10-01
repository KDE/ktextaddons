/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolrequestparamstest.h"
#include "impl/mcpprotocolrequestparams.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolRequestParamsTest)

McpProtocolRequestParamsTest::McpProtocolRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams w;
    QVERIFY(!w.meta().has_value());
}

void McpProtocolRequestParamsTest::shouldLoadAndSaveRequestParams()
{
    QVERIFY(TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams::toJson({}).isEmpty());

    QJsonObject obj;
    obj["_meta"_L1] = QJsonObject{{"progressToken"_L1, 42}};
    const auto params = TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams::fromJson(obj);
    QVERIFY(params.meta().has_value());
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolRequestParams::toJson(params), obj);
}

#include "moc_mcpprotocolrequestparamstest.cpp"
