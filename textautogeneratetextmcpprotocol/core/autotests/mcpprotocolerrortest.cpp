/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolerrortest.h"
#include "impl/mcpprotocolerror.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolErrorTest)

McpProtocolErrorTest::McpProtocolErrorTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolErrorTest::shouldhaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolError w;
    QCOMPARE(w.code(), 0);
    QVERIFY(w.message().isEmpty());
    QVERIFY(!w.data().has_value());
}

void McpProtocolErrorTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject obj;
    obj["code"_L1] = -32600;
    obj["message"_L1] = u"Invalid request"_s;
    QVERIFY(McpProtocolError::fromJson(obj).isValid());

    QJsonObject missingCode = obj;
    missingCode.remove("code"_L1);
    QCOMPARE(McpProtocolError::fromJson(missingCode), McpProtocolError());

    QJsonObject missingMessage = obj;
    missingMessage.remove("message"_L1);
    QCOMPARE(McpProtocolError::fromJson(missingMessage), McpProtocolError());
}

#include "moc_mcpprotocolerrortest.cpp"
