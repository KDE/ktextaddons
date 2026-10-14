/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolloggingmessagenotificationtest.h"
#include "impl/mcpprotocolloggingmessagenotification.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolLoggingMessageNotificationTest)

McpProtocolLoggingMessageNotificationTest::McpProtocolLoggingMessageNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolLoggingMessageNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolLoggingMessageNotification w;
    // TODO
}

void McpProtocolLoggingMessageNotificationTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    using namespace Qt::Literals::StringLiterals;
    QJsonObject params;
    params["level"_L1] = u"info"_s;
    params["data"_L1] = u"message"_s;
    QJsonObject valid;
    valid["jsonrpc"_L1] = u"2.0"_s;
    valid["method"_L1] = u"notifications/message"_s;
    valid["params"_L1] = params;
    const McpProtocolLoggingMessageNotification notification = McpProtocolLoggingMessageNotification::fromJson(valid);
    QVERIFY(notification.params().isValid());
    QCOMPARE(notification.params().level(), McpProtocolUtils::LoggingLevel::Info);

    QJsonObject obj = valid;
    obj.remove(u"params"_s);
    QCOMPARE(McpProtocolLoggingMessageNotification::fromJson(obj), McpProtocolLoggingMessageNotification());

    for (const QString &key : {u"level"_s, u"data"_s}) {
        QJsonObject invalidParams = params;
        invalidParams.remove(key);
        obj = valid;
        obj["params"_L1] = invalidParams;
        QCOMPARE(McpProtocolLoggingMessageNotification::fromJson(obj), McpProtocolLoggingMessageNotification());
        QCOMPARE(McpProtocolLoggingMessageNotificationParams::fromJson(invalidParams), McpProtocolLoggingMessageNotificationParams());
    }
    {
        QJsonObject invalidParams = params;
        invalidParams["level"_L1] = u"foo"_s;
        QCOMPARE(McpProtocolLoggingMessageNotificationParams::fromJson(invalidParams), McpProtocolLoggingMessageNotificationParams());
    }
}

#include "moc_mcpprotocolloggingmessagenotificationtest.cpp"
