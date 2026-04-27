/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistresourcesrequesttest.h"
#include "mcpprotocollistresourcesrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListResourcesRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolListResourcesRequestTest::McpProtocolListResourcesRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListResourcesRequestTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourcesRequest w;
    QCOMPARE(w.type(), "resources/list"_ba);
    // TODO
}
#include "moc_mcpprotocollistresourcesrequesttest.cpp"
