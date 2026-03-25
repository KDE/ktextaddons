/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocollistresourcetemplatesrequesttest.h"
#include "mcpprotocollistresourcetemplatesrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolListResourceTemplatesRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolListResourceTemplatesRequestTest::McpProtocolListResourceTemplatesRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListResourceTemplatesRequestTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolListResourceTemplatesRequest w;
    QCOMPARE(w.type(), "resources/templates/list"_ba);
    QVERIFY(!w.params().has_value());
    // TODO
}
#include "moc_mcpprotocollistresourcetemplatesrequesttest.cpp"
