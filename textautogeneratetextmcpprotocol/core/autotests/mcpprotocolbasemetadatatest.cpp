/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolbasemetadatatest.h"
#include "impl/mcpprotocolbasemetadata.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolBaseMetadataTest)

McpProtocolBaseMetadataTest::McpProtocolBaseMetadataTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolBaseMetadataTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolBaseMetadata w;
    QVERIFY(!w.title().has_value());
    QVERIFY(w.name().isEmpty());
}
void McpProtocolBaseMetadataTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject obj;
    obj["name"_L1] = u"foo"_s;
    QCOMPARE(McpProtocolBaseMetadata::fromJson(obj).name(), u"foo"_s);

    QCOMPARE(McpProtocolBaseMetadata::fromJson(QJsonObject()), McpProtocolBaseMetadata());

    obj["name"_L1] = 42;
    QCOMPARE(McpProtocolBaseMetadata::fromJson(obj), McpProtocolBaseMetadata());
}

#include "moc_mcpprotocolbasemetadatatest.cpp"
