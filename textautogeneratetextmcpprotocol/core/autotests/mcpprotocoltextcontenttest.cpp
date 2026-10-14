/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltextcontenttest.h"
#include "impl/mcpprotocoltextcontent.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolTextContentTest)

McpProtocolTextContentTest::McpProtocolTextContentTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolTextContentTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolTextContent w;
    QVERIFY(w.text().isEmpty());
    QVERIFY(!w.annotations().has_value());
    QVERIFY(!w.meta().has_value());
}

void McpProtocolTextContentTest::shouldRejectMissingRequiredFields()
{
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QCOMPARE(McpProtocolTextContent::fromJson(QJsonObject{{"type"_L1, u"text"_s}, {"text"_L1, u"Hello"_s}}).text(), u"Hello"_s);
    // Missing text
    QCOMPARE(McpProtocolTextContent::fromJson(QJsonObject{{"type"_L1, u"text"_s}}), McpProtocolTextContent());
    // text is not a string
    QCOMPARE(McpProtocolTextContent::fromJson(QJsonObject{{"type"_L1, u"text"_s}, {"text"_L1, 2}}), McpProtocolTextContent());
}

#include "moc_mcpprotocoltextcontenttest.cpp"
