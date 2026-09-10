/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokoroengine.h"
#include "texttospeechkokoro.h"
#include "texttospeechkokoroutils.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;
TextToSpeechKokoroEngine::TextToSpeechKokoroEngine([[maybe_unused]] const QVariantMap &parameters, QObject *parent)
    : QTextToSpeechEngine(parent)
    , mTextToSpeechKokoro(new TextToSpeechKokoro(this))
{
    connect(mTextToSpeechKokoro.get(), &TextToSpeechKokoro::stateChanged, this, &TextToSpeechKokoroEngine::stateChanged);
    connect(mTextToSpeechKokoro.get(), &TextToSpeechKokoro::errorOccurred, this, &TextToSpeechKokoroEngine::errorOccurred);
    connect(mTextToSpeechKokoro.get(), &TextToSpeechKokoro::synthesized, this, &TextToSpeechKokoroEngine::synthesized);

    // The engine has to start on a usable voice, QTextToSpeech does not select
    // one before speaking.
    if (!setLocale(QLocale())) {
        // The system locale is not one of the nine languages of the model.
        const QList<TextToSpeechKokoroUtils::KokoroVoice> kokoroVoices = TextToSpeechKokoroUtils::kokoroVoices();
        if (!kokoroVoices.isEmpty()) {
            mLocale = kokoroVoices.constFirst().locale;
            (void)setVoice(createKokoroVoice(kokoroVoices.constFirst()));
        }
    }
}

TextToSpeechKokoroEngine::~TextToSpeechKokoroEngine() = default;

QTextToSpeech::Capabilities TextToSpeechKokoroEngine::capabilities() const
{
    // Kokoro reports the graphemes of each chunk, not of each word, so
    // WordByWordProgress cannot be claimed.
    return QTextToSpeech::Capability::Speak | QTextToSpeech::Capability::PauseResume | QTextToSpeech::Capability::Synthesize;
}

QList<QLocale> TextToSpeechKokoroEngine::availableLocales() const
{
    return TextToSpeechKokoroUtils::availableLocales();
}

QList<QVoice> TextToSpeechKokoroEngine::availableVoices() const
{
    // QTextToSpeechEngine::createVoice() is protected, so the conversion from
    // the voice table to QVoice can only happen here, in the engine itself.
    // QTextToSpeech::availableVoices() only shows the current locale, the other
    // ones are reached by switching locale, as allVoices() does.
    const QList<TextToSpeechKokoroUtils::KokoroVoice> kokoroVoices = TextToSpeechKokoroUtils::kokoroVoices();
    QList<QVoice> voices;
    voices.reserve(kokoroVoices.count());
    for (const TextToSpeechKokoroUtils::KokoroVoice &kokoroVoice : kokoroVoices) {
        if (kokoroVoice.locale != mLocale) {
            continue;
        }
        voices.append(createKokoroVoice(kokoroVoice));
    }
    return voices;
}

QVoice TextToSpeechKokoroEngine::createKokoroVoice(const TextToSpeechKokoroUtils::KokoroVoice &kokoroVoice)
{
    // The identifier is stored as the voice data: it is what setVoice() has to
    // hand over to the backend. Kokoro says nothing about age.
    return createVoice(kokoroVoice.name, kokoroVoice.locale, kokoroVoice.gender, QVoice::Other, kokoroVoice.identifier);
}

QString TextToSpeechKokoroEngine::kokoroIdentifier(const QVoice &voice)
{
    return voiceData(voice).toString();
}

void TextToSpeechKokoroEngine::say(const QString &text)
{
    mTextToSpeechKokoro->say(text);
}

void TextToSpeechKokoroEngine::synthesize(const QString &text)
{
    mTextToSpeechKokoro->synthesize(text);
}

void TextToSpeechKokoroEngine::stop([[maybe_unused]] QTextToSpeech::BoundaryHint boundaryHint)
{
    // Kokoro can only be interrupted between two chunks, so a boundary finer
    // than the utterance cannot be honoured.
    mTextToSpeechKokoro->stop();
}

void TextToSpeechKokoroEngine::pause([[maybe_unused]] QTextToSpeech::BoundaryHint boundaryHint)
{
    // Suspending the audio sink stops the playback right away, whatever the
    // boundary asked for.
    mTextToSpeechKokoro->pause();
}

void TextToSpeechKokoroEngine::resume()
{
    mTextToSpeechKokoro->resume();
}

double TextToSpeechKokoroEngine::rate() const
{
    return mTextToSpeechKokoro->rate();
}

bool TextToSpeechKokoroEngine::setRate(double rate)
{
    return mTextToSpeechKokoro->setRate(rate);
}

double TextToSpeechKokoroEngine::pitch() const
{
    // Kokoro has no pitch control, the voice defines it.
    return 0.0;
}

bool TextToSpeechKokoroEngine::setPitch([[maybe_unused]] double pitch)
{
    return false;
}

QLocale TextToSpeechKokoroEngine::locale() const
{
    return mLocale;
}

bool TextToSpeechKokoroEngine::setLocale(const QLocale &locale)
{
    const QList<TextToSpeechKokoroUtils::KokoroVoice> kokoroVoices = TextToSpeechKokoroUtils::kokoroVoices();
    // The locales of the model are language and country, "fr_FR" and not "fr",
    // so a request for "fr" has to match on the language alone.
    for (const TextToSpeechKokoroUtils::KokoroVoice &kokoroVoice : kokoroVoices) {
        if (kokoroVoice.locale != locale && kokoroVoice.locale.language() != locale.language()) {
            continue;
        }
        mLocale = kokoroVoice.locale;
        // Changing the locale invalidates the voice: take the first one of the
        // new locale, as the other engines do.
        return setVoice(createKokoroVoice(kokoroVoice));
    }
    return false;
}

double TextToSpeechKokoroEngine::volume() const
{
    return mTextToSpeechKokoro->volume();
}

bool TextToSpeechKokoroEngine::setVolume(double volume)
{
    return mTextToSpeechKokoro->setVolume(volume);
}

QVoice TextToSpeechKokoroEngine::voice() const
{
    return mVoice;
}

bool TextToSpeechKokoroEngine::setVoice(const QVoice &voice)
{
    const QString identifier = kokoroIdentifier(voice);
    if (!mTextToSpeechKokoro->setVoiceIdentifier(identifier)) {
        return false;
    }
    mVoice = voice;
    mLocale = voice.locale();
    return true;
}

QTextToSpeech::State TextToSpeechKokoroEngine::state() const
{
    return mTextToSpeechKokoro->state();
}

QTextToSpeech::ErrorReason TextToSpeechKokoroEngine::errorReason() const
{
    return mTextToSpeechKokoro->errorReason();
}

QString TextToSpeechKokoroEngine::errorString() const
{
    return mTextToSpeechKokoro->errorString();
}

#include "moc_texttospeechkokoroengine.cpp"
