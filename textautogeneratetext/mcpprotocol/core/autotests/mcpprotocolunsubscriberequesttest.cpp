/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolunsubscriberequesttest.h"
#include "mcpprotocolunsubscriberequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolUnsubscribeRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolUnsubscribeRequestTest::McpProtocolUnsubscribeRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolUnsubscribeRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolUnsubscribeRequest w;
    QCOMPARE(w.type(), "resources/unsubscribe"_ba);
    // TODO
}
#include "moc_mcpprotocolunsubscriberequesttest.cpp"
