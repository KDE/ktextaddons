/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechconfiginterface.h"
#include "textedittexttospeech_debug.h"
#include <KLocalizedString>
#include <QTextToSpeech>
using namespace TextEditTextToSpeech;

TextToSpeechConfigInterface::TextToSpeechConfigInterface(QObject *parent)
    : AbstractTextToSpeechConfigInterface(parent)
{
}

TextToSpeechConfigInterface::~TextToSpeechConfigInterface() = default;

QStringList TextToSpeechConfigInterface::availableVoices() const
{
    QStringList lst;
    if (mTextToSpeech) {
        const QVector<QVoice> voices = mTextToSpeech->availableVoices();
        lst.reserve(voices.count());
        for (const QVoice &voice : voices) {
            lst << voice.name();
        }
    } else {
        qCWarning(TEXTEDITTEXTTOSPEECH_LOG) << "Text To Speech is not created. ";
    }
    return lst;
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
#if QT_VERSION >= QT_VERSION_CHECK(6, 4, 0)
    if (!mTextToSpeech || (mTextToSpeech && (mTextToSpeech->engine() != engineName)))
#endif
    {
        delete mTextToSpeech;
        mTextToSpeech = new QTextToSpeech(engineName, this);
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
    // TODO mTextToSpeech->setVoice()

    // TODO change text ?
    mTextToSpeech->say(i18n("Morning, this is the test for testing settings."));
}

#include "moc_texttospeechconfiginterface.cpp"
