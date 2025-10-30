/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttospeechinfoenqueuetest.h"
#include "core/texttospeech/textautogeneratetexttospeechenqueueinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextToSpeechInfoEnqueueTest)
TextAutoGenerateTextToSpeechInfoEnqueueTest::TextAutoGenerateTextToSpeechInfoEnqueueTest(QObject *parent)
    : QObject(parent)
{
}

void TextAutoGenerateTextToSpeechInfoEnqueueTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextToSpeechEnqueueInfo info;
    QVERIFY(info.chatId().isEmpty());
    QVERIFY(info.messageId().isEmpty());
    QVERIFY(!info.isValid());
}

#include "moc_textautogeneratetexttospeechinfoenqueuetest.cpp"
