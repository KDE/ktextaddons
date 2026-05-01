/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolutilstest.h"
#include "impl/mcpprotocolutils.h"
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

#include "moc_mcpprotocolutilstest.cpp"
