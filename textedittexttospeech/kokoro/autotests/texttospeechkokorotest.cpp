/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokorotest.h"
#include "texttospeechkokoro.h"
#include <QSignalSpy>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(TextToSpeechKokoroTest)
TextToSpeechKokoroTest::TextToSpeechKokoroTest(QObject *parent)
    : QObject{parent}
{
}

void TextToSpeechKokoroTest::shouldHaveDefaultValues()
{
    TextEditTextToSpeech::TextToSpeechKokoro w;
    QCOMPARE(w.state(), QTextToSpeech::Ready);
    QCOMPARE(w.errorReason(), QTextToSpeech::ErrorReason::NoError);
    QVERIFY(w.errorString().isEmpty());
    QCOMPARE(w.rate(), 0.0);
    QCOMPARE(w.volume(), 1.0);
    QCOMPARE(w.voiceIdentifier(), u"af_heart"_s);
}

void TextToSpeechKokoroTest::shouldAssignRate_data()
{
    QTest::addColumn<double>("rate");
    QTest::addColumn<bool>("accepted");
    QTest::newRow("normal") << 0.0 << true;
    QTest::newRow("slowest") << -1.0 << true;
    QTest::newRow("fastest") << 1.0 << true;
    QTest::newRow("too-slow") << -1.5 << false;
    QTest::newRow("too-fast") << 1.5 << false;
}

void TextToSpeechKokoroTest::shouldAssignRate()
{
    QFETCH(double, rate);
    QFETCH(bool, accepted);
    TextEditTextToSpeech::TextToSpeechKokoro w;
    QCOMPARE(w.setRate(rate), accepted);
    QCOMPARE(w.rate(), accepted ? rate : 0.0);
}

void TextToSpeechKokoroTest::shouldAssignVolume_data()
{
    QTest::addColumn<double>("volume");
    QTest::addColumn<bool>("accepted");
    QTest::newRow("silent") << 0.0 << true;
    QTest::newRow("half") << 0.5 << true;
    QTest::newRow("loudest") << 1.0 << true;
    QTest::newRow("negative") << -0.5 << false;
    QTest::newRow("too-loud") << 1.5 << false;
}

void TextToSpeechKokoroTest::shouldAssignVolume()
{
    QFETCH(double, volume);
    QFETCH(bool, accepted);
    TextEditTextToSpeech::TextToSpeechKokoro w;
    QCOMPARE(w.setVolume(volume), accepted);
    QCOMPARE(w.volume(), accepted ? volume : 1.0);
}

void TextToSpeechKokoroTest::shouldAssignVoiceIdentifier_data()
{
    QTest::addColumn<QString>("identifier");
    QTest::addColumn<bool>("accepted");
    QTest::newRow("french") << u"ff_siwis"_s << true;
    QTest::newRow("japanese") << u"jf_alpha"_s << true;
    QTest::newRow("empty") << QString() << false;
    // The first character has to be one of the language codes of the model.
    QTest::newRow("unknown-language") << u"xf_foo"_s << false;
}

void TextToSpeechKokoroTest::shouldAssignVoiceIdentifier()
{
    QFETCH(QString, identifier);
    QFETCH(bool, accepted);
    TextEditTextToSpeech::TextToSpeechKokoro w;
    QCOMPARE(w.setVoiceIdentifier(identifier), accepted);
    QCOMPARE(w.voiceIdentifier(), accepted ? identifier : u"af_heart"_s);
}

void TextToSpeechKokoroTest::shouldNotSpeakEmptyText()
{
    // Nothing to say must not start the backend, which would be reported as an
    // error when kokoro is not installed.
    TextEditTextToSpeech::TextToSpeechKokoro w;
    QSignalSpy stateSpy(&w, &TextEditTextToSpeech::TextToSpeechKokoro::stateChanged);
    QSignalSpy errorSpy(&w, &TextEditTextToSpeech::TextToSpeechKokoro::errorOccurred);
    w.say(QString());
    w.say(u"   \n  "_s);
    QCOMPARE(w.state(), QTextToSpeech::Ready);
    QVERIFY(stateSpy.isEmpty());
    QVERIFY(errorSpy.isEmpty());
}

#include "moc_texttospeechkokorotest.cpp"
