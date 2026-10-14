/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolimplementationtest.h"
#include "impl/mcpprotocolimplementation.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolImplementationTest)

McpProtocolImplementationTest::McpProtocolImplementationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolImplementationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolImplementation w;
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.icons().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(!w.websiteUrl().has_value());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.version().isEmpty());
}

void McpProtocolImplementationTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    using namespace Qt::Literals::StringLiterals;
    QJsonObject validIcon;
    validIcon["src"_L1] = u"https://example.com/icon.png"_s;
    QJsonObject invalidIcon;
    invalidIcon["mimeType"_L1] = u"image/png"_s;

    QJsonObject valid;
    valid["name"_L1] = u"client"_s;
    valid["version"_L1] = u"1.0"_s;
    valid["icons"_L1] = QJsonArray{validIcon, invalidIcon};
    const McpProtocolImplementation impl = McpProtocolImplementation::fromJson(valid);
    QVERIFY(impl.isValid());
    QVERIFY(impl.icons().has_value());
    QCOMPARE(impl.icons()->count(), 1);

    for (const QString &key : {u"name"_s, u"version"_s}) {
        QJsonObject obj = valid;
        obj.remove(key);
        QCOMPARE(McpProtocolImplementation::fromJson(obj), McpProtocolImplementation());
    }
}

#include "moc_mcpprotocolimplementationtest.cpp"
