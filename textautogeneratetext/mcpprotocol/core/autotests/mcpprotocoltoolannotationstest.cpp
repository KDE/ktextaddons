/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltoolannotationstest.h"
#include "mcpprotocoltoolannotations.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolToolAnnotationsTest)

McpProtocolToolAnnotationsTest::McpProtocolToolAnnotationsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolAnnotationsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations w;
    QString mTitle;
    QVERIFY(w.destructiveHint());
    QVERIFY(!w.idempotentHint());
    QVERIFY(w.openWorldHint());
    QVERIFY(!w.readOnlyHint());
    QVERIFY(w.title().isEmpty());
}

#include "moc_mcpprotocoltoolannotationstest.cpp"
