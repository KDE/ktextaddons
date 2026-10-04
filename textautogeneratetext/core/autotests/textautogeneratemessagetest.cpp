/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessagetest.h"
#include "core/textautogenerateanswerinfo.h"
#include "core/textautogeneratemessage.h"
#include "textautogenerate_autotest_helper.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextAutoGenerateMessageTest)
TextAutoGenerateMessageTest::TextAutoGenerateMessageTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateMessageTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateMessage msg;
    QVERIFY(msg.content().isEmpty());
    QCOMPARE(msg.sender(), TextAutoGenerateText::TextAutoGenerateMessage::Sender::Unknown);
    QCOMPARE(msg.dateTime(), -1);
    QVERIFY(!msg.isValid());
    QVERIFY(!msg.inProgress());
    QVERIFY(!msg.editingMode());
    QVERIFY(!msg.mouseHover());
    QVERIFY(!msg.textToSpeechInProgress());
    QVERIFY(msg.uuid().isEmpty());
    QVERIFY(msg.answerUuid().isEmpty());
    QVERIFY(msg.engineName().isEmpty());
    QVERIFY(msg.modelName().isEmpty());
    QVERIFY(msg.instanceName().isEmpty());
    QVERIFY(msg.tools().isEmpty());
    QCOMPARE(msg.numberOfTextSearched(), -1);
    QVERIFY(!msg.messageAttachments());

    // 10/05/2025 => size 224
    QVERIFY(msg.toolExchange().isEmpty());
    QCOMPARE(sizeof(TextAutoGenerateText::TextAutoGenerateMessage), 240);
}

void TextAutoGenerateMessageTest::shouldCheckFromString()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"user"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"llm"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::Assistant);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"system"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::System);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"tool"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::Tool);
}

void TextAutoGenerateMessageTest::shouldParseMessage_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<TextAutoGenerateText::TextAutoGenerateMessage>("expectedMessage");
    {
        TextAutoGenerateText::TextAutoGenerateMessage firstMessageRef;
        firstMessageRef.setAnswerUuid("b84a362695c34e5491b54e414192fb70");
        firstMessageRef.setDateTime(1753338999);
        firstMessageRef.setUuid("79aa1eac872647a2ac12cb56ddd00e1f");
        firstMessageRef.setContent(u"test1"_s);
        firstMessageRef.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
        firstMessageRef.generateHtml();

        QTest::addRow("test1user") << u"test1user"_s << firstMessageRef;
    }
    {
        TextAutoGenerateText::TextAutoGenerateMessage firstMessageLlmRef;
        firstMessageLlmRef.setAnswerUuid("foo");
        firstMessageLlmRef.setDateTime(1753338990);
        firstMessageLlmRef.setUuid("136ccbbe9e1e4d6a90c6b9917daf9a29");
        firstMessageLlmRef.setContent(u"test llm"_s);
        firstMessageLlmRef.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::Assistant);
        firstMessageLlmRef.generateHtml();
        TextAutoGenerateText::TextAutoGenerateAnswerInfo info;
        info.setEngineName(u"openai"_s);
        info.setInstanceName(u"test openai"_s);
        info.setModelName(u"gpt-3.5-turbo-16k"_s);
        firstMessageLlmRef.setMessageInfo(info);

        QTest::addRow("test1llm") << u"test1llm"_s << firstMessageLlmRef;
    }
}

void TextAutoGenerateMessageTest::shouldParseMessage()
{
    QFETCH(QString, name);
    QFETCH(TextAutoGenerateText::TextAutoGenerateMessage, expectedMessage);
    const QString originalJsonFile = QLatin1StringView(TEXTAUTOGENERATE_DATA_DIR) + "/json/"_L1 + name + ".json"_L1;

    const QJsonObject obj = AutoTestHelper::loadJsonObject(originalJsonFile);
    const TextAutoGenerateText::TextAutoGenerateMessage originalMessage = TextAutoGenerateText::TextAutoGenerateMessage::deserialize(obj);
    const bool messageIsEqual = (originalMessage == expectedMessage);
    if (!messageIsEqual) {
        qDebug() << "originalMessage " << originalMessage;
        qDebug() << "ExpectedMessage " << expectedMessage;
    }
    QVERIFY(messageIsEqual);
}

void TextAutoGenerateMessageTest::shouldSerializeMessage()
{
    {
        TextAutoGenerateText::TextAutoGenerateMessage firstMessageRef;
        firstMessageRef.setAnswerUuid("b84a362695c34e5491b54e414192fb70");
        firstMessageRef.setDateTime(1753338999);
        firstMessageRef.setUuid("79aa1eac872647a2ac12cb56ddd00e1f");
        firstMessageRef.setContent(u"test1"_s);
        firstMessageRef.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
        firstMessageRef.generateHtml();

        const QByteArray ba = TextAutoGenerateText::TextAutoGenerateMessage::serialize(firstMessageRef);
        const TextAutoGenerateText::TextAutoGenerateMessage output =
            TextAutoGenerateText::TextAutoGenerateMessage::deserialize(QCborValue::fromCbor(ba).toMap().toJsonObject());
        QCOMPARE(firstMessageRef, output);
    }
    {
        TextAutoGenerateText::TextAutoGenerateMessage firstMessageLlmRef;
        firstMessageLlmRef.setAnswerUuid("foo");
        firstMessageLlmRef.setDateTime(1753338990);
        firstMessageLlmRef.setUuid("136ccbbe9e1e4d6a90c6b9917daf9a29");
        firstMessageLlmRef.setContent(u"test llm"_s);
        firstMessageLlmRef.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::Assistant);
        firstMessageLlmRef.generateHtml();
        TextAutoGenerateText::TextAutoGenerateAnswerInfo info;
        info.setEngineName(u"openai"_s);
        info.setInstanceName(u"test openai"_s);
        info.setModelName(u"gpt-3.5-turbo-16k"_s);
        firstMessageLlmRef.setMessageInfo(info);
        const QByteArray ba = TextAutoGenerateText::TextAutoGenerateMessage::serialize(firstMessageLlmRef);
        const TextAutoGenerateText::TextAutoGenerateMessage output =
            TextAutoGenerateText::TextAutoGenerateMessage::deserialize(QCborValue::fromCbor(ba).toMap().toJsonObject());
        QCOMPARE(firstMessageLlmRef, output);
    }

    {
        TextAutoGenerateText::TextAutoGenerateMessage firstMessageRef;
        firstMessageRef.setAnswerUuid("b84a362695c34e5491b54e414192fb70");
        firstMessageRef.setDateTime(1753338999);
        firstMessageRef.setUuid("79aa1eac872647a2ac12cb56ddd00e1f");
        firstMessageRef.setContent(u"test1"_s);
        firstMessageRef.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
        firstMessageRef.generateHtml();

        TextAutoGenerateText::TextAutoGenerateAttachments t;
        QList<TextAutoGenerateText::TextAutoGenerateAttachment> list;
        {
            TextAutoGenerateText::TextAutoGenerateAttachment att;
            att.setContent("sdfsdf"_ba);
            att.setMimeType("mp4");
            att.setName(u"foo"_s);
            att.setAttachmentId("idttt"_ba);
            att.setAttachmentType(TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Audio);
            list.append(att);
        }
        {
            TextAutoGenerateText::TextAutoGenerateAttachment att;
            att.setContent("foo11"_ba);
            att.setMimeType("doc");
            att.setName(u"foo2"_s);
            att.setAttachmentId("idttt2"_ba);
            att.setAttachmentType(TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::File);
            list.append(att);
        }
        t.setMessageAttachments(list);
        firstMessageRef.setMessageAttachments(t);

        const QByteArray ba = TextAutoGenerateText::TextAutoGenerateMessage::serialize(firstMessageRef);
        const TextAutoGenerateText::TextAutoGenerateMessage output =
            TextAutoGenerateText::TextAutoGenerateMessage::deserialize(QCborValue::fromCbor(ba).toMap().toJsonObject());
        QCOMPARE(firstMessageRef, output);
    }
}

void TextAutoGenerateMessageTest::shouldSerializeReplyInfo()
{
    TextAutoGenerateText::TextAutoGenerateMessage message;
    message.setUuid("message-id");
    message.setContent(u"answer"_s);
    message.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::Assistant);
    message.setDateTime(1753338990);

    TextAutoGenerateText::TextAutoGenerateTextReplyInfo replyInfo;
    replyInfo.replyType = TextAutoGenerateText::TextAutoGenerateTextReplyInfo::ReplyType::OpenAI;
    replyInfo.totalDuration = std::chrono::nanoseconds(111);
    replyInfo.loadDuration = std::chrono::nanoseconds(222);
    replyInfo.promptEvalTokenCount = 333;
    replyInfo.promptEvalDuration = std::chrono::nanoseconds(444);
    replyInfo.tokenCount = 555;
    replyInfo.completionTokens = 666;
    replyInfo.promptTokens = 777;
    replyInfo.duration = std::chrono::nanoseconds(888);
    message.setInfo(replyInfo);

    const QByteArray ba = TextAutoGenerateText::TextAutoGenerateMessage::serialize(message);
    const TextAutoGenerateText::TextAutoGenerateMessage output =
        TextAutoGenerateText::TextAutoGenerateMessage::deserialize(QCborValue::fromCbor(ba).toMap().toJsonObject());
    QCOMPARE(message, output);
}

namespace
{
TextAutoGenerateText::TextAutoGenerateMessage messageWithToolExchange()
{
    TextAutoGenerateText::TextAutoGenerateMessage message;
    message.setUuid("message-id");
    message.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::Assistant);
    message.setDateTime(1753338990);
    TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo toolCall;
    toolCall.id = "call_1";
    toolCall.toolName = "weather";
    toolCall.arguments = QJsonObject{{"city"_L1, u"Paris"_s}, {"days"_L1, 2}};
    message.appendToolExchange(u"Let me check"_s, {toolCall}, {{"call_1"_ba, u"Sunny"_s}});
    message.setContent(u"It's sunny"_s);
    return message;
}
}

void TextAutoGenerateMessageTest::shouldSerializeToolExchange()
{
    const TextAutoGenerateText::TextAutoGenerateMessage message = messageWithToolExchange();
    QCOMPARE(message.toolExchange().count(), 2);
    const QByteArray ba = TextAutoGenerateText::TextAutoGenerateMessage::serialize(message);
    const TextAutoGenerateText::TextAutoGenerateMessage output =
        TextAutoGenerateText::TextAutoGenerateMessage::deserialize(QCborValue::fromCbor(ba).toMap().toJsonObject());
    QCOMPARE(output.toolExchange(), message.toolExchange());
    QCOMPARE(message, output);
}

void TextAutoGenerateMessageTest::shouldConvertToolExchangeToOpenAI()
{
    const auto list = messageWithToolExchange().convertToChatJson(true, true, TextAutoGenerateText::TextAutoGenerateMessage::ToolCallFormat::OpenAI);
    QCOMPARE(list.count(), 3);
    // Assistant asks tool
    const QJsonObject assistant = list.at(0);
    QCOMPARE(assistant.value("role"_L1).toString(), u"assistant"_s);
    QCOMPARE(assistant.value("content"_L1).toString(), u"Let me check"_s);
    const QJsonObject toolCall = assistant.value("tool_calls"_L1).toArray().at(0).toObject();
    QCOMPARE(toolCall.value("id"_L1).toString(), u"call_1"_s);
    QCOMPARE(toolCall.value("type"_L1).toString(), u"function"_s);
    QCOMPARE(toolCall.value("function"_L1).toObject().value("name"_L1).toString(), u"weather"_s);
    // Arguments are a json string
    QCOMPARE(toolCall.value("function"_L1).toObject().value("arguments"_L1).toString(), uR"({"city":"Paris","days":2})"_s);
    // Tool result
    QCOMPARE(list.at(1), QJsonObject({{"role"_L1, u"tool"_s}, {"tool_call_id"_L1, u"call_1"_s}, {"content"_L1, u"Sunny"_s}}));
    // Final answer
    QCOMPARE(list.at(2).value("role"_L1).toString(), u"assistant"_s);
    QCOMPARE(list.at(2).value("content"_L1).toString(), u"It's sunny"_s);
}

void TextAutoGenerateMessageTest::shouldConvertToolExchangeToOllama()
{
    const auto list = messageWithToolExchange().convertToChatJson(true, true, TextAutoGenerateText::TextAutoGenerateMessage::ToolCallFormat::Ollama);
    QCOMPARE(list.count(), 3);
    const QJsonObject function = list.at(0).value("tool_calls"_L1).toArray().at(0).toObject().value("function"_L1).toObject();
    QCOMPARE(function.value("name"_L1).toString(), u"weather"_s);
    // Arguments are an object
    QCOMPARE(function.value("arguments"_L1).toObject(), QJsonObject({{"city"_L1, u"Paris"_s}, {"days"_L1, 2}}));
    QCOMPARE(list.at(1), QJsonObject({{"role"_L1, u"tool"_s}, {"tool_name"_L1, u"weather"_s}, {"content"_L1, u"Sunny"_s}}));
}

// TODO add image support

#include "moc_textautogeneratemessagetest.cpp"
