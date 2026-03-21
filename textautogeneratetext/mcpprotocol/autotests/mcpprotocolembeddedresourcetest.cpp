/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolembeddedresourcetest.h"
#include "mcpprotocolembeddedresource.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolEmbeddedResourceTest)

McpProtocolEmbeddedResourceTest::McpProtocolEmbeddedResourceTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolEmbeddedResourceTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolEmbeddedResource w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.annotations().has_value());
    // TODO EmbeddedResourceResource QVERIFY(w.prompts().isEmpty());
}
#include "moc_mcpprotocolembeddedresourcetest.cpp"
