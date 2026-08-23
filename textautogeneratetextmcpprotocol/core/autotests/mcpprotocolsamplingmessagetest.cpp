/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsamplingmessagetest.h"
#include "impl/mcpprotocolsamplingmessage.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolSamplingMessageTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSamplingMessageTest::McpProtocolSamplingMessageTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolSamplingMessageTest::shouldHaveDefaultValues()
{
    const McpProtocolSamplingMessage w;
    QVERIFY(!w.meta().has_value());
    QCOMPARE(w.role(), McpProtocolUtils::Role::Unknown);
}

void McpProtocolSamplingMessageTest::shouldConvertJson()
{
    QJsonObject content;
    content["type"_L1] = u"text"_s;
    content["text"_L1] = u"Hello"_s;

    QJsonObject obj;
    obj["content"_L1] = content;
    obj["role"_L1] = u"user"_s;

    const auto message = McpProtocolSamplingMessage::fromJson(obj);
    QCOMPARE(message.role(), McpProtocolUtils::Role::User);
    const auto messageContent = message.content();
    const auto textContent = std::get_if<McpProtocolTextContent>(&messageContent);
    QVERIFY(textContent);
    QCOMPARE(textContent->text(), u"Hello"_s);
    QCOMPARE(McpProtocolSamplingMessage::toJson(message), obj);

    // A content array collapses into the QList alternative of the variant.
    QJsonObject secondContent;
    secondContent["type"_L1] = u"text"_s;
    secondContent["text"_L1] = u"World"_s;
    QJsonObject arrayObj;
    arrayObj["content"_L1] = QJsonArray{content, secondContent};
    arrayObj["role"_L1] = u"assistant"_s;

    const auto arrayMessage = McpProtocolSamplingMessage::fromJson(arrayObj);
    const auto arrayContent = arrayMessage.content();
    const auto blocks = std::get_if<QList<McpProtocolUtils::SamplingMessageContentBlock>>(&arrayContent);
    QVERIFY(blocks);
    QCOMPARE(blocks->count(), 2);
    QCOMPARE(McpProtocolSamplingMessage::toJson(arrayMessage), arrayObj);
}

#include "moc_mcpprotocolsamplingmessagetest.cpp"
