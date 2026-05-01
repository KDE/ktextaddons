/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpservertest.h"
#include "server/mcpserver.h"
#include <QStandardPaths>
#include <QTest>

QTEST_GUILESS_MAIN(McpServerTest)
using namespace Qt::Literals::StringLiterals;
McpServerTest::McpServerTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void McpServerTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpServer w;
    QVERIFY(w.serverUrl().isEmpty());
    QVERIFY(w.enabled());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.identifier().isEmpty());
    QVERIFY(!w.isValid());
}

void McpServerTest::shouldVerifyValidValue()
{
    TextAutoGenerateTextMcpProtocolCore::McpServer w;
    QVERIFY(!w.isValid());

    w.setName(u"foo"_s);
    QVERIFY(!w.isValid());

    w.setIdentifier("bla"_ba);
    QVERIFY(!w.isValid());

    w.setServerUrl(QUrl(u"bla"_s));
    QVERIFY(w.isValid());
}

#include "moc_mcpservertest.cpp"
