/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolrelatedtaskmetadatatest.h"
#include "mcpprotocolrelatedtaskmetadata.h"
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolRelatedTaskMetadataTest)

McpProtocolRelatedTaskMetadataTest::McpProtocolRelatedTaskMetadataTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolRelatedTaskMetadataTest::shouldHaveDefaultValues()
{
    const McpProtocol::McpProtocolRelatedTaskMetadata w;
    QVERIFY(w.taskId().isEmpty());
}
#include "moc_mcpprotocolrelatedtaskmetadatatest.cpp"
