/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcommonutilstest.h"
#include "common/mcpprotocolcommonutils.h"
#include <QTest>
#include <cctype>
QTEST_GUILESS_MAIN(McpProtocolCommonUtilsTest)

McpProtocolCommonUtilsTest::McpProtocolCommonUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCommonUtilsTest::shouldGenerateAuthToken()
{
    const QByteArray token = TextAutoGenerateTextMcpProtocolCore::McpProtocolCommonUtils::generateAuthToken();
    // 32 bytes encoded in base64url without padding
    QCOMPARE(token.size(), 43);
    for (const char c : token) {
        QVERIFY2(std::isalnum(static_cast<unsigned char>(c)) || c == '-' || c == '_', token.constData());
    }
    QVERIFY(token != TextAutoGenerateTextMcpProtocolCore::McpProtocolCommonUtils::generateAuthToken());
}

#include "moc_mcpprotocolcommonutilstest.cpp"
