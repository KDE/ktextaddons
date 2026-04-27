/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourcetest.h"
#include "mcpprotocolresource.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceTest)

McpProtocolResourceTest::McpProtocolResourceTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolResource w;
    QVERIFY(w.uri().isEmpty());
    QVERIFY(!w.title().has_value());
    QVERIFY(!w.size().has_value());
    QVERIFY(w.name().isEmpty());
    QVERIFY(!w.mimeType().has_value());
    QVERIFY(!w.icons().has_value());
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.annotations().has_value());
    QVERIFY(!w.meta().has_value());
}
#include "moc_mcpprotocolresourcetest.cpp"
