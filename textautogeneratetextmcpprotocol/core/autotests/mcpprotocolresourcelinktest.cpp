/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourcelinktest.h"
#include "impl/mcpprotocolresourcelink.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceLinkTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolResourceLinkTest::McpProtocolResourceLinkTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceLinkTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceLink w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.annotations().has_value());
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.mimeType().has_value());
    QVERIFY(!w.size().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.uri().isEmpty());
    QCOMPARE(w.type(), "resource_link"_ba);
}

void McpProtocolResourceLinkTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceLink;
    const QJsonObject obj{{"type"_L1, u"resource_link"_s}, {"name"_L1, u"foo"_s}, {"uri"_L1, u"file:///foo.txt"_s}};
    const McpProtocolResourceLink link = McpProtocolResourceLink::fromJson(obj);
    QVERIFY(link.isValid());
    QCOMPARE(McpProtocolResourceLink::toJson(link), obj);
    QVERIFY(!McpProtocolResourceLink().isValid());

    QJsonObject missingName = obj;
    missingName.remove("name"_L1);
    QCOMPARE(McpProtocolResourceLink::fromJson(missingName), McpProtocolResourceLink());

    QJsonObject missingUri = obj;
    missingUri.remove("uri"_L1);
    QCOMPARE(McpProtocolResourceLink::fromJson(missingUri), McpProtocolResourceLink());
}

#include "moc_mcpprotocolresourcelinktest.cpp"
