/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolcompleterequesttest.h"
#include "impl/mcpprotocolcompleterequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolCompleteRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolCompleteRequestTest::McpProtocolCompleteRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolCompleteRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolCompleteRequest w;
    QCOMPARE(w.type(), "completion/complete"_ba);
    // TODO
}
#include "moc_mcpprotocolcompleterequesttest.cpp"
