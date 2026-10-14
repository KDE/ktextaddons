/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourceupdatednotificationparamstest.h"
#include "impl/mcpprotocolresourceupdatednotificationparams.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceUpdatedNotificationParamsTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolResourceUpdatedNotificationParamsTest::McpProtocolResourceUpdatedNotificationParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceUpdatedNotificationParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceUpdatedNotificationParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.uri().isEmpty());
}

void McpProtocolResourceUpdatedNotificationParamsTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceUpdatedNotificationParams;
    const QJsonObject obj{{"uri"_L1, u"file:///foo.txt"_s}};
    const McpProtocolResourceUpdatedNotificationParams params = McpProtocolResourceUpdatedNotificationParams::fromJson(obj);
    QVERIFY(params.isValid());
    QCOMPARE(McpProtocolResourceUpdatedNotificationParams::toJson(params), obj);
    QVERIFY(!McpProtocolResourceUpdatedNotificationParams().isValid());
    QCOMPARE(McpProtocolResourceUpdatedNotificationParams::fromJson(QJsonObject()), McpProtocolResourceUpdatedNotificationParams());
}

#include "moc_mcpprotocolresourceupdatednotificationparamstest.cpp"
