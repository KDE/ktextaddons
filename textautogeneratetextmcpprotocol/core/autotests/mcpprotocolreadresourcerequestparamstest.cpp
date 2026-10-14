/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolreadresourcerequestparamstest.h"
#include "impl/mcpprotocolreadresourcerequestparams.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolReadResourceRequestParamsTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolReadResourceRequestParamsTest::McpProtocolReadResourceRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolReadResourceRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.uri().isEmpty());
}

void McpProtocolReadResourceRequestParamsTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceRequestParams;
    const QJsonObject obj{{"uri"_L1, u"file:///foo.txt"_s}};
    const McpProtocolReadResourceRequestParams params = McpProtocolReadResourceRequestParams::fromJson(obj);
    QVERIFY(params.isValid());
    QCOMPARE(McpProtocolReadResourceRequestParams::toJson(params), obj);
    QVERIFY(!McpProtocolReadResourceRequestParams().isValid());
    QCOMPARE(McpProtocolReadResourceRequestParams::fromJson(QJsonObject()), McpProtocolReadResourceRequestParams());
}

#include "moc_mcpprotocolreadresourcerequestparamstest.cpp"
