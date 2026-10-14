/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolreadresourcerequesttest.h"
#include "impl/mcpprotocolreadresourcerequest.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolReadResourceRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolReadResourceRequestTest::McpProtocolReadResourceRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolReadResourceRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceRequest w;
    QCOMPARE(w.type(), "resources/read"_ba);
    // TODO
}

void McpProtocolReadResourceRequestTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceRequest;
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s},
                          {"method"_L1, u"resources/read"_s},
                          {"id"_L1, 1},
                          {"params"_L1, QJsonObject{{"uri"_L1, u"file:///foo.txt"_s}}}};
    QCOMPARE(McpProtocolReadResourceRequest::toJson(McpProtocolReadResourceRequest::fromJson(obj)), obj);

    QJsonObject missingId = obj;
    missingId.remove("id"_L1);
    QCOMPARE(McpProtocolReadResourceRequest::fromJson(missingId), McpProtocolReadResourceRequest());

    QJsonObject missingParams = obj;
    missingParams.remove("params"_L1);
    QCOMPARE(McpProtocolReadResourceRequest::fromJson(missingParams), McpProtocolReadResourceRequest());

    QJsonObject missingUri = obj;
    missingUri["params"_L1] = QJsonObject();
    QCOMPARE(McpProtocolReadResourceRequest::fromJson(missingUri), McpProtocolReadResourceRequest());
}

#include "moc_mcpprotocolreadresourcerequesttest.cpp"
