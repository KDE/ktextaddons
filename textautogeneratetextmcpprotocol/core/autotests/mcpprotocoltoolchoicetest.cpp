/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltoolchoicetest.h"
#include "impl/mcpprotocoltoolchoice.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolToolChoiceTest)

McpProtocolToolChoiceTest::McpProtocolToolChoiceTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolChoiceTest::shouldhaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolChoice w;
    QCOMPARE(w.mode(), TextAutoGenerateTextMcpProtocolCore::McpProtocolToolChoice::Mode::Unknown);
}

void McpProtocolToolChoiceTest::shouldReturnUnknownForInvalidMode()
{
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolToolChoice::convertModeFromString(u"foo"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolToolChoice::Mode::Unknown);
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolToolChoice::convertModeFromString(u"auto"_s),
             TextAutoGenerateTextMcpProtocolCore::McpProtocolToolChoice::Mode::Auto);
}

#include "moc_mcpprotocoltoolchoicetest.cpp"
