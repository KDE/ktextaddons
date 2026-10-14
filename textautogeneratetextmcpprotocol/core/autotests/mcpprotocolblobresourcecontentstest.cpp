/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolblobresourcecontentstest.h"
#include "impl/mcpprotocolblobresourcecontents.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolBlobResourceContentsTest)

McpProtocolBlobResourceContentsTest::McpProtocolBlobResourceContentsTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolBlobResourceContentsTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolBlobResourceContents w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(!w.mimeType().has_value());
    QVERIFY(w.uri().isEmpty());
    QVERIFY(w.blob().isEmpty());
}
void McpProtocolBlobResourceContentsTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject obj;
    obj["uri"_L1] = u"file:///tmp/foo"_s;
    obj["blob"_L1] = u"AAAA"_s;
    QVERIFY(McpProtocolBlobResourceContents::fromJson(obj).isValid());

    QJsonObject missingUri = obj;
    missingUri.remove("uri"_L1);
    QCOMPARE(McpProtocolBlobResourceContents::fromJson(missingUri), McpProtocolBlobResourceContents());

    QJsonObject missingBlob = obj;
    missingBlob.remove("blob"_L1);
    QCOMPARE(McpProtocolBlobResourceContents::fromJson(missingBlob), McpProtocolBlobResourceContents());
}

#include "moc_mcpprotocolblobresourcecontentstest.cpp"
