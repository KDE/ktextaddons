/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolpaginatedrequestparamstest.h"
#include "impl/mcpprotocolpaginatedrequestparams.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolPaginatedRequestParamsTest)

McpProtocolPaginatedRequestParamsTest::McpProtocolPaginatedRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolPaginatedRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.cursor().isEmpty());
}

void McpProtocolPaginatedRequestParamsTest::shouldNotWriteEmptyCursor()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedRequestParams params;
    QVERIFY(!TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedRequestParams::toJson(params).contains("cursor"_L1));
    params.setCursor(u"next"_s);
    const QJsonObject obj = TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedRequestParams::toJson(params);
    QCOMPARE(obj.value("cursor"_L1).toString(), u"next"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedRequestParams::fromJson(obj), params);
}

#include "moc_mcpprotocolpaginatedrequestparamstest.cpp"
