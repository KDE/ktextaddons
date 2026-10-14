/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcancellednotificationparamstest.h"
#include "impl/mcpprotocolcancellednotificationparams.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCancelledNotificationParamsTest)

McpProtocolCancelledNotificationParamsTest::McpProtocolCancelledNotificationParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCancelledNotificationParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCancelledNotificationParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.reason().has_value());
    QVERIFY(!w.requestId().has_value());
}
void McpProtocolCancelledNotificationParamsTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject obj;
    obj["requestId"_L1] = u"abc"_s;
    QVERIFY(McpProtocolCancelledNotificationParams::fromJson(obj).requestId().has_value());

    // requestId is optional: an invalid value is ignored
    obj["requestId"_L1] = true;
    QVERIFY(!McpProtocolCancelledNotificationParams::fromJson(obj).requestId().has_value());
}

#include "moc_mcpprotocolcancellednotificationparamstest.cpp"
