/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolunsupportedprotocolversionerrortest.h"
#include "impl/mcpprotocolunsupportedprotocolversionerror.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
using TextAutoGenerateTextMcpProtocolCore::McpProtocolUnsupportedProtocolVersionError;
QTEST_GUILESS_MAIN(McpProtocolUnsupportedProtocolVersionErrorTest)

McpProtocolUnsupportedProtocolVersionErrorTest::McpProtocolUnsupportedProtocolVersionErrorTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolUnsupportedProtocolVersionErrorTest::shouldLoadAndSaveError()
{
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s},
                          {"id"_L1, 2},
                          {"error"_L1,
                           QJsonObject{{"code"_L1, -32022},
                                       {"message"_L1, u"Unsupported protocol version"_s},
                                       {"data"_L1, QJsonObject{{"supported"_L1, QJsonArray{u"2026-07-28"_s}}, {"requested"_L1, u"1999-01-01"_s}}}}}};
    const auto error = McpProtocolUnsupportedProtocolVersionError::fromJson(obj);
    QCOMPARE(error.error().code(), McpProtocolUnsupportedProtocolVersionError::errorCode);
    QVERIFY(error.id().has_value());
    QCOMPARE(McpProtocolUnsupportedProtocolVersionError::toJson(error), obj);
}

void McpProtocolUnsupportedProtocolVersionErrorTest::shouldRejectOtherErrorCode()
{
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, 2}, {"error"_L1, QJsonObject{{"code"_L1, -32601}, {"message"_L1, u"Method not found"_s}}}};
    QCOMPARE(McpProtocolUnsupportedProtocolVersionError::fromJson(obj), McpProtocolUnsupportedProtocolVersionError());
}

void McpProtocolUnsupportedProtocolVersionErrorTest::shouldRejectMissingRequiredFields()
{
    // Missing error
    QCOMPARE(McpProtocolUnsupportedProtocolVersionError::fromJson(QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, 2}}),
             McpProtocolUnsupportedProtocolVersionError());
    // error is not an object
    QCOMPARE(McpProtocolUnsupportedProtocolVersionError::fromJson(QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, 2}, {"error"_L1, u"foo"_s}}),
             McpProtocolUnsupportedProtocolVersionError());
}

void McpProtocolUnsupportedProtocolVersionErrorTest::shouldReturnSupportedAndRequested()
{
    // Invalid entry (not a string) is ignored
    const QJsonObject obj{
        {"jsonrpc"_L1, u"2.0"_s},
        {"id"_L1, 2},
        {"error"_L1,
         QJsonObject{{"code"_L1, -32022},
                     {"message"_L1, u"Unsupported protocol version"_s},
                     {"data"_L1, QJsonObject{{"supported"_L1, QJsonArray{u"2025-11-25"_s, 42, u"2026-07-28"_s}}, {"requested"_L1, u"1999-01-01"_s}}}}}};
    const auto error = McpProtocolUnsupportedProtocolVersionError::fromJson(obj);
    QCOMPARE(error.supported(), QStringList({u"2025-11-25"_s, u"2026-07-28"_s}));
    QCOMPARE(error.requested(), u"1999-01-01"_s);

    QVERIFY(McpProtocolUnsupportedProtocolVersionError().supported().isEmpty());
    QVERIFY(McpProtocolUnsupportedProtocolVersionError().requested().isEmpty());
}

#include "moc_mcpprotocolunsupportedprotocolversionerrortest.cpp"
