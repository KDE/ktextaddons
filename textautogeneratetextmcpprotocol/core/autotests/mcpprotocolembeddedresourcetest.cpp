/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolembeddedresourcetest.h"
#include "impl/mcpprotocolembeddedresource.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolEmbeddedResourceTest)

McpProtocolEmbeddedResourceTest::McpProtocolEmbeddedResourceTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolEmbeddedResourceTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolEmbeddedResource w;
    QCOMPARE(w.type(), "resource"_ba);
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.annotations().has_value());
}
#include "moc_mcpprotocolembeddedresourcetest.cpp"
