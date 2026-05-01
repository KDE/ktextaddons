/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourcelinktest.h"
#include "impl/mcpprotocolresourcelink.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceLinkTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolResourceLinkTest::McpProtocolResourceLinkTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceLinkTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceLink w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.annotations().has_value());
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.mimeType().has_value());
    QVERIFY(!w.size().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.uri().isEmpty());
    QCOMPARE(w.type(), "resource_link"_ba);
}
#include "moc_mcpprotocolresourcelinktest.cpp"
