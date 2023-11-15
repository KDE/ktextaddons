/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  based on VoiceAssistant plugin code
*/

#include "voskspeechtotextdevice.h"
#include "libvoskspeechtotext_debug.h"
#if HAVE_VOSK_API_SUPPORT
#include "HAVE_VOSK_API_SUPPORT.h"
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

bool VoskSpeechToTextDevice::initialize(VoskSpeechToTextDeviceInfo &&info)
{
#if HAVE_VOSK_API_SUPPORT
    mModel = vosk_model_new(QString(modelDir + formattedLang).toUtf8());
    if (mModel) {
        mRecognizer = vosk_recognizer_new(mModel, info.sampleRate);
    }

    if (!mModel || !mRecognizer) {
        return false
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
#endif
    return len;
}

void VoskSpeechToTextDevice::parseText(const char *json)
{
    const QJsonDocument obj = QJsonDocument::fromJson(json);
    QString text = obj[QStringLiteral("text")].toString();

    if (text.isEmpty())
        return;
#if HAVE_VOSK_API_SUPPORT
    else if (m_isAsking) {
        Q_EMIT answerReady(text);
        return;
    }

    text.append(u' ');

    if (!text.contains(m_wakeWord)) {
        if (!is_listining_because_of_wakeword)
            return;

        Q_EMIT falsePositiveWakeWord();
        is_listining_because_of_wakeword = false;
        return;
    }

    text = text.mid(text.indexOf(m_wakeWord) + m_wakeWord.size());
    text = text.trimmed();

    Q_EMIT result(text);
    qDebug() << "[debug] Text:" << text;
    Q_EMIT doneListening();
#endif
}

void VoskSpeechToTextDevice::parsePartial(const char *json)
{
    const QJsonDocument obj = QJsonDocument::fromJson(json);
    QString text = obj[QStringLiteral("partial")].toString();
    if (text.isEmpty())
        return;
#if HAVE_VOSK_API_SUPPORT
    text.append(u' ');

    if (text.contains(m_wakeWord)) {
        Q_EMIT wakeWordDetected();
        text = text.mid(text.indexOf(m_wakeWord) + m_wakeWord.size());
        is_listining_because_of_wakeword = true;
    } else if (is_listining_because_of_wakeword) {
        Q_EMIT falsePositiveWakeWord();
        is_listining_because_of_wakeword = false;
        return;
    } else if (!m_isAsking)
        return;

    Q_EMIT result(text);
#endif
}

QDebug operator<<(QDebug d, const VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo &t)
{
    d << "sampleRate " << t.sampleRate;
    return d;
}

#include "moc_voskspeechtotextdevice.cpp"
