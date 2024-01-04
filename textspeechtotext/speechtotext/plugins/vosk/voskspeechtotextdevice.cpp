/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  based on VoiceAssistant plugin code
*/

#include "voskspeechtotextdevice.h"
#include "libvoskspeechtotext_debug.h"
#if HAVE_VOSK_API_SUPPORT
#include "vosk_api.h"
#endif
#include <QJsonDocument>

VoskSpeechToTextDevice::VoskSpeechToTextDevice(QObject *parent)
    : QIODevice{parent}
{
    if (!open(QIODevice::ReadWrite)) {
        qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to open VoskSpeechToTextDevice";
#if HAVE_VOSK_API_SUPPORT
        vosk_set_log_level(-1);
#endif
    }
}

VoskSpeechToTextDevice::~VoskSpeechToTextDevice()
{
#if HAVE_VOSK_API_SUPPORT
    vosk_recognizer_free(mRecognizer);
    vosk_model_free(mModel);
#endif
}

bool VoskSpeechToTextDevice::available() const
{
#if HAVE_VOSK_API_SUPPORT
    return true;
#else
    return false;
#endif
}

bool VoskSpeechToTextDevice::isAsking() const
{
    return mIsAsking;
}

void VoskSpeechToTextDevice::setAsking(bool asking)
{
    if (mIsAsking != asking) {
        mIsAsking = asking;
        Q_EMIT askingChanged();
    }
}

bool VoskSpeechToTextDevice::initialize(VoskSpeechToTextDeviceInfo &&info)
{
#if HAVE_VOSK_API_SUPPORT
    mModel = vosk_model_new(QString(info.modelDir + info.formattedLang).toUtf8().constData());
    if (mModel) {
        mRecognizer = vosk_recognizer_new(mModel, info.sampleRate);
    }

    if (!mModel || !mRecognizer) {
        return false;
    }
#endif
    return true;
}

void VoskSpeechToTextDevice::clear()
{
#if HAVE_VOSK_API_SUPPORT
    if (mRecognizer) {
        vosk_recognizer_reset(mRecognizer);
    }
#endif
}

qint64 VoskSpeechToTextDevice::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data);
    return maxlen;
}

qint64 VoskSpeechToTextDevice::writeData(const char *data, qint64 len)
{
#if HAVE_VOSK_API_SUPPORT
    if (vosk_recognizer_accept_waveform(mRecognizer, data, (int)len)) {
        parseText(vosk_recognizer_result(mRecognizer));
    } else {
        parsePartial(vosk_recognizer_partial_result(mRecognizer));
    }
#else
    Q_UNUSED(data);
#endif
    return len;
}

void VoskSpeechToTextDevice::parseText(const char *json)
{
    const QJsonDocument obj = QJsonDocument::fromJson(json);
    QString text = obj[QStringLiteral("text")].toString();

    if (text.isEmpty())
        return;
    else if (mIsAsking) {
        Q_EMIT result(text);
        return;
    }

    text.append(u' ');

    if (!text.contains(mWakeWord)) {
        if (!mIsListiningBecauseOfWakeWord)
            return;

        Q_EMIT falsePositiveWakeWord();
        mIsListiningBecauseOfWakeWord = false;
        return;
    }

    text = text.mid(text.indexOf(mWakeWord) + mWakeWord.size());
    text = text.trimmed();

    Q_EMIT result(text);
    qDebug() << "[debug] Text:" << text;
    Q_EMIT doneListening();
}

void VoskSpeechToTextDevice::parsePartial(const char *json)
{
    const QJsonDocument obj = QJsonDocument::fromJson(json);
    QString text = obj[QStringLiteral("partial")].toString();
    if (text.isEmpty())
        return;
    text.append(u' ');

    if (text.contains(mWakeWord)) {
        Q_EMIT wakeWordDetected();
        text = text.mid(text.indexOf(mWakeWord) + mWakeWord.size());
        mIsListiningBecauseOfWakeWord = true;
    } else if (mIsListiningBecauseOfWakeWord) {
        Q_EMIT falsePositiveWakeWord();
        mIsListiningBecauseOfWakeWord = false;
        return;
    } else if (!mIsAsking)
        return;

    Q_EMIT result(text);
}

QDebug operator<<(QDebug d, const VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo &t)
{
    d << "sampleRate " << t.sampleRate;
    return d;
}

#include "moc_voskspeechtotextdevice.cpp"
