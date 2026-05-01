/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourcetemplatetest.h"
#include "impl/mcpprotocolresourcetemplate.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceTemplateTest)

McpProtocolResourceTemplateTest::McpProtocolResourceTemplateTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceTemplateTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceTemplate w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.annotations().has_value());
    QVERIFY(!w.description().has_value());
    QVERIFY(!w.icons().has_value());
    QVERIFY(!w.mimeType().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(w.uriTemplate().isEmpty());
    QVERIFY(w.name().isEmpty());
}
#include "moc_mcpprotocolresourcetemplatetest.cpp"
