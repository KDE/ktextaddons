/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolembeddedresourcetest.h"
#include "impl/mcpprotocolembeddedresource.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolEmbeddedResourceTest)

McpProtocolEmbeddedResourceTest::McpProtocolEmbeddedResourceTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolEmbeddedResourceTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolEmbeddedResource w;
    QCOMPARE(w.type(), "resource"_ba);
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.annotations().has_value());
}
void McpProtocolEmbeddedResourceTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject resource;
    resource["uri"_L1] = u"file:///tmp/foo"_s;
    resource["blob"_L1] = u"AAAA"_s;
    QJsonObject obj;
    obj["type"_L1] = u"resource"_s;
    obj["resource"_L1] = resource;
    QVERIFY(McpProtocolEmbeddedResource::fromJson(obj).isValid());

    QJsonObject missingResource = obj;
    missingResource.remove("resource"_L1);
    QCOMPARE(McpProtocolEmbeddedResource::fromJson(missingResource), McpProtocolEmbeddedResource());

    QJsonObject invalidResource = obj;
    QJsonObject badResource = resource;
    badResource.remove("uri"_L1);
    invalidResource["resource"_L1] = badResource;
    QCOMPARE(McpProtocolEmbeddedResource::fromJson(invalidResource), McpProtocolEmbeddedResource());
}

#include "moc_mcpprotocolembeddedresourcetest.cpp"
