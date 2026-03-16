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

#include "moc_mcpprotocolutilstest.cpp"
