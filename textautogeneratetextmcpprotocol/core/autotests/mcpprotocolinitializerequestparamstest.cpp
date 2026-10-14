/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolinitializerequestparamstest.h"
#include "impl/mcpprotocolinitializerequestparams.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolInitializeRequestParamsTest)

McpProtocolInitializeRequestParamsTest::McpProtocolInitializeRequestParamsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolInitializeRequestParamsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequestParams w;
    QVERIFY(!w.meta().has_value());
    // TODO
}

void McpProtocolInitializeRequestParamsTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    using namespace Qt::Literals::StringLiterals;
    QJsonObject clientInfo;
    clientInfo["name"_L1] = u"client"_s;
    clientInfo["version"_L1] = u"1.0"_s;
    QJsonObject valid;
    valid["protocolVersion"_L1] = u"2025-11-25"_s;
    valid["capabilities"_L1] = QJsonObject();
    valid["clientInfo"_L1] = clientInfo;
    const McpProtocolInitializeRequestParams params = McpProtocolInitializeRequestParams::fromJson(valid);
    QVERIFY(params.isValid());
    QCOMPARE(params.protocolVersion(), u"2025-11-25"_s);

    for (const QString &key : {u"protocolVersion"_s, u"capabilities"_s, u"clientInfo"_s}) {
        QJsonObject obj = valid;
        obj.remove(key);
        QCOMPARE(McpProtocolInitializeRequestParams::fromJson(obj), McpProtocolInitializeRequestParams());
    }
    {
        QJsonObject obj = valid;
        obj["clientInfo"_L1] = QJsonObject();
        QCOMPARE(McpProtocolInitializeRequestParams::fromJson(obj), McpProtocolInitializeRequestParams());
    }
}

#include "moc_mcpprotocolinitializerequestparamstest.cpp"
