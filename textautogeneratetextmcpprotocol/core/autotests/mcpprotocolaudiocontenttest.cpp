/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolaudiocontenttest.h"
#include "impl/mcpprotocolaudiocontent.h"
#include <QJsonArray>
#include <QJsonObject>
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
void McpProtocolAudioContentTest::shouldRejectMissingRequiredFields()
{
    using namespace Qt::Literals::StringLiterals;
    using namespace TextAutoGenerateTextMcpProtocolCore;
    QJsonObject obj;
    obj["type"_L1] = u"audio"_s;
    obj["data"_L1] = u"AAAA"_s;
    obj["mimeType"_L1] = u"audio/wav"_s;
    QVERIFY(McpProtocolAudioContent::fromJson(obj).isValid());

    QJsonObject missingData = obj;
    missingData.remove("data"_L1);
    QCOMPARE(McpProtocolAudioContent::fromJson(missingData), McpProtocolAudioContent());

    QJsonObject missingMimeType = obj;
    missingMimeType.remove("mimeType"_L1);
    QCOMPARE(McpProtocolAudioContent::fromJson(missingMimeType), McpProtocolAudioContent());
}

#include "moc_mcpprotocolaudiocontenttest.cpp"
