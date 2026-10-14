/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolicontest.h"
#include "impl/mcpprotocolicon.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolIconTest)

McpProtocolIconTest::McpProtocolIconTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolIconTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolIcon w;
    QVERIFY(w.src().isEmpty());
    QVERIFY(!w.mimeType());
    QVERIFY(!w.sizes());
    QVERIFY(!w.theme());
}

void McpProtocolIconTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    using namespace Qt::Literals::StringLiterals;
    QJsonObject valid;
    valid["src"_L1] = u"https://example.com/icon.png"_s;
    valid["theme"_L1] = u"dark"_s;
    const McpProtocolIcon icon = McpProtocolIcon::fromJson(valid);
    QVERIFY(icon.isValid());
    QCOMPARE(icon.theme().value_or(QString()), u"dark"_s);

    QJsonObject obj = valid;
    obj.remove(u"src"_s);
    QCOMPARE(McpProtocolIcon::fromJson(obj), McpProtocolIcon());
    QVERIFY(!McpProtocolIcon::fromJson(obj).isValid());

    obj = valid;
    obj["theme"_L1] = u"foo"_s;
    QVERIFY(!McpProtocolIcon::fromJson(obj).theme().has_value());
}

#include "moc_mcpprotocolicontest.cpp"
