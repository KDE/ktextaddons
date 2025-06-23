/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeech.h"
using namespace Qt::Literals::StringLiterals;

#include "texttospeechutil.h"

#include <KConfig>
#include <QLocale>
#include <QTextToSpeech>
#include <QVector>

class TextEditTextToSpeech::TextToSpeechPrivate
{
public:
    QString mDefaultEngine;
    QTextToSpeech *mTextToSpeech = nullptr;
};

using namespace TextEditTextToSpeech;
TextToSpeech::TextToSpeech(QObject *parent)
    : QObject(parent)
    , d(new TextEditTextToSpeech::TextToSpeechPrivate)
{
    reloadSettings();
}

TextToSpeech::~TextToSpeech() = default;

void TextToSpeech::reloadSettings()
{
    const TextEditTextToSpeech::TextToSpeechUtil::TextToSpeechSettings settings = TextEditTextToSpeech::TextToSpeechUtil::loadSettings();

    const QString engineName = settings.engineName;
    if (d->mDefaultEngine != engineName) {
        if (d->mTextToSpeech) {
            if (d->mTextToSpeech && (d->mTextToSpeech->engine() != engineName)) {
                disconnect(d->mTextToSpeech, &QTextToSpeech::stateChanged, this, &TextToSpeech::slotStateChanged);
                delete d->mTextToSpeech;
                d->mTextToSpeech = nullptr;
            }
        }
    }
    if (!d->mTextToSpeech) {
        d->mTextToSpeech = new QTextToSpeech(engineName, this);
        connect(d->mTextToSpeech, &QTextToSpeech::stateChanged, this, &TextToSpeech::slotStateChanged);
    }
    d->mDefaultEngine = engineName;
    const int rate = settings.rate;
    const double rateDouble = rate / 100.0;
    d->mTextToSpeech->setRate(rateDouble);
    const int pitch = settings.pitch;
    const double pitchDouble = pitch / 100.0;
    d->mTextToSpeech->setPitch(pitchDouble);
    const int volumeValue = settings.volumeValue;
    const double volumeDouble = volumeValue / 100.0;
    d->mTextToSpeech->setVolume(volumeDouble);
    d->mTextToSpeech->setLocale(QLocale(settings.localeName));
    // It doesn't have api for it d->mTextToSpeech->setVoice(grp.readEntry("voice"));
}

TextToSpeech *TextToSpeech::self()
{
    static TextToSpeech s_self;
    return &s_self;
}

void TextToSpeech::slotStateChanged()
{
    TextToSpeech::State state;
    switch (d->mTextToSpeech->state()) {
    case QTextToSpeech::Ready:
        state = TextToSpeech::Ready;
        break;
    case QTextToSpeech::Speaking:
        state = TextToSpeech::Speaking;
        break;
    case QTextToSpeech::Paused:
        state = TextToSpeech::Paused;
        break;
    case QTextToSpeech::Error:
        state = TextToSpeech::BackendError;
        break;
    case QTextToSpeech::Synthesizing:
        state = TextToSpeech::Synthesizing;
        break;
    }
    Q_EMIT stateChanged(state);
}

bool TextToSpeech::isReady() const
{
    return d->mTextToSpeech->state() != QTextToSpeech::Error;
}

void TextToSpeech::say(const QString &text)
{
    d->mTextToSpeech->say(text);
}

void TextToSpeech::stop()
{
    d->mTextToSpeech->stop();
}

void TextToSpeech::pause()
{
    d->mTextToSpeech->pause();
}

void TextToSpeech::resume()
{
    d->mTextToSpeech->resume();
}

void TextToSpeech::setRate(double rate)
{
    d->mTextToSpeech->setRate(rate);
}

void TextToSpeech::setPitch(double pitch)
{
    d->mTextToSpeech->setPitch(pitch);
}

void TextToSpeech::setVolume(double volume)
{
    d->mTextToSpeech->setVolume(volume);
}

double TextToSpeech::volume() const
{
    return d->mTextToSpeech->volume();
}

QVector<QLocale> TextToSpeech::availableLocales() const
{
    return d->mTextToSpeech->availableLocales();
}

QStringList TextToSpeech::availableVoices() const
{
    QStringList lst;
    const QVector<QVoice> voices = d->mTextToSpeech->availableVoices();
    lst.reserve(voices.count());
    for (const QVoice &voice : voices) {
        lst << voice.name();
    }
    return lst;
}

QStringList TextToSpeech::availableEngines() const
{
    return QTextToSpeech::availableEngines();
}

void TextToSpeech::setLocale(const QLocale &locale) const
{
    d->mTextToSpeech->setLocale(locale);
}

QLocale TextToSpeech::locale() const
{
    return d->mTextToSpeech->locale();
}

#include "moc_texttospeech.cpp"
