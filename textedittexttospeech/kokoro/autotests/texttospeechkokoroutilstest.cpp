/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokoroutilstest.h"
#include "texttospeechkokoroutils.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextToSpeechKokoroUtilsTest)
TextToSpeechKokoroUtilsTest::TextToSpeechKokoroUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void TextToSpeechKokoroUtilsTest::shouldHavePythonScript()
{
    QCOMPARE(TextEditTextToSpeech::TextToSpeechKokoroUtils::pythonScript(), u"kokoro_helper.py"_s);
}
#include "moc_texttospeechkokoroutilstest.cpp"
