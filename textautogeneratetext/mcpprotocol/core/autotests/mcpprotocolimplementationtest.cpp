/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolimplementationtest.h"
#include "mcpprotocolimplementation.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolImplementationTest)

McpProtocolImplementationTest::McpProtocolImplementationTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolImplementationTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolImplementation w;
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.icons().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(!w.websiteUrl().has_value());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.version().isEmpty());
}
#include "moc_mcpprotocolimplementationtest.cpp"
