/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessagetest.h"
#include "core/textautogeneratemessage.h"
#include "textautogenerate_autotest_helper.h"
#include <QJsonDocument>
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
    TextAutoGenerateText::TextAutoGenerateMessage msg;
    QVERIFY(msg.content().isEmpty());
    QCOMPARE(msg.sender(), TextAutoGenerateText::TextAutoGenerateMessage::Sender::Unknown);
    QCOMPARE(msg.dateTime(), -1);
    QVERIFY(!msg.isValid());
    QVERIFY(!msg.inProgress());
    QVERIFY(!msg.editingMode());
    QVERIFY(!msg.mouseHover());
    QVERIFY(msg.uuid().isEmpty());
    QVERIFY(msg.answerUuid().isEmpty());
    QVERIFY(msg.engineName().isEmpty());
    QVERIFY(msg.modelName().isEmpty());
    QVERIFY(msg.instanceName().isEmpty());

    // 10/05/2025 => size 224
    QCOMPARE(sizeof(TextAutoGenerateText::TextAutoGenerateMessage), 152);
}

void TextAutoGenerateMessageTest::shouldCheckFromString()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"user"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"llm"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::Assistant);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"system"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::System);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"tool"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::Tool);
}
#if 0
void TextAutoGenerateMessageTest::shouldParseMessage_data()
{
    QTest::addColumn<QString>("name");
    QTest::addColumn<TextAutoGenerateText::TextAutoGenerateMessage>("expectedMessage");

    TextAutoGenerateText::TextAutoGenerateMessage firstMessageRef;
    firstMessageRef.setAnswerUuid("b84a362695c34e5491b54e414192fb70");
    firstMessageRef.setDateTime(1753338999);
    firstMessageRef.setUuid("79aa1eac872647a2ac12cb56ddd00e1f");
    firstMessageRef.setContent(u"test1"_s);
    firstMessageRef.setSender(TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);

    QTest::addRow("test1user") << u"test1user"_s << firstMessageRef;
}


void TextAutoGenerateMessageTest::shouldParseMessage()
{
    QFETCH(QString, name);
    QFETCH(TextAutoGenerateText::TextAutoGenerateMessage, expectedMessage);
    const QString originalJsonFile = QLatin1StringView(TEXTAUTOGENERATE_DATA_DIR) + "/json/"_L1 + name + ".json"_L1;
    QFile f(originalJsonFile);
    QVERIFY(f.open(QIODevice::ReadOnly));
    const QByteArray content = f.readAll();
    f.close();

    const QJsonObject obj = AutoTestHelper::loadJsonObject(originalJsonFile);
    const TextAutoGenerateText::TextAutoGenerateMessage originalMessage = TextAutoGenerateText::TextAutoGenerateMessage::deserialize(obj);
    const bool messageIsEqual = (originalMessage == expectedMessage);
    if (!messageIsEqual) {
        qDebug() << "originalMessage " << originalMessage;
        qDebug() << "ExpectedMessage " << expectedMessage;
    }
    QVERIFY(messageIsEqual);
}
#endif

#include "moc_textautogeneratemessagetest.cpp"
