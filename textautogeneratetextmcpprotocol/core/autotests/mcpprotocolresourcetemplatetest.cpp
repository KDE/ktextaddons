/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourcetemplatetest.h"
#include "impl/mcpprotocolresourcetemplate.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceTemplateTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolResourceTemplateTest::McpProtocolResourceTemplateTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceTemplateTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceTemplate w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.annotations().has_value());
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.icons().has_value());
    QVERIFY(!w.mimeType().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(w.uriTemplate().isEmpty());
    QVERIFY(w.name().isEmpty());
}

void McpProtocolResourceTemplateTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceTemplate;
    const QJsonObject obj{{"name"_L1, u"files"_s}, {"uriTemplate"_L1, u"file:///{path}"_s}};
    const McpProtocolResourceTemplate resourceTemplate = McpProtocolResourceTemplate::fromJson(obj);
    QVERIFY(resourceTemplate.isValid());
    QCOMPARE(McpProtocolResourceTemplate::toJson(resourceTemplate), obj);
    QVERIFY(!McpProtocolResourceTemplate().isValid());

    QJsonObject missingName = obj;
    missingName.remove("name"_L1);
    QCOMPARE(McpProtocolResourceTemplate::fromJson(missingName), McpProtocolResourceTemplate());

    QJsonObject missingUriTemplate = obj;
    missingUriTemplate.remove("uriTemplate"_L1);
    QCOMPARE(McpProtocolResourceTemplate::fromJson(missingUriTemplate), McpProtocolResourceTemplate());
}

#include "moc_mcpprotocolresourcetemplatetest.cpp"
