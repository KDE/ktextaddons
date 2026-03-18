/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolutilstest.h"
#include "mcpprotocolutils.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolUtilsTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolUtilsTest::McpProtocolUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolUtilsTest::shouldConvertRoleToString()
{
    QCOMPARE(McpProtocol::McpProtocolUtils::convertRoleToString(McpProtocol::McpProtocolUtils::Role::Assistant), u"assistant"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertRoleToString(McpProtocol::McpProtocolUtils::Role::Unknown), QString());
    QCOMPARE(McpProtocol::McpProtocolUtils::convertRoleToString(McpProtocol::McpProtocolUtils::Role::User), u"user"_s);
}

void McpProtocolUtilsTest::shouldConvertRoleFromString()
{
    QCOMPARE(McpProtocol::McpProtocolUtils::convertRoleFromString(u"assistant"_s), McpProtocol::McpProtocolUtils::Role::Assistant);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertRoleFromString(QString()), McpProtocol::McpProtocolUtils::Role::Unknown);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertRoleFromString(u"bla"_s), McpProtocol::McpProtocolUtils::Role::Unknown);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertRoleFromString(u"user"_s), McpProtocol::McpProtocolUtils::Role::User);
}

void McpProtocolUtilsTest::shouldConvertLoggingLevelToString()
{
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelToString(McpProtocol::McpProtocolUtils::LoggingLevel::Alert), u"alert"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelToString(McpProtocol::McpProtocolUtils::LoggingLevel::Unknown), QString());
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelToString(McpProtocol::McpProtocolUtils::LoggingLevel::Critical), u"critical"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelToString(McpProtocol::McpProtocolUtils::LoggingLevel::Debug), u"debug"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelToString(McpProtocol::McpProtocolUtils::LoggingLevel::Emergency), u"emergency"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelToString(McpProtocol::McpProtocolUtils::LoggingLevel::Error), u"error"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelToString(McpProtocol::McpProtocolUtils::LoggingLevel::Info), u"info"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelToString(McpProtocol::McpProtocolUtils::LoggingLevel::Warning), u"warning"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelToString(McpProtocol::McpProtocolUtils::LoggingLevel::Notice), u"notice"_s);
}

void McpProtocolUtilsTest::shouldConvertLoggingLevelFromString()
{
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(QString()), McpProtocol::McpProtocolUtils::LoggingLevel::Unknown);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(u"bla"_s), McpProtocol::McpProtocolUtils::LoggingLevel::Unknown);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(u"alert"_s), McpProtocol::McpProtocolUtils::LoggingLevel::Alert);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(u"critical"_s), McpProtocol::McpProtocolUtils::LoggingLevel::Critical);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(u"debug"_s), McpProtocol::McpProtocolUtils::LoggingLevel::Debug);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(u"emergency"_s), McpProtocol::McpProtocolUtils::LoggingLevel::Emergency);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(u"error"_s), McpProtocol::McpProtocolUtils::LoggingLevel::Error);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(u"info"_s), McpProtocol::McpProtocolUtils::LoggingLevel::Info);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(u"warning"_s), McpProtocol::McpProtocolUtils::LoggingLevel::Warning);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(u"notice"_s), McpProtocol::McpProtocolUtils::LoggingLevel::Notice);
}

void McpProtocolUtilsTest::shouldConvertTaskStatusToString()
{
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusToString(McpProtocol::McpProtocolUtils::TaskStatus::Cancelled), u"cancelled"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusToString(McpProtocol::McpProtocolUtils::TaskStatus::Completed), u"completed"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusToString(McpProtocol::McpProtocolUtils::TaskStatus::Failed), u"failed"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusToString(McpProtocol::McpProtocolUtils::TaskStatus::InputRequired), u"input_required"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusToString(McpProtocol::McpProtocolUtils::TaskStatus::Working), u"working"_s);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusToString(McpProtocol::McpProtocolUtils::TaskStatus::Unknown), QString());
}

void McpProtocolUtilsTest::shouldConvertTaskStatusFromString()
{
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusFromString(u"cancelled"_s), McpProtocol::McpProtocolUtils::TaskStatus::Cancelled);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusFromString(u"completed"_s), McpProtocol::McpProtocolUtils::TaskStatus::Completed);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusFromString(u"failed"_s), McpProtocol::McpProtocolUtils::TaskStatus::Failed);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusFromString(u"input_required"_s), McpProtocol::McpProtocolUtils::TaskStatus::InputRequired);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusFromString(u"working"_s), McpProtocol::McpProtocolUtils::TaskStatus::Working);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusFromString(u"foo"_s), McpProtocol::McpProtocolUtils::TaskStatus::Unknown);
    QCOMPARE(McpProtocol::McpProtocolUtils::convertTaskStatusFromString(QString()), McpProtocol::McpProtocolUtils::TaskStatus::Unknown);
}

#include "moc_mcpprotocolutilstest.cpp"
