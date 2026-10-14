/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcalltoolrequestparamstest.h"
#include "impl/mcpprotocolcalltoolrequestparams.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCallToolRequestParamsTest)

McpProtocolCallToolRequestParamsTest::McpProtocolCallToolRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCallToolRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolRequestParams w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.arguments().has_value());
    QVERIFY(!w.task().has_value());
    QVERIFY(w.name().isEmpty());
}
void McpProtocolCallToolRequestParamsTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject obj;
    obj["name"_L1] = u"tool"_s;
    QVERIFY(McpProtocolCallToolRequestParams::fromJson(obj).isValid());

    QCOMPARE(McpProtocolCallToolRequestParams::fromJson(QJsonObject()), McpProtocolCallToolRequestParams());
}

#include "moc_mcpprotocolcalltoolrequestparamstest.cpp"
