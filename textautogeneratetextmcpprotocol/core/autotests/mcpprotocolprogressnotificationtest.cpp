/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolprogressnotificationtest.h"
#include "impl/mcpprotocolprogressnotification.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolProgressNotificationTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolProgressNotificationTest::McpProtocolProgressNotificationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolProgressNotificationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolProgressNotification w;
    QCOMPARE(w.type(), "notifications/progress"_ba);
    // TODO
}

void McpProtocolProgressNotificationTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolProgressNotification;
    QJsonObject obj{{"jsonrpc"_L1, u"2.0"_s},
                    {"method"_L1, u"notifications/progress"_s},
                    {"params"_L1, QJsonObject{{"progress"_L1, 0.5}, {"progressToken"_L1, u"abc"_s}}}};
    QCOMPARE(McpProtocolProgressNotification::toJson(McpProtocolProgressNotification::fromJson(obj)), obj);
    obj["params"_L1] = QJsonObject{{"progress"_L1, 0.5}};
    QCOMPARE(McpProtocolProgressNotification::fromJson(obj), McpProtocolProgressNotification());
    obj.remove("params"_L1);
    QCOMPARE(McpProtocolProgressNotification::fromJson(obj), McpProtocolProgressNotification());
}

#include "moc_mcpprotocolprogressnotificationtest.cpp"
