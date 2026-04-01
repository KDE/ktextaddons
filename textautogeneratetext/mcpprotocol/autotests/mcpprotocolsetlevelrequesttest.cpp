/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsetlevelrequesttest.h"
#include "mcpprotocolsetlevelrequest.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSetLevelRequestTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolSetLevelRequestTest::McpProtocolSetLevelRequestTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSetLevelRequestTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolSetLevelRequest w;
    QCOMPARE(w.type(), "logging/setLevel"_ba);
    // TODO
}
#include "moc_mcpprotocolsetlevelrequesttest.cpp"
