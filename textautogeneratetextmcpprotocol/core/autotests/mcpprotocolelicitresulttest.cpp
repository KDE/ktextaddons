/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolelicitresulttest.h"
#include "impl/mcpprotocolelicitresult.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolElicitResultTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitResultTest::McpProtocolElicitResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolElicitResultTest::shouldHaveDefaultValues()
{
    const McpProtocolElicitResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.content().has_value());
    QCOMPARE(w.action(), McpProtocolElicitResult::Action::Unknown);
}

void McpProtocolElicitResultTest::shouldConvertActionToString()
{
    QCOMPARE(McpProtocolElicitResult::convertActionToString(McpProtocolElicitResult::Action::Accept), u"accept"_s);
    QCOMPARE(McpProtocolElicitResult::convertActionToString(McpProtocolElicitResult::Action::Cancel), u"cancel"_s);
    QCOMPARE(McpProtocolElicitResult::convertActionToString(McpProtocolElicitResult::Action::Decline), u"decline"_s);
    QVERIFY(McpProtocolElicitResult::convertActionToString(McpProtocolElicitResult::Action::Unknown).isEmpty());

    QCOMPARE(McpProtocolElicitResult::convertActionFromString(u"accept"_s), McpProtocolElicitResult::Action::Accept);
    QCOMPARE(McpProtocolElicitResult::convertActionFromString(u"cancel"_s), McpProtocolElicitResult::Action::Cancel);
    QCOMPARE(McpProtocolElicitResult::convertActionFromString(u"decline"_s), McpProtocolElicitResult::Action::Decline);
}

void McpProtocolElicitResultTest::shouldConvertJson()
{
    QJsonObject content;
    content["name"_L1] = u"foo"_s;
    content["age"_L1] = 42;
    content["subscribe"_L1] = true;
    content["tags"_L1] = QJsonArray{u"a"_s, u"b"_s};

    QJsonObject obj;
    obj["action"_L1] = u"accept"_s;
    obj["content"_L1] = content;

    const auto result = McpProtocolElicitResult::fromJson(obj);
    QCOMPARE(result.action(), McpProtocolElicitResult::Action::Accept);
    QVERIFY(result.content().has_value());
    const auto map = *result.content();
    QCOMPARE(std::get<QString>(map.value(u"name"_s)), u"foo"_s);
    QCOMPARE(std::get<int>(map.value(u"age"_s)), 42);
    QCOMPARE(std::get<bool>(map.value(u"subscribe"_s)), true);
    QCOMPARE(std::get<QStringList>(map.value(u"tags"_s)), QStringList({u"a"_s, u"b"_s}));

    QCOMPARE(McpProtocolElicitResult::toJson(result), obj);
}

#include "moc_mcpprotocolelicitresulttest.cpp"
