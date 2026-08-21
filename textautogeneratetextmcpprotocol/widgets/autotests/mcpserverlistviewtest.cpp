/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpserverlistviewtest.h"
#include "server/mcpserverlistview.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(McpServerListViewTest)

McpServerListViewTest::McpServerListViewTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void McpServerListViewTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::McpServerListView w(nullptr);
    QVERIFY(!w.dragEnabled());
    // TODO
}
#include "moc_mcpserverlistviewtest.cpp"
