/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistpromptsrequesttest.h"
#include "mcpprotocollistpromptsrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListPromptsRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolListPromptsRequestTest::McpProtocolListPromptsRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListPromptsRequestTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolListPromptsRequest w;
    QCOMPARE(w.type(), "prompts/list"_ba);
    QVERIFY(!w.params().has_value());
    // TODO
}
#include "moc_mcpprotocollistpromptsrequesttest.cpp"
