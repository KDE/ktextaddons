/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttospeechenqueuemanagertest.h"
#include "core/texttospeech/textautogeneratetexttospeechenqueuemanager.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextToSpeechEnqueueManagerTest)

using namespace TextAutoGenerateText;

static TextAutoGenerateTextToSpeechEnqueueInfo createInfo(const QByteArray &chatId, const QByteArray &messageId)
{
    TextAutoGenerateTextToSpeechEnqueueInfo info;
    info.setChatId(chatId);
    info.setMessageId(messageId);
    return info;
}

TextAutoGenerateTextToSpeechEnqueueManagerTest::TextAutoGenerateTextToSpeechEnqueueManagerTest(QObject *parent)
    : QObject(parent)
{
}

void TextAutoGenerateTextToSpeechEnqueueManagerTest::shouldHaveDefaultValues()
{
    TextAutoGenerateTextToSpeechEnqueueManager m;
    QVERIFY(m.enqueueList().isEmpty());
    QVERIFY(!m.value(0).isValid());
    QVERIFY(!m.value(-1).isValid());
}

void TextAutoGenerateTextToSpeechEnqueueManagerTest::shouldInsertAndKeepIndex()
{
    TextAutoGenerateTextToSpeechEnqueueManager m;
    const auto first = createInfo("chat1", "message1");
    const auto second = createInfo("chat1", "message2");
    m.insert(first);
    m.insert(second);
    QCOMPARE(m.enqueueList().count(), 2);
    QCOMPARE(m.value(0), first);
    QCOMPARE(m.value(1), second);
    QVERIFY(m.contains(first));
    QVERIFY(m.contains(second));
    QVERIFY(!m.contains(createInfo("chat1", "message3")));
    // Same messageId in another chat is a different element.
    QVERIFY(!m.contains(createInfo("chat2", "message1")));
}

void TextAutoGenerateTextToSpeechEnqueueManagerTest::shouldNotContainsInvalidInfo()
{
    TextAutoGenerateTextToSpeechEnqueueManager m;
    // We can have several invalid elements, they still take a slot in the queue.
    const TextAutoGenerateTextToSpeechEnqueueInfo invalid;
    QVERIFY(!m.contains(invalid));
    m.insert(invalid);
    QVERIFY(!m.contains(invalid));
    m.insert(invalid);
    QCOMPARE(m.enqueueList().count(), 2);
    QVERIFY(!m.contains(createInfo("chat1", QByteArray())));
    QVERIFY(!m.contains(createInfo(QByteArray(), "message1")));
}

void TextAutoGenerateTextToSpeechEnqueueManagerTest::shouldRemoveLastOnly()
{
    TextAutoGenerateTextToSpeechEnqueueManager m;
    m.removeLast();
    QVERIFY(m.enqueueList().isEmpty());

    const auto first = createInfo("chat1", "message1");
    const auto second = createInfo("chat1", "message2");
    m.insert(first);
    m.insert(second);
    m.removeLast();
    // The element which is still spoken keeps its index.
    QCOMPARE(m.enqueueList().count(), 1);
    QCOMPARE(m.value(0), first);
    QVERIFY(m.contains(first));
    QVERIFY(!m.contains(second));
}

void TextAutoGenerateTextToSpeechEnqueueManagerTest::shouldClearList()
{
    TextAutoGenerateTextToSpeechEnqueueManager m;
    m.insert(createInfo("chat1", "message1"));
    m.insert(createInfo("chat1", "message2"));
    m.clear();
    QVERIFY(m.enqueueList().isEmpty());
}

#include "moc_textautogeneratetexttospeechenqueuemanagertest.cpp"
