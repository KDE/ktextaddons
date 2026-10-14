/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltextresourcecontentstest.h"
#include "impl/mcpprotocoltextresourcecontents.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolTextResourceContentsTest)

McpProtocolTextResourceContentsTest::McpProtocolTextResourceContentsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolTextResourceContentsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolTextResourceContents w;
    QVERIFY(w.text().isEmpty());
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.mimeType().has_value());
    QVERIFY(w.uri().isEmpty());
}

void McpProtocolTextResourceContentsTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QVERIFY(McpProtocolTextResourceContents::fromJson(QJsonObject{{"uri"_L1, u"file:///foo"_s}, {"text"_L1, u"bla"_s}}).isValid());
    // Missing uri
    QCOMPARE(McpProtocolTextResourceContents::fromJson(QJsonObject{{"text"_L1, u"bla"_s}}), McpProtocolTextResourceContents());
    // Missing text
    QCOMPARE(McpProtocolTextResourceContents::fromJson(QJsonObject{{"uri"_L1, u"file:///foo"_s}}), McpProtocolTextResourceContents());
}

#include "moc_mcpprotocoltextresourcecontentstest.cpp"
