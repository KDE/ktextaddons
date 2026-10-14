/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourcetest.h"
#include "impl/mcpprotocolresource.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolResourceTest::McpProtocolResourceTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResource w;
    QVERIFY(w.uri().isEmpty());
    QVERIFY(!w.title().has_value());
    QVERIFY(!w.size().has_value());
    QVERIFY(w.name().isEmpty());
    QVERIFY(!w.mimeType().has_value());
    QVERIFY(!w.icons().has_value());
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.annotations().has_value());
    QVERIFY(!w.meta().has_value());
}

void McpProtocolResourceTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolResource;
    QJsonObject obj{{"name"_L1, u"foo"_s}, {"uri"_L1, u"file:///foo.txt"_s}};
    const McpProtocolResource resource = McpProtocolResource::fromJson(obj);
    QVERIFY(resource.isValid());
    QCOMPARE(McpProtocolResource::toJson(resource), obj);
    QVERIFY(!McpProtocolResource().isValid());

    QJsonObject missingName = obj;
    missingName.remove("name"_L1);
    QCOMPARE(McpProtocolResource::fromJson(missingName), McpProtocolResource());

    QJsonObject missingUri = obj;
    missingUri.remove("uri"_L1);
    QCOMPARE(McpProtocolResource::fromJson(missingUri), McpProtocolResource());

    // Invalid icons are skipped
    obj["icons"_L1] = QJsonArray{QJsonObject{{"src"_L1, u"https://example.com/icon.png"_s}}, QJsonObject()};
    const McpProtocolResource withIcons = McpProtocolResource::fromJson(obj);
    QVERIFY(withIcons.icons().has_value());
    QCOMPARE(withIcons.icons()->count(), 1);
}

#include "moc_mcpprotocolresourcetest.cpp"
