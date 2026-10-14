/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolprogressnotificationparamstest.h"
#include "impl/mcpprotocolprogressnotificationparams.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolProgressNotificationParamsTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolProgressNotificationParamsTest::McpProtocolProgressNotificationParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolProgressNotificationParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolProgressNotificationParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.message().has_value());
    QVERIFY(!w.total().has_value());
    // QVERIFY(!w.progressToken());
    QCOMPARE(w.progress(), 0.0);
}

void McpProtocolProgressNotificationParamsTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolProgressNotificationParams;
    const QJsonObject obj{{"progress"_L1, 0.5}, {"progressToken"_L1, u"abc"_s}};
    const McpProtocolProgressNotificationParams params = McpProtocolProgressNotificationParams::fromJson(obj);
    QVERIFY(params.isValid());
    QCOMPARE(params.progress(), 0.5);
    QCOMPARE(McpProtocolProgressNotificationParams::toJson(params), obj);
    QVERIFY(!McpProtocolProgressNotificationParams().isValid());

    QJsonObject missingToken = obj;
    missingToken.remove("progressToken"_L1);
    QCOMPARE(McpProtocolProgressNotificationParams::fromJson(missingToken), McpProtocolProgressNotificationParams());

    QJsonObject invalidToken = obj;
    invalidToken["progressToken"_L1] = QJsonObject();
    QCOMPARE(McpProtocolProgressNotificationParams::fromJson(invalidToken), McpProtocolProgressNotificationParams());

    QJsonObject missingProgress = obj;
    missingProgress.remove("progress"_L1);
    QCOMPARE(McpProtocolProgressNotificationParams::fromJson(missingProgress), McpProtocolProgressNotificationParams());

    QJsonObject invalidProgress = obj;
    invalidProgress["progress"_L1] = u"50%"_s;
    QCOMPARE(McpProtocolProgressNotificationParams::fromJson(invalidProgress), McpProtocolProgressNotificationParams());
}

#include "moc_mcpprotocolprogressnotificationparamstest.cpp"
