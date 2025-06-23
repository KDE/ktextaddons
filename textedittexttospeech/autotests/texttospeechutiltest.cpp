/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechutiltest.h"
using namespace Qt::Literals::StringLiterals;

#include "texttospeechutil.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextToSpeechUtilTest)
TextToSpeechUtilTest::TextToSpeechUtilTest(QObject *parent)
    : QObject{parent}
{
}

void TextToSpeechUtilTest::shouldHaveDefaultValues()
{
    QCOMPARE(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigFileName(), u"texttospeechrc"_s);
    QCOMPARE(TextEditTextToSpeech::TextToSpeechUtil::textToSpeechConfigGroupName(), u"Settings"_s);
}

#include "moc_texttospeechutiltest.cpp"
