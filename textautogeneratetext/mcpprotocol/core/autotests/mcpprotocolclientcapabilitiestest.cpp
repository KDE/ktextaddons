/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolclientcapabilitiestest.h"
#include "mcpprotocolclientcapabilities.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolClientCapabilitiesTest)

McpProtocolClientCapabilitiesTest::McpProtocolClientCapabilitiesTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolClientCapabilitiesTest::shouldhaveDefaultValues()
{
    const McpProtocol::McpProtocolClientCapabilities w;
    // TODO
}

#include "moc_mcpprotocolclientcapabilitiestest.cpp"
