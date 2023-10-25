/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
  based on VoiceAssistant plugin code
*/

#include "voskspeechtotextdevice.h"
#include "libvoskspeechtotext_debug.h"
#ifdef VOSK_API
#include "vosk_api.h"
#endif
#include <QJsonDocument>

VoskSpeechToTextDevice::VoskSpeechToTextDevice(QObject *parent)
    : QIODevice{parent}
{
    if (!open(QIODevice::ReadWrite)) {
        qCWarning(LIBVOSKSPEECHTOTEXT_LOG) << "Impossible to open VoskSpeechToTextDevice";
#ifdef VOSK_API
        vosk_set_log_level(-1);
#endif
    }
}

VoskSpeechToTextDevice::~VoskSpeechToTextDevice()
{
#ifdef VOSK_API
    vosk_recognizer_free(recognizer);
    vosk_model_free(model);
#endif
}

qint64 VoskSpeechToTextDevice::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data);
    return maxlen;
}

qint64 VoskSpeechToTextDevice::writeData(const char *data, qint64 len)
{
#ifdef VOSK_API
    if (vosk_recognizer_accept_waveform(recognizer, data, (int)size)) {
        parseText(vosk_recognizer_result(recognizer));
    } else {
        parsePartial(vosk_recognizer_partial_result(recognizer));
    }
#endif
    return len;
}

void VoskSpeechToTextDevice::parseText(const char *json)
{
#ifdef VOSK_API
    auto obj = QJsonDocument::fromJson(json);
    QString text = obj[QStringLiteral("text")].toString();

    if (text.isEmpty())
        return;
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

    Q_EMIT textUpdated(text);
    qDebug() << "[debug] Text:" << text;
    Q_EMIT doneListening();
#endif
}

void VoskSpeechToTextDevice::parsePartial(const char *json)
{
#ifdef VOSK_API
    auto obj = QJsonDocument::fromJson(json);
    QString text = obj[QStringLiteral("partial")].toString();
    if (text.isEmpty())
        return;
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

    Q_EMIT textUpdated(text);
#endif
}

#include "moc_voskspeechtotextdevice.cpp"
