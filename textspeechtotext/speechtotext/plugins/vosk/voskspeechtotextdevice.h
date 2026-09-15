/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "config-vosk-plugin.h"
#include "libvoskspeechtotext_export.h"
#include <QIODevice>
class QDebug;
#if HAVE_VOSK_API_SUPPORT
class VoskModel;
class VoskRecognizer;
#endif

class LIBVOSKSPEECHTOTEXT_EXPORT VoskSpeechToTextDevice : public QIODevice
{
    Q_OBJECT
public:
    struct LIBVOSKSPEECHTOTEXT_EXPORT VoskSpeechToTextDeviceInfo {
        /*! Absolute path of the model directory, as extracted on disk. */
        QString modelPath;
        int sampleRate = 0;
    };

    explicit VoskSpeechToTextDevice(QObject *parent = nullptr);
    ~VoskSpeechToTextDevice() override;

    void clear();

    /*!
     * Flushes the recognizer: emits the result for the audio accepted so far.
     * Must be called once the audio capture is stopped, otherwise the last
     * utterance stays buffered in vosk and is never reported.
     */
    void finish();

    [[nodiscard]] bool initialize(VoskSpeechToTextDeviceInfo &&info);

    [[nodiscard]] bool available() const;

    [[nodiscard]] bool isAsking() const;

    void setAsking(bool asking);

Q_SIGNALS:
    void result(const QString &str);
    void askingChanged();
    void doneListening();
    void falsePositiveWakeWord();
    void wakeWordDetected();

protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;

private:
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void parseText(const char *json);
    LIBVOSKSPEECHTOTEXT_NO_EXPORT void parsePartial(const char *json);
    QString mWakeWord;
    bool mIsAsking = false;
    bool mIsListiningBecauseOfWakeWord = false;
#if HAVE_VOSK_API_SUPPORT
    VoskModel *mModel = nullptr;
    VoskRecognizer *mRecognizer = nullptr;
#endif
};
Q_DECLARE_TYPEINFO(VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo, Q_MOVABLE_TYPE);
LIBVOSKSPEECHTOTEXT_EXPORT QDebug operator<<(QDebug d, const VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo &t);
