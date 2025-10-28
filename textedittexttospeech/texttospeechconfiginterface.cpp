/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechconfiginterface.h"
#include "textedittexttospeech_debug.h"
#include <KLocalizedString>
#include <QTextToSpeech>
using namespace TextEditTextToSpeech;

TextToSpeechConfigInterface::TextToSpeechConfigInterface(QObject *parent)
    : QObject(parent)
{
}

TextToSpeechConfigInterface::~TextToSpeechConfigInterface() = default;

QVector<QVoice> TextToSpeechConfigInterface::availableVoices() const
{
    QVector<QVoice> voices;
    if (mTextToSpeech) {
        voices = mTextToSpeech->availableVoices();
    } else {
        qCWarning(TEXTEDITTEXTTOSPEECH_LOG) << "Text To Speech is not created. ";
    }
    return voices;
}

QStringList TextToSpeechConfigInterface::availableEngines() const
{
    if (mTextToSpeech) {
        return mTextToSpeech->availableEngines();
    }
    qCWarning(TEXTEDITTEXTTOSPEECH_LOG) << "Text To Speech is not created. ";
    return {};
}

QVector<QLocale> TextToSpeechConfigInterface::availableLocales() const
{
    if (mTextToSpeech) {
        return mTextToSpeech->availableLocales();
    }
    qCWarning(TEXTEDITTEXTTOSPEECH_LOG) << "Text To Speech is not created. ";
    return {};
}

QLocale TextToSpeechConfigInterface::locale() const
{
    if (mTextToSpeech) {
        return mTextToSpeech->locale();
    }
    qCWarning(TEXTEDITTEXTTOSPEECH_LOG) << "Text To Speech is not created. ";
    return {};
}

void TextToSpeechConfigInterface::setEngine(const QString &engineName)
{
    if (!mTextToSpeech || (mTextToSpeech->engine() != engineName)) {
        delete mTextToSpeech;
        mTextToSpeech = new QTextToSpeech(engineName, this);
        connect(mTextToSpeech, &QTextToSpeech::stateChanged, this, &TextToSpeechConfigInterface::stateChanged);
    }
}

void TextToSpeechConfigInterface::testEngine(const EngineSettings &engineSettings)
{
    if (!mTextToSpeech) {
        qCWarning(TEXTEDITTEXTTOSPEECH_LOG) << "Text To Speech is not created. ";
        return;
    }
    const int rate = engineSettings.rate;
    const double rateDouble = rate / 100.0;
    mTextToSpeech->setRate(rateDouble);
    const int pitch = engineSettings.pitch;
    const double pitchDouble = pitch / 100.0;
    mTextToSpeech->setPitch(pitchDouble);
    const int volume = engineSettings.volume;
    const double volumeDouble = volume / 100.0;
    mTextToSpeech->setVolume(volumeDouble);
    mTextToSpeech->setLocale(QLocale(engineSettings.localeName));
    mTextToSpeech->setVoice(engineSettings.voice);

    // TODO change text ?
    mTextToSpeech->say(i18n("Morning, this is the test for testing settings."));
}

void TextToSpeechConfigInterface::stop()
{
    if (mTextToSpeech->state() == QTextToSpeech::Speaking) {
        mTextToSpeech->stop();
    }
}

QDebug operator<<(QDebug d, const TextEditTextToSpeech::TextToSpeechConfigInterface::EngineSettings &t)
{
    d << " Rate " << t.rate;
    d << " pitch " << t.pitch;
    d << " volume " << t.volume;
    d << " voice " << t.voice;
    d << " localeName " << t.localeName;
    return d;
}

#include "moc_texttospeechconfiginterface.cpp"
