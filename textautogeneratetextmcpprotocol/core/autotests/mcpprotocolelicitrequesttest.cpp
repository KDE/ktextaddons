/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolelicitrequesttest.h"
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequest>

QTEST_GUILESS_MAIN(McpProtocolElicitRequestTest)

McpProtocolElicitRequestTest::McpProtocolElicitRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolElicitRequestTest::shouldHaveDefaultValues()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest request;
    QCOMPARE(request.type(), "elicitation/create");
}

#include "moc_mcpprotocolelicitrequesttest.cpp"
