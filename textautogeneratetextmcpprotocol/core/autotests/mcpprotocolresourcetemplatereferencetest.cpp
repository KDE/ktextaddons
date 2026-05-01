/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourcetemplatereferencetest.h"
#include "impl/mcpprotocolresourcetemplatereference.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceTemplateReferenceTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolResourceTemplateReferenceTest::McpProtocolResourceTemplateReferenceTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceTemplateReferenceTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceTemplateReference w;
    QCOMPARE(w.type(), "ref/resource"_ba);
    QVERIFY(w.uri().isEmpty());
}
#include "moc_mcpprotocolresourcetemplatereferencetest.cpp"
