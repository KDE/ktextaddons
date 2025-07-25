/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessagetest.h"
#include "core/textautogeneratemessage.h"
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
    QCOMPARE(sizeof(TextAutoGenerateText::TextAutoGenerateMessage), 184);
}

void TextAutoGenerateMessageTest::shouldCheckFromString()
{
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"user"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::User);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"llm"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::Assistant);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"system"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::System);
    QCOMPARE(TextAutoGenerateText::TextAutoGenerateMessage::senderFromString(u"tool"_s), TextAutoGenerateText::TextAutoGenerateMessage::Sender::Tool);
}

#include "moc_textautogeneratemessagetest.cpp"
