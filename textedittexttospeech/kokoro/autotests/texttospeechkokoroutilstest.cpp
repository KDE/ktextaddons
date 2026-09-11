/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokoroutilstest.h"
#include "texttospeechkokoroutils.h"
#include <QDir>
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

void TextToSpeechKokoroUtilsTest::shouldHaveVenvPython()
{
    // Disable on CI QCOMPARE(TextEditTextToSpeech::TextToSpeechKokoroUtils::venvPython(), QDir::homePath() + u"/.venv/kokoro/bin/python"_s);
}

void TextToSpeechKokoroUtilsTest::shouldHavePythonVersion()
{
    QCOMPARE(TextEditTextToSpeech::TextToSpeechKokoroUtils::pythonVersion(), u"python3.11"_s);
}

#include "moc_texttospeechkokoroutilstest.cpp"
