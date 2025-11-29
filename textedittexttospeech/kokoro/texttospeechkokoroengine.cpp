/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokoroengine.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;
TextToSpeechKokoroEngine::TextToSpeechKokoroEngine(const QVariantMap &parameters, QObject *parent)
    : QTextToSpeechEngine(parent)
{
}

TextToSpeechKokoroEngine::~TextToSpeechKokoroEngine() = default;

QList<QLocale> TextToSpeechKokoroEngine::availableLocales() const
{
    return {};
}

QList<QVoice> TextToSpeechKokoroEngine::availableVoices() const
{
    return {};
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

bool TextToSpeechKokoroEngine::setPitch(double pitch)
{
    return {};
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
