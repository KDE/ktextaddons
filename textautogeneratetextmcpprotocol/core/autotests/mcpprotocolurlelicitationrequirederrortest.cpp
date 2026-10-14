/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolurlelicitationrequirederrortest.h"
#include "impl/mcpprotocolurlelicitationrequirederror.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
using TextAutoGenerateTextMcpProtocolCore::McpProtocolURLElicitationRequiredError;
QTEST_GUILESS_MAIN(McpProtocolURLElicitationRequiredErrorTest)

McpProtocolURLElicitationRequiredErrorTest::McpProtocolURLElicitationRequiredErrorTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolURLElicitationRequiredErrorTest::shouldLoadAndSaveError()
{
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, 2}, {"error"_L1, QJsonObject{{"code"_L1, -32042}, {"message"_L1, u"Authorization required"_s}}}};
    const auto error = McpProtocolURLElicitationRequiredError::fromJson(obj);
    QCOMPARE(error.error().code(), McpProtocolURLElicitationRequiredError::errorCode);
    QVERIFY(error.id().has_value());
    QCOMPARE(McpProtocolURLElicitationRequiredError::toJson(error), obj);
}

void McpProtocolURLElicitationRequiredErrorTest::shouldRejectOtherErrorCode()
{
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, 2}, {"error"_L1, QJsonObject{{"code"_L1, -32601}, {"message"_L1, u"Method not found"_s}}}};
    QCOMPARE(McpProtocolURLElicitationRequiredError::fromJson(obj), McpProtocolURLElicitationRequiredError());
}

void McpProtocolURLElicitationRequiredErrorTest::shouldRejectMissingRequiredFields()
{
    // Missing error
    QCOMPARE(McpProtocolURLElicitationRequiredError::fromJson(QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, 2}}), McpProtocolURLElicitationRequiredError());
    // error is not an object
    QCOMPARE(McpProtocolURLElicitationRequiredError::fromJson(QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, 2}, {"error"_L1, u"foo"_s}}),
             McpProtocolURLElicitationRequiredError());
}

void McpProtocolURLElicitationRequiredErrorTest::shouldReturnElicitations()
{
    const QJsonObject validElicitation{{"mode"_L1, u"url"_s},
                                       {"elicitationId"_L1, u"elicit-1"_s},
                                       {"message"_L1, u"Authorize access"_s},
                                       {"url"_L1, u"https://example.com/authorize"_s}};
    // Invalid entry (no url) is ignored
    const QJsonObject invalidElicitation{{"mode"_L1, u"url"_s}, {"elicitationId"_L1, u"elicit-2"_s}, {"message"_L1, u"Missing url"_s}};
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s},
                          {"id"_L1, 2},
                          {"error"_L1,
                           QJsonObject{{"code"_L1, -32042},
                                       {"message"_L1, u"Authorization required"_s},
                                       {"data"_L1, QJsonObject{{"elicitations"_L1, QJsonArray{validElicitation, invalidElicitation}}}}}}};
    const auto error = McpProtocolURLElicitationRequiredError::fromJson(obj);
    const auto elicitations = error.elicitations();
    QCOMPARE(elicitations.count(), 1);
    QCOMPARE(elicitations.constFirst().elicitationId(), u"elicit-1"_s);
    QCOMPARE(elicitations.constFirst().url(), u"https://example.com/authorize"_s);

    QVERIFY(McpProtocolURLElicitationRequiredError().elicitations().isEmpty());
}

#include "moc_mcpprotocolurlelicitationrequirederrortest.cpp"
