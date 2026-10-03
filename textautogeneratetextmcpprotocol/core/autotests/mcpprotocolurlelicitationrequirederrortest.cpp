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

#include "moc_mcpprotocolurlelicitationrequirederrortest.cpp"
