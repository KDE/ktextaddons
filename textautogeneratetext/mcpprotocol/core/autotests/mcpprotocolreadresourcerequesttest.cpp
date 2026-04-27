/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolreadresourcerequesttest.h"
#include "mcpprotocolreadresourcerequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolReadResourceRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolReadResourceRequestTest::McpProtocolReadResourceRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolReadResourceRequestTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolReadResourceRequest w;
    QCOMPARE(w.type(), "resources/read"_ba);
    // TODO
}
#include "moc_mcpprotocolreadresourcerequesttest.cpp"
