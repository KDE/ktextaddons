/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistrootsresulttest.h"
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListRootsResult>

QTEST_GUILESS_MAIN(McpProtocolListRootsResultTest)

McpProtocolListRootsResultTest::McpProtocolListRootsResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListRootsResultTest::shouldHaveDefaultValues()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolListRootsResult request;
    QVERIFY(request.roots().isEmpty());
}

#include "moc_mcpprotocollistrootsresulttest.cpp"
