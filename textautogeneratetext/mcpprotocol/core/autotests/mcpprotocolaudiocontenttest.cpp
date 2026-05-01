/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolaudiocontenttest.h"
#include "impl/mcpprotocolaudiocontent.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolAudioContentTest)

McpProtocolAudioContentTest::McpProtocolAudioContentTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolAudioContentTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolAudioContent w;
    QVERIFY(w.data().isEmpty());
    QVERIFY(!w.annotations());
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.mimeType().isEmpty());
}
#include "moc_mcpprotocolaudiocontenttest.cpp"
