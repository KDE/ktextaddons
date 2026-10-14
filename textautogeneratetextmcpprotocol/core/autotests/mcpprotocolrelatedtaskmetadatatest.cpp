/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolrelatedtaskmetadatatest.h"
#include "impl/mcpprotocolrelatedtaskmetadata.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolRelatedTaskMetadataTest)
using namespace Qt::Literals::StringLiterals;

McpProtocolRelatedTaskMetadataTest::McpProtocolRelatedTaskMetadataTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolRelatedTaskMetadataTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolRelatedTaskMetadata w;
    QVERIFY(w.taskId().isEmpty());
}

void McpProtocolRelatedTaskMetadataTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolRelatedTaskMetadata;
    const QJsonObject obj{{"taskId"_L1, u"t1"_s}};
    QCOMPARE(McpProtocolRelatedTaskMetadata::fromJson(obj).taskId(), u"t1"_s);
    QCOMPARE(McpProtocolRelatedTaskMetadata::fromJson(QJsonObject()), McpProtocolRelatedTaskMetadata());
    QCOMPARE(McpProtocolRelatedTaskMetadata::fromJson(QJsonObject{{"taskId"_L1, 1}}), McpProtocolRelatedTaskMetadata());
}

#include "moc_mcpprotocolrelatedtaskmetadatatest.cpp"
