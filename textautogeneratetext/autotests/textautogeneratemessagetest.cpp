/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessagetest.h"
#include "core/textautogeneratemessage.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateMessageTest)
TextAutoGenerateMessageTest::TextAutoGenerateMessageTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateMessageTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutoGenerateMessage msg;
    QVERIFY(msg.content().isEmpty());
    QCOMPARE(msg.sender(), TextAutogenerateText::TextAutoGenerateMessage::Sender::Unknown);
    QCOMPARE(msg.dateTime(), -1);
    QVERIFY(!msg.isValid());
    QVERIFY(!msg.inProgress());
    QVERIFY(msg.uuid().isEmpty());
}

#include "moc_textautogeneratemessagetest.cpp"
