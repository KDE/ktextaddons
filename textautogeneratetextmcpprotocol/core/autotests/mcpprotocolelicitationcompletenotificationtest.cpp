/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolelicitationcompletenotificationtest.h"
#include "impl/mcpprotocolelicitationcompletenotification.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolElicitationCompleteNotificationTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

McpProtocolElicitationCompleteNotificationTest::McpProtocolElicitationCompleteNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolElicitationCompleteNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitationCompleteNotification w;
    QVERIFY(w.params().elicitationId().isEmpty());
}
void McpProtocolElicitationCompleteNotificationTest::shouldConvertJson()
{
    McpProtocolElicitationCompleteNotification::Params params;
    params.setElicitationId(u"elicit-1"_s);
    QCOMPARE(params.elicitationId(), u"elicit-1"_s);
    McpProtocolElicitationCompleteNotification notification;
    notification.setParams(params);

    const QJsonObject obj = McpProtocolElicitationCompleteNotification::toJson(notification);
    QCOMPARE(obj.value("method"_L1).toString(), u"notifications/elicitation/complete"_s);
    QCOMPARE(McpProtocolElicitationCompleteNotification::fromJson(obj), notification);

    QJsonObject wrongMethod = obj;
    wrongMethod["method"_L1] = u"notifications/progress"_s;
    QCOMPARE(McpProtocolElicitationCompleteNotification::fromJson(wrongMethod), McpProtocolElicitationCompleteNotification());
}

#include "moc_mcpprotocolelicitationcompletenotificationtest.cpp"
