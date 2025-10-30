/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttospeechinfotest.h"
#include "core/texttospeech/textautogeneratetexttospeechinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateTextToSpeechInfoTest)
TextAutoGenerateTextToSpeechInfoTest::TextAutoGenerateTextToSpeechInfoTest(QObject *parent)
    : QObject(parent)
{
}

void TextAutoGenerateTextToSpeechInfoTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateTextToSpeechInfo info;
    QVERIFY(info.chatId().isEmpty());
    QVERIFY(info.messageId().isEmpty());
    QVERIFY(!info.isValid());
}

#include "moc_textautogeneratetexttospeechinfotest.cpp"
