/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeech.h"
#include "textedittexttospeech_debug.h"

#include "texttospeechutil.h"

#include <QLocale>
#include <QTextToSpeech>
#include <QVector>

using namespace Qt::Literals::StringLiterals;
class TextEditTextToSpeech::TextToSpeechPrivate
{
public:
    QString mDefaultEngine;
    QTextToSpeech *mTextToSpeech = nullptr;
    qsizetype mCurrentTextToSpeechId = -1;
    bool initialized = false;
};

using namespace TextEditTextToSpeech;
TextToSpeech::TextToSpeech(QObject *parent)
    : QObject(parent)
    , d(new TextEditTextToSpeech::TextToSpeechPrivate)
{
}

TextToSpeech::~TextToSpeech() = default;

void TextToSpeech::reloadSettings()
{
    d->initialized = true;
    const TextEditTextToSpeech::TextToSpeechUtil::TextToSpeechSettings settings = TextEditTextToSpeech::TextToSpeechUtil::loadSettings();
    qCDebug(TEXTEDITTEXTTOSPEECH_LOG) << settings;
    const QString engineName = settings.engineName;
    if (d->mDefaultEngine != engineName) {
        if (d->mTextToSpeech) {
            if (d->mTextToSpeech->engine() != engineName) {
                disconnect(d->mTextToSpeech, &QTextToSpeech::stateChanged, this, &TextToSpeech::slotStateChanged);
                disconnect(d->mTextToSpeech, &QTextToSpeech::aboutToSynthesize, this, &TextToSpeech::slotAboutToSynthesize);
                delete d->mTextToSpeech;
                d->mTextToSpeech = nullptr;
            }
        }
    }
    if (!d->mTextToSpeech) {
        d->mTextToSpeech = new QTextToSpeech(engineName, this);
        connect(d->mTextToSpeech, &QTextToSpeech::stateChanged, this, &TextToSpeech::slotStateChanged);
        connect(d->mTextToSpeech, &QTextToSpeech::aboutToSynthesize, this, &TextToSpeech::slotAboutToSynthesize);
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
    d->mTextToSpeech->setVoice(settings.voice);
}

TextToSpeech *TextToSpeech::self()
{
    static TextToSpeech s_self;
    return &s_self;
}

void TextToSpeech::initialize()
{
    if (!d->initialized) {
        reloadSettings();
    }
}

void TextToSpeech::slotAboutToSynthesize([[maybe_unused]] qsizetype id)
{
    const auto currentSpeechId = d->mCurrentTextToSpeechId;
    Q_EMIT aboutToSynthesize(currentSpeechId, ++d->mCurrentTextToSpeechId);
}

void TextToSpeech::slotStateChanged()
{
    TextToSpeech::State state = TextToSpeech::State::Unknown;
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
    if (state == TextToSpeech::Ready) {
        // Workaround for bug in qtextspeech
        d->mTextToSpeech->stop();
        Q_EMIT aboutToSynthesize(d->mCurrentTextToSpeechId, -1);
        // Reinitialize
        d->mCurrentTextToSpeechId = -1;
    }
}

bool TextToSpeech::isReady() const
{
    return d->mTextToSpeech->state() != QTextToSpeech::Error;
}

void TextToSpeech::say(const QString &text)
{
    initialize();
    d->mTextToSpeech->say(text);
}

qsizetype TextToSpeech::enqueue(const QString &text)
{
    initialize();
    return d->mTextToSpeech->enqueue(text);
}

void TextToSpeech::stop()
{
    initialize();
    d->mTextToSpeech->stop();
}

void TextToSpeech::pause()
{
    initialize();
    d->mTextToSpeech->pause();
}

void TextToSpeech::resume()
{
    initialize();
    d->mTextToSpeech->resume();
}

void TextToSpeech::setRate(double rate)
{
    initialize();
    d->mTextToSpeech->setRate(rate);
}

void TextToSpeech::setPitch(double pitch)
{
    initialize();
    d->mTextToSpeech->setPitch(pitch);
}

void TextToSpeech::setVolume(double volume)
{
    initialize();
    d->mTextToSpeech->setVolume(volume);
}

double TextToSpeech::volume() const
{
    return d->mTextToSpeech ? d->mTextToSpeech->volume() : -1.0;
}

QVector<QLocale> TextToSpeech::availableLocales() const
{
    return d->mTextToSpeech ? d->mTextToSpeech->availableLocales() : QVector<QLocale>();
}

QStringList TextToSpeech::availableVoices() const
{
    QStringList lst;
    const QVector<QVoice> voices = d->mTextToSpeech ? d->mTextToSpeech->availableVoices() : QVector<QVoice>();
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

void TextToSpeech::setLocale(const QLocale &locale)
{
    initialize();
    d->mTextToSpeech->setLocale(locale);
}

QLocale TextToSpeech::locale() const
{
    return d->mTextToSpeech ? d->mTextToSpeech->locale() : QLocale();
}

#include "moc_texttospeech.cpp"
