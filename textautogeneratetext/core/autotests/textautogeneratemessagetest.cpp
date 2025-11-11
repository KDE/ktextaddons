/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessagetest.h"
#include "core/textautogenerateanswerinfo.h"
#include "core/textautogeneratemessage.h"
#include "textautogenerate_autotest_helper.h"
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

    // 10/05/2025 => size 224
    QCOMPARE(sizeof(TextAutoGenerateText::TextAutoGenerateMessage), 160);
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
            att.setAttachmentType(TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Audio);
            list.append(att);
        }
        {
            TextAutoGenerateText::TextAutoGenerateAttachment att;
            att.setContent("foo11"_ba);
            att.setMimeType("doc");
            att.setName(u"foo2"_s);
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

// TODO add image support

#include "moc_textautogeneratemessagetest.cpp"
