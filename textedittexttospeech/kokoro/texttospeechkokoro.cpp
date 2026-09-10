/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoro.h"
#include "texttospeech_kokoro_lib_debug.h"
#include "texttospeechkokoroutils.h"

#include <KLocalizedString>
#include <QAudio>
#include <QAudioSink>
#include <QJsonDocument>
#include <QProcess>
#include <QTimer>
#include <algorithm>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;

namespace
{
// The sink is fed from the event loop: often enough to never starve it, rarely
// enough to stay cheap. Kokoro emits chunks of several seconds.
constexpr int s_writeIntervalMs = 20;

// The voice used when the engine did not choose one, as in kokoro_helper.py.
const char s_defaultVoice[] = "af_heart";

// Kokoro speaks at speed 1.0, QTextToSpeech at rate 0.0. Halving and doubling
// the speed is what the model stays intelligible with.
[[nodiscard]] double speedFromRate(double rate)
{
    return rate < 0.0 ? 1.0 + rate * 0.5 : 1.0 + rate;
}

[[nodiscard]] QAudioFormat::SampleFormat sampleFormat(const QString &name)
{
    // kokoro_helper.py only knows those two, int16 being what it defaults to.
    return name == "float"_L1 ? QAudioFormat::Float : QAudioFormat::Int16;
}
}

TextToSpeechKokoro::TextToSpeechKokoro(QObject *parent)
    : QObject{parent}
    , mVoiceIdentifier(QString::fromLatin1(s_defaultVoice))
    , mWriteTimer(new QTimer(this))
{
    mWriteTimer->setInterval(s_writeIntervalMs);
    connect(mWriteTimer, &QTimer::timeout, this, &TextToSpeechKokoro::slotWriteTimeout);
}

TextToSpeechKokoro::~TextToSpeechKokoro()
{
    stopPlayback();
    if (mProcess) {
        // The death of the backend must not be reported while this object is
        // being destroyed.
        disconnect(mProcess, nullptr, this, nullptr);
    }
    if (mProcess && mProcess->state() != QProcess::NotRunning) {
        // "quit" lets the script close the model cleanly, killing it is the
        // fallback for a backend stuck in a synthesis.
        mProcess->write(QByteArrayLiteral("{\"cmd\": \"quit\"}\n"));
        mProcess->closeWriteChannel();
        if (!mProcess->waitForFinished(2000)) {
            mProcess->kill();
            mProcess->waitForFinished(1000);
        }
    }
}

void TextToSpeechKokoro::say(const QString &text)
{
    startJob(text, Mode::Play);
}

void TextToSpeechKokoro::synthesize(const QString &text)
{
    startJob(text, Mode::Synthesize);
}

void TextToSpeechKokoro::startJob(const QString &text, Mode mode)
{
    // Only one utterance at a time: the previous one is dropped, as every other
    // QTextToSpeech engine does.
    stop();
    if (text.trimmed().isEmpty()) {
        return;
    }
    if (!ensureBackend()) {
        return;
    }
    mMode = mode;
    mEndOfStream = false;
    mCurrentJobId = ++mLastJobId;
    sendRequest({
        {"cmd"_L1, "say"_L1},
        {"id"_L1, mCurrentJobId},
        {"text"_L1, text},
        {"voice"_L1, mVoiceIdentifier},
        {"speed"_L1, speedFromRate(mRate)},
        {"sampleFormat"_L1, "int16"_L1},
    });
    setState(mode == Mode::Play ? QTextToSpeech::Speaking : QTextToSpeech::Synthesizing);
}

bool TextToSpeechKokoro::ensureBackend()
{
    if (mProcess && mProcess->state() != QProcess::NotRunning) {
        return true;
    }
    if (mProcess) {
        // Nothing this dead backend could still say is of any interest.
        disconnect(mProcess, nullptr, this, nullptr);
        mProcess->deleteLater();
        mProcess = nullptr;
    }

    const QString python = TextToSpeechKokoroUtils::venvPython();
    const QString script = TextToSpeechKokoroUtils::pythonScriptPath();
    if (python.isEmpty() || script.isEmpty()) {
        setError(QTextToSpeech::ErrorReason::Initialization, i18n("Kokoro is not installed. Please install it first."));
        return false;
    }

    mStdoutBuffer.clear();
    mPendingFrame = {};
    mPendingPayloadSize = 0;

    mProcess = new QProcess(this);
    connect(mProcess, &QProcess::readyReadStandardOutput, this, &TextToSpeechKokoro::slotReadyReadStandardOutput);
    connect(mProcess, &QProcess::readyReadStandardError, this, [this]() {
        // The script logs on stderr: torch and HuggingFace are chatty, and the
        // protocol would be corrupted if that went to stdout.
        qCDebug(KOKORO_TEXT_TO_SPEECH_LIB_LOG) << "kokoro:" << mProcess->readAllStandardError().trimmed();
    });
    connect(mProcess, &QProcess::finished, this, [this](int exitCode, QProcess::ExitStatus exitStatus) {
        stopPlayback();
        mCurrentJobId = 0;
        // The next say() starts a new backend, this one cannot be reused.
        mProcess->deleteLater();
        mProcess = nullptr;
        if (exitStatus != QProcess::NormalExit || exitCode != 0) {
            setError(QTextToSpeech::ErrorReason::Playback, i18n("The Kokoro backend stopped unexpectedly."));
        }
    });
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        // finished() is not emitted when the process could not be started at all.
        if (error == QProcess::FailedToStart) {
            setError(QTextToSpeech::ErrorReason::Initialization, i18n("Unable to start the Kokoro backend."));
        }
    });
    // QProcess buffers what is written while it is starting, so the first
    // request does not have to wait for started().
    mProcess->start(python, {script, u"serve"_s});
    return true;
}

void TextToSpeechKokoro::sendRequest(const QJsonObject &request)
{
    if (!mProcess) {
        return;
    }
    mProcess->write(QJsonDocument(request).toJson(QJsonDocument::Compact) + '\n');
}

void TextToSpeechKokoro::cancelCurrentJob()
{
    if (mCurrentJobId == 0) {
        return;
    }
    // Without this the backend would keep synthesizing chunks nobody plays.
    sendRequest({{"cmd"_L1, "cancel"_L1}, {"id"_L1, mCurrentJobId}});
    mCurrentJobId = 0;
}

void TextToSpeechKokoro::slotReadyReadStandardOutput()
{
    mStdoutBuffer.append(mProcess->readAllStandardOutput());
    while (true) {
        if (mPendingPayloadSize > 0) {
            if (mStdoutBuffer.size() < mPendingPayloadSize) {
                return;
            }
            const QByteArray payload = mStdoutBuffer.first(mPendingPayloadSize);
            mStdoutBuffer.remove(0, mPendingPayloadSize);
            mPendingPayloadSize = 0;
            handleFrame(std::exchange(mPendingFrame, {}), payload);
            continue;
        }
        const qsizetype endOfLine = mStdoutBuffer.indexOf('\n');
        if (endOfLine == -1) {
            return;
        }
        const QByteArray line = mStdoutBuffer.first(endOfLine);
        mStdoutBuffer.remove(0, endOfLine + 1);
        QJsonParseError parseError;
        const QJsonObject frame = QJsonDocument::fromJson(line, &parseError).object();
        if (parseError.error != QJsonParseError::NoError) {
            qCWarning(KOKORO_TEXT_TO_SPEECH_LIB_LOG) << "Malformed frame:" << parseError.errorString() << line;
            continue;
        }
        // A frame declaring a size is immediately followed by that many raw bytes.
        if (const qsizetype size = frame.value("size"_L1).toInteger(); size > 0) {
            mPendingFrame = frame;
            mPendingPayloadSize = size;
            continue;
        }
        handleFrame(frame, {});
    }
}

void TextToSpeechKokoro::handleFrame(const QJsonObject &frame, const QByteArray &payload)
{
    const QString type = frame.value("type"_L1).toString();
    if (type == "error"_L1 && !frame.contains("id"_L1)) {
        // A protocol error, not the failure of a given synthesis.
        qCWarning(KOKORO_TEXT_TO_SPEECH_LIB_LOG) << "Kokoro error:" << frame;
        setError(QTextToSpeech::ErrorReason::Input, frame.value("message"_L1).toString());
        return;
    }
    if (type == "ready"_L1) {
        qCDebug(KOKORO_TEXT_TO_SPEECH_LIB_LOG) << "Kokoro backend ready:" << frame;
        return;
    }
    // Frames of a job which was cancelled or replaced: there is nothing left to
    // play, and reporting its end would clear the state of the current one.
    if (mCurrentJobId == 0 || frame.value("id"_L1).toInt() != mCurrentJobId) {
        return;
    }
    if (type == "format"_L1) {
        handleFormatFrame(frame);
    } else if (type == "chunk"_L1) {
        handleChunkFrame(payload);
    } else if (type == "end"_L1) {
        handleEndFrame();
    } else if (type == "error"_L1) {
        const QString message = frame.value("message"_L1).toString();
        qCWarning(KOKORO_TEXT_TO_SPEECH_LIB_LOG) << "Kokoro synthesis failed:" << message;
        // The backend is already done with that job, there is nothing to cancel.
        mCurrentJobId = 0;
        stopPlayback();
        setError(QTextToSpeech::ErrorReason::Input, i18n("Kokoro was unable to synthesize the text: %1", message));
    } else {
        qCWarning(KOKORO_TEXT_TO_SPEECH_LIB_LOG) << "Unknown frame type:" << type;
    }
}

void TextToSpeechKokoro::handleFormatFrame(const QJsonObject &frame)
{
    QAudioFormat format;
    format.setSampleRate(frame.value("sampleRate"_L1).toInt());
    format.setChannelCount(frame.value("channels"_L1).toInt());
    format.setSampleFormat(sampleFormat(frame.value("sampleFormat"_L1).toString()));
    if (!format.isValid()) {
        cancelCurrentJob();
        stopPlayback();
        setError(QTextToSpeech::ErrorReason::Playback, i18n("Kokoro reported an unusable audio format."));
        return;
    }
    mAudioFormat = format;
    if (mMode == Mode::Play) {
        startPlayback(format);
    }
}

void TextToSpeechKokoro::handleChunkFrame(const QByteArray &payload)
{
    if (mMode == Mode::Synthesize) {
        Q_EMIT synthesized(mAudioFormat, payload);
        return;
    }
    mPendingAudio.append(payload);
    writePendingAudio();
}

void TextToSpeechKokoro::handleEndFrame()
{
    mEndOfStream = true;
    // In synthesize mode, and when the text produced no audio at all, there is
    // nothing left to wait for.
    if (mMode == Mode::Synthesize || !mAudioSink) {
        stopPlayback();
        mCurrentJobId = 0;
        setState(QTextToSpeech::Ready);
        return;
    }
    // Otherwise the sink still has to play what was already handed to it,
    // slotWriteTimeout() reports the end once it ran dry.
    slotWriteTimeout();
}

void TextToSpeechKokoro::startPlayback(const QAudioFormat &format)
{
    stopPlayback();
    mAudioSink = new QAudioSink(format, this);
    mAudioSink->setVolume(QtAudio::convertVolume(mVolume, QtAudio::LogarithmicVolumeScale, QtAudio::LinearVolumeScale));
    mAudioDevice = mAudioSink->start();
    if (!mAudioDevice) {
        cancelCurrentJob();
        stopPlayback();
        setError(QTextToSpeech::ErrorReason::Playback, i18n("Unable to open the audio device."));
        return;
    }
    mWriteTimer->start();
}

void TextToSpeechKokoro::stopPlayback()
{
    mWriteTimer->stop();
    mPendingAudio.clear();
    if (mAudioSink) {
        mAudioSink->stop();
        mAudioSink->deleteLater();
        mAudioSink = nullptr;
        // Owned by the sink, which just closed it.
        mAudioDevice = nullptr;
    }
}

void TextToSpeechKokoro::writePendingAudio()
{
    if (!mAudioDevice || mPendingAudio.isEmpty()) {
        return;
    }
    const qint64 bytesFree = mAudioSink->bytesFree();
    if (bytesFree <= 0) {
        return;
    }
    const qint64 written = mAudioDevice->write(mPendingAudio.constData(), std::min<qint64>(bytesFree, mPendingAudio.size()));
    if (written > 0) {
        mPendingAudio.remove(0, written);
    }
}

void TextToSpeechKokoro::slotWriteTimeout()
{
    writePendingAudio();
    // The sink only falls back to idle once it played everything it was given,
    // which, the backend being done, is the end of the utterance.
    if (mEndOfStream && mPendingAudio.isEmpty() && mAudioSink && mAudioSink->state() == QtAudio::IdleState) {
        stopPlayback();
        mCurrentJobId = 0;
        setState(QTextToSpeech::Ready);
    }
}

void TextToSpeechKokoro::stop()
{
    cancelCurrentJob();
    stopPlayback();
    mEndOfStream = false;
    setState(QTextToSpeech::Ready);
}

void TextToSpeechKokoro::pause()
{
    if (mState != QTextToSpeech::Speaking || !mAudioSink) {
        return;
    }
    // The backend keeps synthesizing, its chunks pile up in mPendingAudio.
    mWriteTimer->stop();
    mAudioSink->suspend();
    setState(QTextToSpeech::Paused);
}

void TextToSpeechKokoro::resume()
{
    if (mState != QTextToSpeech::Paused || !mAudioSink) {
        return;
    }
    mAudioSink->resume();
    mWriteTimer->start();
    setState(QTextToSpeech::Speaking);
}

double TextToSpeechKokoro::rate() const
{
    return mRate;
}

bool TextToSpeechKokoro::setRate(double rate)
{
    if (rate < -1.0 || rate > 1.0) {
        return false;
    }
    // Kokoro is told the speed with the request, so it only applies to the next
    // utterance.
    mRate = rate;
    return true;
}

double TextToSpeechKokoro::volume() const
{
    return mVolume;
}

bool TextToSpeechKokoro::setVolume(double volume)
{
    if (volume < 0.0 || volume > 1.0) {
        return false;
    }
    mVolume = volume;
    if (mAudioSink) {
        mAudioSink->setVolume(QtAudio::convertVolume(mVolume, QtAudio::LogarithmicVolumeScale, QtAudio::LinearVolumeScale));
    }
    return true;
}

QString TextToSpeechKokoro::voiceIdentifier() const
{
    return mVoiceIdentifier;
}

bool TextToSpeechKokoro::setVoiceIdentifier(const QString &identifier)
{
    // The language of the pipeline is derived from the identifier, an unknown
    // one would make the backend fail on the next say().
    if (TextToSpeechKokoroUtils::languageCode(identifier).isEmpty()) {
        return false;
    }
    mVoiceIdentifier = identifier;
    return true;
}

QTextToSpeech::State TextToSpeechKokoro::state() const
{
    return mState;
}

QTextToSpeech::ErrorReason TextToSpeechKokoro::errorReason() const
{
    return mErrorReason;
}

QString TextToSpeechKokoro::errorString() const
{
    return mErrorString;
}

void TextToSpeechKokoro::setState(QTextToSpeech::State state)
{
    if (mState == state) {
        return;
    }
    if (state != QTextToSpeech::Error) {
        mErrorReason = QTextToSpeech::ErrorReason::NoError;
        mErrorString.clear();
    }
    mState = state;
    Q_EMIT stateChanged(mState);
}

void TextToSpeechKokoro::setError(QTextToSpeech::ErrorReason reason, const QString &errorString)
{
    mErrorReason = reason;
    mErrorString = errorString;
    setState(QTextToSpeech::Error);
    Q_EMIT errorOccurred(mErrorReason, mErrorString);
}

#include "moc_texttospeechkokoro.cpp"
