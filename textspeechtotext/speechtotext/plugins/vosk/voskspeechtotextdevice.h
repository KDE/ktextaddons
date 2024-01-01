/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "config-vosk-plugin.h"
#include "libvoskspeechtotext_export.h"
#include <QIODevice>

#if HAVE_VOSK_API_SUPPORT
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

    [[nodiscard]] bool available() const;
Q_SIGNALS:
    void result(const QString &str);

protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

private:
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void parseText(const char *json);
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void parsePartial(const char *json);
#if HAVE_VOSK_API_SUPPORT
    VoskModel *mModel = nullptr;
    VoskRecognizer *mRecognizer = nullptr;
#endif
};
Q_DECLARE_TYPEINFO(VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo, Q_MOVABLE_TYPE);
LIBVOSKSPEECHTOTEXT_EXPORT QDebug operator<<(QDebug d, const VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo &t);
