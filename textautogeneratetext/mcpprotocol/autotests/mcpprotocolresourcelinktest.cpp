/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourcelinktest.h"
#include "mcpprotocolresourcelink.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceLinkTest)

McpProtocolResourceLinkTest::McpProtocolResourceLinkTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceLinkTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolResourceLink w;
    // TODO
}
#include "moc_mcpprotocolresourcelinktest.cpp"
