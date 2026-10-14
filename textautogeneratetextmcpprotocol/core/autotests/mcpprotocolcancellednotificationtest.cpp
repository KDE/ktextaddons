/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcancellednotificationtest.h"
#include "impl/mcpprotocolcancellednotification.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCancelledNotificationTest)

McpProtocolCancelledNotificationTest::McpProtocolCancelledNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCancelledNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelledNotification w;
    // TODO
}
void McpProtocolCancelledNotificationTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject params;
    params["requestId"_L1] = 1;
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCancelledNotification::type());
    obj["params"_L1] = params;
    QVERIFY(McpProtocolCancelledNotification::fromJson(obj).params().requestId().has_value());

    QJsonObject missingParams = obj;
    missingParams.remove("params"_L1);
    QCOMPARE(McpProtocolCancelledNotification::fromJson(missingParams), McpProtocolCancelledNotification());
}

#include "moc_mcpprotocolcancellednotificationtest.cpp"
