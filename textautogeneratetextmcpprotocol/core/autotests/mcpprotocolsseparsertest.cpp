/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsseparsertest.h"
#include "common/mcpprotocolsseparser.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
using TextAutoGenerateTextMcpProtocolCore::McpProtocolSseParser;
QTEST_GUILESS_MAIN(McpProtocolSseParserTest)

McpProtocolSseParserTest::McpProtocolSseParserTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSseParserTest::shouldParseEvents()
{
    McpProtocolSseParser parser;
    const auto events = parser.feed("event: endpoint\ndata: /messages?sessionId=1\n\ndata: {\"a\":1}\nid: 42\n\n"_ba);
    QCOMPARE(events.count(), 2);
    QCOMPARE(events.at(0).event, "endpoint"_ba);
    QCOMPARE(events.at(0).data, "/messages?sessionId=1"_ba);
    QCOMPARE(events.at(1).event, "message"_ba);
    QCOMPARE(events.at(1).data, "{\"a\":1}"_ba);
    QCOMPARE(events.at(1).id, "42"_ba);
    QCOMPARE(parser.lastEventId(), "42"_ba);
}

void McpProtocolSseParserTest::shouldParseSplitChunks()
{
    McpProtocolSseParser parser;
    QVERIFY(parser.feed("event: mess"_ba).isEmpty());
    QVERIFY(parser.feed("age\nda"_ba).isEmpty());
    QVERIFY(parser.feed("ta: foo\n"_ba).isEmpty());
    const auto events = parser.feed("\n"_ba);
    QCOMPARE(events.count(), 1);
    QCOMPARE(events.at(0).data, "foo"_ba);
}

void McpProtocolSseParserTest::shouldParseMultiLineData()
{
    McpProtocolSseParser parser;
    const auto events = parser.feed("data: line1\ndata:line2\n\n"_ba);
    QCOMPARE(events.count(), 1);
    QCOMPARE(events.at(0).data, "line1\nline2"_ba);
}

void McpProtocolSseParserTest::shouldIgnoreComments()
{
    McpProtocolSseParser parser;
    QVERIFY(parser.feed(": keep-alive\n\n"_ba).isEmpty());
    const auto events = parser.feed(": ping\ndata: foo\n\n"_ba);
    QCOMPARE(events.count(), 1);
    QCOMPARE(events.at(0).data, "foo"_ba);
}

void McpProtocolSseParserTest::shouldSupportCrLf()
{
    McpProtocolSseParser parser;
    QVERIFY(parser.feed("data: foo\r"_ba).isEmpty());
    const auto events = parser.feed("\n\r\n"_ba);
    QCOMPARE(events.count(), 1);
    QCOMPARE(events.at(0).data, "foo"_ba);
}

void McpProtocolSseParserTest::shouldParseRetry()
{
    McpProtocolSseParser parser;
    QCOMPARE(parser.retry(), -1);
    QVERIFY(parser.feed("retry: 3000\n\n"_ba).isEmpty());
    QCOMPARE(parser.retry(), 3000);
    // Invalid value is ignored
    QVERIFY(parser.feed("retry: 12a\n\n"_ba).isEmpty());
    QCOMPARE(parser.retry(), 3000);
    parser.clear();
    QCOMPARE(parser.retry(), -1);
}

void McpProtocolSseParserTest::shouldKeepLastEventIdWhenConnectionIsReset()
{
    McpProtocolSseParser parser;
    QCOMPARE(parser.feed("id: 5\nretry: 100\ndata: foo\n\ndata: incomplete\n"_ba).count(), 1);
    parser.resetConnection();
    QCOMPARE(parser.lastEventId(), "5"_ba);
    QCOMPARE(parser.retry(), 100);
    // Incomplete event from previous connection is dropped
    const auto events = parser.feed("data: bar\n\n"_ba);
    QCOMPARE(events.count(), 1);
    QCOMPARE(events.at(0).data, "bar"_ba);
}

#include "moc_mcpprotocolsseparsertest.cpp"
