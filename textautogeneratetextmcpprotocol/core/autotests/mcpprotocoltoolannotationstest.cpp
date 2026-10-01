/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoltoolannotationstest.h"
#include "impl/mcpprotocoltoolannotations.h"
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpProtocolToolAnnotationsTest)

McpProtocolToolAnnotationsTest::McpProtocolToolAnnotationsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolToolAnnotationsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations w;
    QVERIFY(!w.destructiveHint().has_value());
    QVERIFY(!w.idempotentHint().has_value());
    QVERIFY(!w.openWorldHint().has_value());
    QVERIFY(!w.readOnlyHint().has_value());
    QVERIFY(!w.title().has_value());
    QVERIFY(TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations::toJson(w).isEmpty());
}

void McpProtocolToolAnnotationsTest::shouldLoadAndSaveOnlyPresentValues()
{
    QJsonObject obj;
    obj["readOnlyHint"_L1] = true;
    obj["destructiveHint"_L1] = false;
    const auto annotations = TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations::fromJson(obj);
    QCOMPARE(*annotations.readOnlyHint(), true);
    QCOMPARE(*annotations.destructiveHint(), false);
    QVERIFY(!annotations.idempotentHint().has_value());
    QVERIFY(!annotations.openWorldHint().has_value());
    QVERIFY(!annotations.title().has_value());
    QCOMPARE(TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations::toJson(annotations), obj);
}

#include "moc_mcpprotocoltoolannotationstest.cpp"
