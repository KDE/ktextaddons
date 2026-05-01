/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsubscriberequesttest.h"
#include "impl/mcpprotocolsubscriberequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSubscribeRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolSubscribeRequestTest::McpProtocolSubscribeRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSubscribeRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolSubscribeRequest w;
    QCOMPARE(w.type(), "resources/subscribe"_ba);
    // TODO
}
#include "moc_mcpprotocolsubscriberequesttest.cpp"
