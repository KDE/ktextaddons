/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltaskstatusnotificationtest.h"
#include "impl/mcpprotocoltaskstatusnotification.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolTaskStatusNotificationTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolTaskStatusNotificationTest::McpProtocolTaskStatusNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolTaskStatusNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolTaskStatusNotification w;
    QCOMPARE(w.type(), "notifications/tasks/status"_ba);
}

void McpProtocolTaskStatusNotificationTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    const QJsonObject params{{"taskId"_L1, u"t1"_s},
                             {"status"_L1, u"completed"_s},
                             {"createdAt"_L1, u"2025-11-25T10:00:00Z"_s},
                             {"lastUpdatedAt"_L1, u"2025-11-25T10:00:01Z"_s}};
    const QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s}, {"method"_L1, u"notifications/tasks/status"_s}, {"params"_L1, params}};
    QCOMPARE(McpProtocolTaskStatusNotification::fromJson(obj).params().taskId(), u"t1"_s);
    // Missing params
    QJsonObject withoutParams = obj;
    withoutParams.remove("params"_L1);
    QCOMPARE(McpProtocolTaskStatusNotification::fromJson(withoutParams), McpProtocolTaskStatusNotification());
    // Invalid params
    QJsonObject invalidParams = obj;
    QJsonObject incomplete = params;
    incomplete.remove("taskId"_L1);
    invalidParams["params"_L1] = incomplete;
    QCOMPARE(McpProtocolTaskStatusNotification::fromJson(invalidParams), McpProtocolTaskStatusNotification());
}

#include "moc_mcpprotocoltaskstatusnotificationtest.cpp"
