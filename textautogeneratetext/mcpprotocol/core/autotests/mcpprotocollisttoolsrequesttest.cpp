/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollisttoolsrequesttest.h"
#include "mcpprotocollisttoolsrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListToolsRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolListToolsRequestTest::McpProtocolListToolsRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListToolsRequestTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolListToolsRequest w;
    QCOMPARE(w.type(), "tools/list"_ba);
    // TODO
}
#include "moc_mcpprotocollisttoolsrequesttest.cpp"
