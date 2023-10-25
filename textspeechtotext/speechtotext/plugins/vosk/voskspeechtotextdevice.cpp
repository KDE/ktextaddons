/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextdevice.h"
#include "libvoskspeechtotext_debug.h"
#ifdef VOSK_API
#include "vosk_api.h"
#endif

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
    // TODO
    return -1;
}

#include "moc_voskspeechtotextdevice.cpp"
