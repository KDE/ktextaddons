/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "speechtotextwhisper_export.h"
#include <QIODevice>
#include <QJsonObject>
#include <QList>
class QProcess;
class QDebug;

/*!
 * \brief Hands the captured audio over to whisper_helper.py and reports what it recognized.
 *
 * faster-whisper is a python library, so the recognition runs in the helper
 * script, started in its "serve" mode. The device talks to it over its
 * stdin/stdout with the frame protocol the script documents: one utf-8 json
 * line, immediately followed by the raw PCM when the frame declares a size.
 *
 * The audio QAudioSource pushes into writeData() is forwarded as it comes. The
 * script is the one which cuts it into utterances and decodes them, and it
 * answers with one "final" frame per utterance, hence result().
 */
class SPEECHTOTEXTWHISPER_EXPORT WhisperSpeechToTextDevice : public QIODevice
{
    Q_OBJECT
public:
    struct SPEECHTOTEXTWHISPER_EXPORT WhisperSpeechToTextDeviceInfo {
        /*! Model of the faster-whisper family ("small", "large-v3"…), empty for the one the script defaults to. */
        QString model;
        /*! Language of the dictation, empty to let whisper detect it. */
        QString language;
        /*! Quantization used by ctranslate2 ("int8", "float16"…), empty for the script default. */
        QString computeType;
        /*! "cpu" or "cuda", empty for the script default. */
        QString device;
        /*! Text biasing the recognition towards a vocabulary, empty when there is none. */
        QString prompt;
        /*! Ask for the intermediate results: each of them costs a full decoding. */
        bool partials = false;
    };

    explicit WhisperSpeechToTextDevice(QObject *parent = nullptr);
    ~WhisperSpeechToTextDevice() override;

    /*!
     * Stores the settings the next dictation is started with and makes sure the
     * script is running. Returns false when the python side is not installed.
     */
    [[nodiscard]] bool initialize(WhisperSpeechToTextDeviceInfo &&info);

    [[nodiscard]] WhisperSpeechToTextDeviceInfo info() const;

    /*! The script is running and did not report a broken installation. */
    [[nodiscard]] bool available() const;

    /*! Starts a new dictation, dropping what the previous one had buffered. */
    void clear();

    /*!
     * Ends the dictation: the script decodes the audio it has left and emits it.
     * Must be called once the audio capture is stopped, otherwise the last
     * utterance stays in the endpointer of the script and is never reported.
     */
    void finish();

    /*!
     * Extracts the complete frames of \a buffer, and removes them from it.
     *
     * A frame is one json line, plus the raw payload it declares with "size".
     * An incomplete frame is left in the buffer for the next read.
     */
    [[nodiscard]] static QList<QJsonObject> takeFrames(QByteArray &buffer);

    /*! The audio is a stream: nothing of what was written can be read back. */
    [[nodiscard]] bool isSequential() const override;

Q_SIGNALS:
    /*! One utterance was recognized. */
    void result(const QString &text);
    /*! What the script understood so far, only when partials were asked for. */
    void partialResult(const QString &text);
    /*! The script is done with everything finish() flushed. */
    void doneListening();
    void errorOccurred(const QString &message);

protected:
    /*! QAudioSource only pushes audio in, there is nothing to read from this device. */
    [[nodiscard]] qint64 readData(char *data, qint64 maxlen) override;
    [[nodiscard]] qint64 writeData(const char *data, qint64 len) override;

private:
    SPEECHTOTEXTWHISPER_NO_EXPORT [[nodiscard]] bool startProcess();
    SPEECHTOTEXTWHISPER_NO_EXPORT void sendRequest(QJsonObject request, const QByteArray &payload = {});
    SPEECHTOTEXTWHISPER_NO_EXPORT void readFrames();
    SPEECHTOTEXTWHISPER_NO_EXPORT void processFrame(const QJsonObject &frame);

    WhisperSpeechToTextDeviceInfo mInfo;
    QByteArray mBuffer;
    QProcess *mProcess = nullptr;
    /*! Identifies the dictation, so the answers of the previous one are not taken for its own. */
    int mJobId = 0;
    bool mDictationRunning = false;
    bool mAvailable = true;
    /*! The script was asked to leave: its exit is not a crash. */
    bool mQuitting = false;
};
Q_DECLARE_TYPEINFO(WhisperSpeechToTextDevice::WhisperSpeechToTextDeviceInfo, Q_RELOCATABLE_TYPE);
SPEECHTOTEXTWHISPER_EXPORT QDebug operator<<(QDebug d, const WhisperSpeechToTextDevice::WhisperSpeechToTextDeviceInfo &t);
