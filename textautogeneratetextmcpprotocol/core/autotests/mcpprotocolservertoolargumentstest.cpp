/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolservertoolargumentstest.h"
#include "server/mcpprotocolservertoolarguments.h"
#include <QJsonArray>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolServerToolArgumentsTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

McpProtocolServerToolArgumentsTest::McpProtocolServerToolArgumentsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolServerToolArgumentsTest::shouldCheckIsProvided()
{
    QVERIFY(!McpProtocolServerToolArguments::isProvided(QJsonValue(QJsonValue::Undefined)));
    QVERIFY(!McpProtocolServerToolArguments::isProvided(QJsonValue(QJsonValue::Null)));
    QVERIFY(McpProtocolServerToolArguments::isProvided(QJsonValue(u""_s)));
    QVERIFY(McpProtocolServerToolArguments::isProvided(QJsonValue(false)));
}

void McpProtocolServerToolArgumentsTest::shouldReadInteger()
{
    QCOMPARE(McpProtocolServerToolArguments::integer(QJsonValue(42)), 42);
    QCOMPARE(McpProtocolServerToolArguments::integer(QJsonValue(-3.0)), -3);
    QCOMPARE(McpProtocolServerToolArguments::integer(QJsonValue(u" 60 "_s)), 60);
    QCOMPARE(McpProtocolServerToolArguments::integer(QJsonValue(2.5)), std::nullopt);
    QCOMPARE(McpProtocolServerToolArguments::integer(QJsonValue(u"2.5"_s)), std::nullopt);
    QCOMPARE(McpProtocolServerToolArguments::integer(QJsonValue(u"abc"_s)), std::nullopt);
    QCOMPARE(McpProtocolServerToolArguments::integer(QJsonValue(true)), std::nullopt);
    QCOMPARE(McpProtocolServerToolArguments::integer(QJsonValue()), std::nullopt);
}

void McpProtocolServerToolArgumentsTest::shouldReadNumber()
{
    QCOMPARE(McpProtocolServerToolArguments::number(QJsonValue(1.5)), 1.5);
    QCOMPARE(McpProtocolServerToolArguments::number(QJsonValue(u"1.25"_s)), 1.25);
    QCOMPARE(McpProtocolServerToolArguments::number(QJsonValue(u"abc"_s)), std::nullopt);
    QCOMPARE(McpProtocolServerToolArguments::number(QJsonValue(true)), std::nullopt);
}

void McpProtocolServerToolArgumentsTest::shouldReadBoolean()
{
    QCOMPARE(McpProtocolServerToolArguments::boolean(QJsonValue(true)), true);
    QCOMPARE(McpProtocolServerToolArguments::boolean(QJsonValue(u"False"_s)), false);
    QCOMPARE(McpProtocolServerToolArguments::boolean(QJsonValue(u" true "_s)), true);
    QCOMPARE(McpProtocolServerToolArguments::boolean(QJsonValue(u"yes"_s)), std::nullopt);
    QCOMPARE(McpProtocolServerToolArguments::boolean(QJsonValue(1)), std::nullopt);
}

void McpProtocolServerToolArgumentsTest::shouldReadStringList()
{
    QStringList list;
    QVERIFY(McpProtocolServerToolArguments::readStringList(QJsonValue(), list));
    QVERIFY(list.isEmpty());
    QVERIFY(McpProtocolServerToolArguments::readStringList(QJsonArray{u" a "_s, u""_s, u"b"_s}, list));
    QCOMPARE(list, (QStringList{u"a"_s, u"b"_s}));
    QVERIFY(!McpProtocolServerToolArguments::readStringList(QJsonArray{u"a"_s, 1}, list));
    QVERIFY(!McpProtocolServerToolArguments::readStringList(QJsonValue(u"a"_s), list));
}

void McpProtocolServerToolArgumentsTest::shouldReadOptionalString()
{
    const QMap<QString, QJsonValue> arguments{{u"name"_s, u" Bob "_s}, {u"empty"_s, u""_s}, {u"number"_s, 1}, {u"null"_s, QJsonValue()}};
    std::optional<QString> result;
    QVERIFY(McpProtocolServerToolArguments::readOptionalString(arguments, u"missing"_s, result));
    QVERIFY(!result.has_value());
    QVERIFY(McpProtocolServerToolArguments::readOptionalString(arguments, u"null"_s, result));
    QVERIFY(!result.has_value());
    QVERIFY(McpProtocolServerToolArguments::readOptionalString(arguments, u"name"_s, result));
    QCOMPARE(result, u"Bob"_s);
    QVERIFY(McpProtocolServerToolArguments::readOptionalString(arguments, u"empty"_s, result));
    QCOMPARE(result, QString());
    QVERIFY(!McpProtocolServerToolArguments::readOptionalString(arguments, u"number"_s, result));
}

#include "moc_mcpprotocolservertoolargumentstest.cpp"
