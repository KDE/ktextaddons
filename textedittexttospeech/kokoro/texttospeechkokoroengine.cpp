/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokoroengine.h"
#include "texttospeechkokoroutils.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;
TextToSpeechKokoroEngine::TextToSpeechKokoroEngine(const QVariantMap &parameters, QObject *parent)
    : QTextToSpeechEngine(parent)
{
}

TextToSpeechKokoroEngine::~TextToSpeechKokoroEngine() = default;

QList<QLocale> TextToSpeechKokoroEngine::availableLocales() const
{
    return TextToSpeechKokoroUtils::availableLocales();
}

QList<QVoice> TextToSpeechKokoroEngine::availableVoices() const
{
    // QTextToSpeechEngine::createVoice() is protected, so the conversion from
    // the voice table to QVoice can only happen here, in the engine itself.
    const QList<TextToSpeechKokoroUtils::KokoroVoice> kokoroVoices = TextToSpeechKokoroUtils::kokoroVoices();
    QList<QVoice> voices;
    voices.reserve(kokoroVoices.count());
    for (const TextToSpeechKokoroUtils::KokoroVoice &kokoroVoice : kokoroVoices) {
        // The identifier is stored as the voice data: it is what setVoice() has
        // to hand over to the backend. Kokoro says nothing about age.
        voices.append(createVoice(kokoroVoice.name, kokoroVoice.locale, kokoroVoice.gender, QVoice::Other, kokoroVoice.identifier));
    }
    return voices;
}

QString TextToSpeechKokoroEngine::kokoroIdentifier(const QVoice &voice)
{
    return voiceData(voice).toString();
}

void TextToSpeechKokoroEngine::say(const QString &text)
{
}

void TextToSpeechKokoroEngine::synthesize(const QString &text)
{
}

void TextToSpeechKokoroEngine::stop(QTextToSpeech::BoundaryHint boundaryHint)
{
}

void TextToSpeechKokoroEngine::pause(QTextToSpeech::BoundaryHint boundaryHint)
{
}

void TextToSpeechKokoroEngine::resume()
{
}

double TextToSpeechKokoroEngine::rate() const
{
    return {};
}

bool TextToSpeechKokoroEngine::setRate(double rate)
{
    return {};
}

double TextToSpeechKokoroEngine::pitch() const
{
    return {};
}

bool TextToSpeechKokoroEngine::setPitch([[maybe_unused]] double pitch)
{
    return false;
}

QLocale TextToSpeechKokoroEngine::locale() const
{
    return {};
}

bool TextToSpeechKokoroEngine::setLocale(const QLocale &locale)
{
    return {};
}

double TextToSpeechKokoroEngine::volume() const
{
    return {};
}

bool TextToSpeechKokoroEngine::setVolume(double volume)
{
    return {};
}

QVoice TextToSpeechKokoroEngine::voice() const
{
    return {};
}

bool TextToSpeechKokoroEngine::setVoice(const QVoice &voice)
{
    return {};
}

QTextToSpeech::State TextToSpeechKokoroEngine::state() const
{
    return {};
}

QTextToSpeech::ErrorReason TextToSpeechKokoroEngine::errorReason() const
{
    return {};
}

QString TextToSpeechKokoroEngine::errorString() const
{
    return {};
}

#include "moc_texttospeechkokoroengine.cpp"
