/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextdevice.h"
#include "speechtotextwhisper_lib_debug.h"
#include "whisperspeechtotextutils.h"

#include <KLocalizedString>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QProcess>

using namespace Qt::Literals::StringLiterals;

namespace
{
// The script keeps its own default for whatever it is not told about: an empty
// value must not be sent as an empty string, it would override it with nothing.
void insertIfNotEmpty(QJsonObject &request, const QString &key, const QString &value)
{
    if (!value.isEmpty()) {
        request.insert(key, value);
    }
}
}

WhisperSpeechToTextDevice::WhisperSpeechToTextDevice(QObject *parent)
    : QIODevice{parent}
{
    if (!open(QIODevice::ReadWrite)) {
        qCWarning(SPEECHTOTEXT_WHISPER_LIB_LOG) << "Impossible to open WhisperSpeechToTextDevice";
    }
}

WhisperSpeechToTextDevice::~WhisperSpeechToTextDevice()
{
    if (!mProcess || mProcess->state() == QProcess::NotRunning) {
        return;
    }
    mQuitting = true;
    sendRequest({{u"cmd"_s, u"quit"_s}});
    mProcess->closeWriteChannel();
    // "quit" makes the script leave its loop; killing it right away could cut a
    // model download in the middle of the file it is writing in the cache.
    if (!mProcess->waitForFinished(2000)) {
        mProcess->kill();
        mProcess->waitForFinished(1000);
    }
}

bool WhisperSpeechToTextDevice::initialize(WhisperSpeechToTextDeviceInfo &&info)
{
    // The script reloads the model by itself when a dictation asks for another
    // one, so new settings do not need a new process.
    mInfo = std::move(info);
    return startProcess();
}

WhisperSpeechToTextDevice::WhisperSpeechToTextDeviceInfo WhisperSpeechToTextDevice::info() const
{
    return mInfo;
}

bool WhisperSpeechToTextDevice::available() const
{
    return mProcess && mProcess->state() == QProcess::Running && mAvailable;
}

bool WhisperSpeechToTextDevice::startProcess()
{
    if (mProcess && mProcess->state() != QProcess::NotRunning) {
        return true;
    }
    const QString python = WhisperSpeechToTextUtils::venvPython();
    const QString script = WhisperSpeechToTextUtils::pythonScriptPath();
    if (python.isEmpty() || script.isEmpty()) {
        // Nothing to talk to: the python side has not been installed yet.
        qCWarning(SPEECHTOTEXT_WHISPER_LIB_LOG) << "Unable to start whisper: python" << python << "script" << script;
        return false;
    }
    if (!mProcess) {
        mProcess = new QProcess(this);
        connect(mProcess, &QProcess::readyReadStandardOutput, this, &WhisperSpeechToTextDevice::readFrames);
        // The script logs on stderr, and it redirects there what the libraries it
        // loads print, so that they cannot corrupt the frames of stdout.
        connect(mProcess, &QProcess::readyReadStandardError, this, [this]() {
            qCDebug(SPEECHTOTEXT_WHISPER_LIB_LOG) << "whisper_helper.py:" << mProcess->readAllStandardError().trimmed();
        });
        connect(mProcess, &QProcess::finished, this, [this](int exitCode, QProcess::ExitStatus exitStatus) {
            mDictationRunning = false;
            mBuffer.clear();
            if (mQuitting) {
                return;
            }
            qCWarning(SPEECHTOTEXT_WHISPER_LIB_LOG) << "whisper_helper.py stopped. Exit code:" << exitCode << exitStatus;
            Q_EMIT errorOccurred(i18n("The whisper backend stopped unexpectedly."));
        });
    }
    mBuffer.clear();
    mDictationRunning = false;
    mAvailable = true;
    mQuitting = false;
    mProcess->start(python, {script, u"serve"_s});
    // Nothing can be sent to a process which is not started yet, and the caller
    // asks for a yes or no answer.
    if (!mProcess->waitForStarted(5000)) {
        qCWarning(SPEECHTOTEXT_WHISPER_LIB_LOG) << "Unable to start" << python << mProcess->errorString();
        return false;
    }
    return true;
}

void WhisperSpeechToTextDevice::clear()
{
    // A script which died must not make the engine mute for the rest of the session.
    if (!startProcess()) {
        return;
    }
    if (mDictationRunning) {
        // What the previous dictation had buffered is not wanted any more.
        sendRequest({{u"cmd"_s, u"cancel"_s}, {u"id"_s, mJobId}});
    }
    ++mJobId;
    QJsonObject request{{u"cmd"_s, u"start"_s},
                        {u"id"_s, mJobId},
                        // QAudioSource is configured with Int16 by SpeechToTextManager.
                        {u"sampleFormat"_s, u"int16"_s},
                        {u"partials"_s, mInfo.partials}};
    insertIfNotEmpty(request, u"model"_s, mInfo.model);
    insertIfNotEmpty(request, u"language"_s, mInfo.language);
    insertIfNotEmpty(request, u"computeType"_s, mInfo.computeType);
    insertIfNotEmpty(request, u"device"_s, mInfo.device);
    insertIfNotEmpty(request, u"prompt"_s, mInfo.prompt);
    sendRequest(request);
    mDictationRunning = true;
}

void WhisperSpeechToTextDevice::finish()
{
    if (!mDictationRunning) {
        return;
    }
    sendRequest({{u"cmd"_s, u"stop"_s}, {u"id"_s, mJobId}});
    mDictationRunning = false;
}

void WhisperSpeechToTextDevice::sendRequest(QJsonObject request, const QByteArray &payload)
{
    if (!mProcess || mProcess->state() != QProcess::Running) {
        qCWarning(SPEECHTOTEXT_WHISPER_LIB_LOG) << "Unable to send" << request << ": whisper_helper.py is not running";
        return;
    }
    if (!payload.isEmpty()) {
        request.insert(u"size"_s, static_cast<qint64>(payload.size()));
    }
    mProcess->write(QJsonDocument(request).toJson(QJsonDocument::Compact));
    mProcess->write("\n");
    if (!payload.isEmpty()) {
        mProcess->write(payload);
    }
}

QList<QJsonObject> WhisperSpeechToTextDevice::takeFrames(QByteArray &buffer)
{
    QList<QJsonObject> frames;
    qsizetype consumed = 0;
    while (true) {
        const qsizetype endOfLine = buffer.indexOf('\n', consumed);
        if (endOfLine < 0) {
            break;
        }
        const QJsonObject frame = QJsonDocument::fromJson(buffer.mid(consumed, endOfLine - consumed)).object();
        // No frame of the engine carries a payload today, but one which did would
        // otherwise be read as if its bytes were the next line.
        const qsizetype payloadSize = qMax(qint64{0}, frame.value(u"size"_s).toInteger());
        if (endOfLine + 1 + payloadSize > buffer.size()) {
            // The payload is not there yet: the frame is taken on the next read.
            break;
        }
        consumed = endOfLine + 1 + payloadSize;
        if (!frame.isEmpty()) {
            frames.append(frame);
        }
    }
    buffer.remove(0, consumed);
    return frames;
}

void WhisperSpeechToTextDevice::readFrames()
{
    mBuffer += mProcess->readAllStandardOutput();
    const QList<QJsonObject> frames = takeFrames(mBuffer);
    for (const QJsonObject &frame : frames) {
        processFrame(frame);
    }
}

void WhisperSpeechToTextDevice::processFrame(const QJsonObject &frame)
{
    const QString type = frame.value(u"type"_s).toString();
    if (type == "final"_L1 || type == "partial"_L1) {
        // Answers of a dictation which was cancelled are not what the caller waits for.
        if (frame.value(u"id"_s).toInt() != mJobId) {
            return;
        }
        const QString text = frame.value(u"text"_s).toString().trimmed();
        if (text.isEmpty()) {
            return;
        }
        if (type == "final"_L1) {
            Q_EMIT result(text);
        } else {
            Q_EMIT partialResult(text);
        }
    } else if (type == "end"_L1) {
        if (frame.value(u"id"_s).toInt() == mJobId) {
            Q_EMIT doneListening();
        }
    } else if (type == "ready"_L1) {
        mAvailable = frame.value(u"available"_s).toBool();
        if (!mAvailable) {
            QStringList missing;
            const QJsonArray array = frame.value(u"missing"_s).toArray();
            for (const auto &value : array) {
                missing.append(value.toString());
            }
            qCWarning(SPEECHTOTEXT_WHISPER_LIB_LOG) << "whisper is not usable, missing:" << missing;
            Q_EMIT errorOccurred(i18n("Whisper is not installed. Missing: %1", missing.join(", "_L1)));
        }
    } else if (type == "error"_L1) {
        const QString message = frame.value(u"message"_s).toString();
        qCWarning(SPEECHTOTEXT_WHISPER_LIB_LOG) << "whisper_helper.py reported:" << message;
        Q_EMIT errorOccurred(message);
    } else {
        qCDebug(SPEECHTOTEXT_WHISPER_LIB_LOG) << "Unhandled frame:" << frame;
    }
}

qint64 WhisperSpeechToTextDevice::readData([[maybe_unused]] char *data, [[maybe_unused]] qint64 maxlen)
{
    return 0;
}

qint64 WhisperSpeechToTextDevice::writeData(const char *data, qint64 len)
{
    // Audio captured before clear() started a dictation has nowhere to go, and
    // dropping it is what the caller expects: it is not an error.
    if (mDictationRunning && len > 0) {
        sendRequest({{u"cmd"_s, u"audio"_s}, {u"id"_s, mJobId}}, QByteArray(data, len));
    }
    return len;
}

bool WhisperSpeechToTextDevice::isSequential() const
{
    return true;
}

QDebug operator<<(QDebug d, const WhisperSpeechToTextDevice::WhisperSpeechToTextDeviceInfo &t)
{
    d.space() << "model" << t.model;
    d.space() << "language" << t.language;
    d.space() << "computeType" << t.computeType;
    d.space() << "device" << t.device;
    d.space() << "prompt" << t.prompt;
    d.space() << "partials" << t.partials;
    return d;
}

#include "moc_whisperspeechtotextdevice.cpp"
