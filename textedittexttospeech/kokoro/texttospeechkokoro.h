/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "kokorotexttospeech_export.h"

#include <QAudioFormat>
#include <QJsonObject>
#include <QObject>
#include <QTextToSpeech>

class QAudioSink;
class QIODevice;
class QProcess;
class QTimer;

namespace TextEditTextToSpeech
{
/*!
 * \class TextEditTextToSpeech::TextToSpeechKokoro
 *
 * \brief Drives the kokoro_helper.py backend and plays back what it synthesizes.
 *
 * The script is started once, in "serve" mode, and kept alive: loading the
 * model costs several seconds, paying it for every sentence is not an option.
 * It reads one JSON request per line on stdin and answers on stdout with
 * frames, a JSON line optionally followed by exactly "size" bytes of raw PCM.
 *
 * Each chunk is pushed to the QAudioSink as soon as it arrives, so that the
 * first sentence is heard while the next ones are still being synthesized.
 *
 * This class knows nothing about QVoice: the engine hands over the Kokoro
 * identifier ("ff_siwis") that the backend expects.
 */
class KOKOROTEXTTOSPEECH_EXPORT TextToSpeechKokoro : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoro(QObject *parent = nullptr);
    ~TextToSpeechKokoro() override;

    /*! Synthesizes \a text and plays it. */
    void say(const QString &text);

    /*!
     * Synthesizes \a text without playing it: the audio is reported by
     * synthesized() instead.
     */
    void synthesize(const QString &text);

    /*!
     * Cancels what is being said and drops the audio which was not played yet.
     *
     * Kokoro can only be interrupted between two chunks, so the boundary hints
     * finer than a chunk cannot be honoured and the playback always stops
     * immediately.
     */
    void stop();

    /*! Suspends the playback, it can be restarted with resume(). */
    void pause();
    void resume();

    /*! The rate in the QTextToSpeech range, -1.0 (slowest) to 1.0 (fastest). */
    [[nodiscard]] double rate() const;
    bool setRate(double rate);

    /*! The volume in the QTextToSpeech range, 0.0 to 1.0. */
    [[nodiscard]] double volume() const;
    bool setVolume(double volume);

    /*! The Kokoro voice identifier, for example "ff_siwis". */
    [[nodiscard]] QString voiceIdentifier() const;
    bool setVoiceIdentifier(const QString &identifier);

    [[nodiscard]] QTextToSpeech::State state() const;
    [[nodiscard]] QTextToSpeech::ErrorReason errorReason() const;
    [[nodiscard]] QString errorString() const;

Q_SIGNALS:
    void stateChanged(QTextToSpeech::State state);
    void errorOccurred(QTextToSpeech::ErrorReason reason, const QString &errorString);
    void synthesized(const QAudioFormat &format, const QByteArray &data);

private:
    /*! What has to be done with the audio of the job which is running. */
    enum class Mode : uint8_t {
        Play,
        Synthesize,
    };

    KOKOROTEXTTOSPEECH_NO_EXPORT void startJob(const QString &text, Mode mode);
    [[nodiscard]] KOKOROTEXTTOSPEECH_NO_EXPORT bool ensureBackend();
    KOKOROTEXTTOSPEECH_NO_EXPORT void sendRequest(const QJsonObject &request);
    /*! Tells the backend to drop the job which is running, if there is one. */
    KOKOROTEXTTOSPEECH_NO_EXPORT void cancelCurrentJob();

    KOKOROTEXTTOSPEECH_NO_EXPORT void slotReadyReadStandardOutput();
    KOKOROTEXTTOSPEECH_NO_EXPORT void handleFrame(const QJsonObject &frame, const QByteArray &payload);
    KOKOROTEXTTOSPEECH_NO_EXPORT void handleFormatFrame(const QJsonObject &frame);
    KOKOROTEXTTOSPEECH_NO_EXPORT void handleChunkFrame(const QByteArray &payload);
    KOKOROTEXTTOSPEECH_NO_EXPORT void handleEndFrame();

    KOKOROTEXTTOSPEECH_NO_EXPORT void startPlayback(const QAudioFormat &format);
    KOKOROTEXTTOSPEECH_NO_EXPORT void stopPlayback();
    KOKOROTEXTTOSPEECH_NO_EXPORT void writePendingAudio();
    KOKOROTEXTTOSPEECH_NO_EXPORT void slotWriteTimeout();

    KOKOROTEXTTOSPEECH_NO_EXPORT void setState(QTextToSpeech::State state);
    KOKOROTEXTTOSPEECH_NO_EXPORT void setError(QTextToSpeech::ErrorReason reason, const QString &errorString);

    QString mVoiceIdentifier;
    QString mErrorString;
    QByteArray mStdoutBuffer;
    /*! Audio synthesized but not handed over to the sink yet. */
    QByteArray mPendingAudio;
    /*! The frame whose payload is still being read. */
    QJsonObject mPendingFrame;
    QAudioFormat mAudioFormat;
    double mRate = 0.0;
    double mVolume = 1.0;
    qsizetype mPendingPayloadSize = 0;
    int mCurrentJobId = 0;
    int mLastJobId = 0;
    QTextToSpeech::State mState = QTextToSpeech::Ready;
    QTextToSpeech::ErrorReason mErrorReason = QTextToSpeech::ErrorReason::NoError;
    Mode mMode = Mode::Play;
    /*! Whether the backend is done with the job which is running. */
    bool mEndOfStream = false;
    QProcess *mProcess = nullptr;
    QAudioSink *mAudioSink = nullptr;
    /*! Owned by mAudioSink. */
    QIODevice *mAudioDevice = nullptr;
    QTimer *const mWriteTimer;
};
}
