/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolutilstest.h"
#include "impl/mcpprotocolelicitrequest.h"
#include "impl/mcpprotocolelicitrequestformparams.h"
#include "impl/mcpprotocolelicitrequesturlparams.h"
#include "impl/mcpprotocolelicitresult.h"
#include "impl/mcpprotocolpingrequest.h"
#include "impl/mcpprotocolutils.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolUtilsTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolUtilsTest::McpProtocolUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolUtilsTest::shouldConvertRoleToString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleToString(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::Assistant),
             u"assistant"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleToString(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::Unknown),
             QString());
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleToString(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::User),
             u"user"_s);
}

void McpProtocolUtilsTest::shouldConvertRoleFromString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleFromString(u"assistant"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::Assistant);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleFromString(QString()),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::Unknown);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleFromString(u"bla"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::Unknown);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertRoleFromString(u"user"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::Role::User);
}

void McpProtocolUtilsTest::shouldConvertLoggingLevelToString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Alert),
             u"alert"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Unknown),
             QString());
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Critical),
             u"critical"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Debug),
             u"debug"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Emergency),
             u"emergency"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Error),
             u"error"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Info),
             u"info"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Warning),
             u"warning"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Notice),
             u"notice"_s);
}

void McpProtocolUtilsTest::shouldConvertLoggingLevelFromString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelFromString(QString()),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Unknown);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelFromString(u"bla"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Unknown);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelFromString(u"alert"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Alert);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelFromString(u"critical"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Critical);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelFromString(u"debug"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Debug);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelFromString(u"emergency"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Emergency);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelFromString(u"error"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Error);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelFromString(u"info"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Info);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelFromString(u"warning"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Warning);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertLoggingLevelFromString(u"notice"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel::Notice);
}

void McpProtocolUtilsTest::shouldConvertTaskStatusToString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Cancelled),
             u"cancelled"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Completed),
             u"completed"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Failed),
             u"failed"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::InputRequired),
             u"input_required"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Working),
             u"working"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Unknown),
             QString());
}

void McpProtocolUtilsTest::shouldConvertTaskStatusFromString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusFromString(u"cancelled"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Cancelled);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusFromString(u"completed"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Completed);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusFromString(u"failed"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Failed);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusFromString(u"input_required"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::InputRequired);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusFromString(u"working"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Working);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusFromString(u"foo"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Unknown);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertTaskStatusFromString(QString()),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::TaskStatus::Unknown);
}

void McpProtocolUtilsTest::shouldConvertProtocolVersionToString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::Unknown),
             QString());
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_03_26),
             u"2025-03-26"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2024_11_05),
             u"2024-11-05"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_06_18),
             u"2025-06-18"_s);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionToString(
                 TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_11_25),
             u"2025-11-25"_s);
}

void McpProtocolUtilsTest::shouldConvertProtocolVersionFromString()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionFromString(u"2025-03-26"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_03_26);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionFromString(u"2024-11-05"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2024_11_05);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionFromString(u"2025-06-18"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_06_18);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionFromString(u"2025-11-25"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_11_25);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionFromString(u"kde"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::Unknown);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionFromString(QString()),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::Unknown);
}

void McpProtocolUtilsTest::shouldOrderLoggingLevelBySeverity()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel;
    QVERIFY(LoggingLevel::Debug < LoggingLevel::Info);
    QVERIFY(LoggingLevel::Info < LoggingLevel::Notice);
    QVERIFY(LoggingLevel::Notice < LoggingLevel::Warning);
    QVERIFY(LoggingLevel::Warning < LoggingLevel::Error);
    QVERIFY(LoggingLevel::Error < LoggingLevel::Critical);
    QVERIFY(LoggingLevel::Critical < LoggingLevel::Alert);
    QVERIFY(LoggingLevel::Alert < LoggingLevel::Emergency);
}

void McpProtocolUtilsTest::shouldKeepLargeRequestId()
{
    const qint64 bigId = 5000000000LL;
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = u"ping"_s;
    obj["id"_L1] = bigId;
    const auto request = TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest::fromJson(obj);
    QVERIFY(std::holds_alternative<qint64>(request.id()));
    QCOMPARE(std::get<qint64>(request.id()), bigId);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest::toJson(request), obj);
}

void McpProtocolUtilsTest::shouldKeepDecimalElicitResultContent()
{
    QJsonObject content;
    content["ratio"_L1] = 0.5;
    content["age"_L1] = 42;
    QJsonObject obj;
    obj["action"_L1] = u"accept"_s;
    obj["content"_L1] = content;
    const auto result = TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::fromJson(obj);
    QVERIFY(result.content().has_value());
    const auto map = *result.content();
    QCOMPARE(std::get<double>(map.value(u"ratio"_s)), 0.5);
    QCOMPARE(std::get<int>(map.value(u"age"_s)), 42);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::toJson(result).value("content"_L1).toObject(), content);
}

void McpProtocolUtilsTest::shouldParseElicitRequestWithoutModeAsForm()
{
    QJsonObject params;
    params["message"_L1] = u"Please provide your name"_s;
    params["requestedSchema"_L1] = QJsonObject{{"type"_L1, u"object"_s}, {"properties"_L1, QJsonObject{}}};
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = u"elicitation/create"_s;
    obj["id"_L1] = 1;
    obj["params"_L1] = params;
    const auto request = TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest::fromJson(obj);
    QVERIFY(std::holds_alternative<TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestFormParams>(request.params()));
}

#include "moc_mcpprotocolutilstest.cpp"
