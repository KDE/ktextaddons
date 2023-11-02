/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libvoskspeechtotext_export.h"
#include <QIODevice>

// #define VOSK_API
#ifdef VOSK_API
class VoskModel;
class VoskRecognizer;
#endif

class LIBVOSKSPEECHTOTEXT_EXPORT VoskSpeechToTextDevice : public QIODevice
{
    Q_OBJECT
public:
    struct LIBVOSKSPEECHTOTEXT_EXPORT VoskSpeechToTextDeviceInfo {
        // TODO add language and co
        int sampleRate = 0;
    };

    explicit VoskSpeechToTextDevice(QObject *parent = nullptr);
    ~VoskSpeechToTextDevice() override;

    void clear();
    [[nodiscard]] bool initialize(VoskSpeechToTextDeviceInfo &&info);

Q_SIGNALS:
    void result(const QString &str);

protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

private:
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void parseText(const char *json);
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void parsePartial(const char *json);
#ifdef VOSK_API
    VoskModel *mModel = nullptr;
    VoskRecognizer *mRecognizer = nullptr;
#endif
};
Q_DECLARE_TYPEINFO(VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo, Q_MOVABLE_TYPE);
LIBVOSKSPEECHTOTEXT_EXPORT QDebug operator<<(QDebug d, const VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo &t);
