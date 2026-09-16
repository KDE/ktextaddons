/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextcachedmodelsjob.h"
#include "speechtotextwhisperinstall_lib_debug.h"
#include "whisperspeechtotextdownloadmodeljob.h"
#include "whisperspeechtotextutils.h"

using namespace Qt::Literals::StringLiterals;

WhisperSpeechToTextCachedModelsJob::WhisperSpeechToTextCachedModelsJob(QObject *parent)
    : QObject{parent}
{
}

WhisperSpeechToTextCachedModelsJob::~WhisperSpeechToTextCachedModelsJob()
{
    if (mProcess && mProcess->state() != QProcess::NotRunning) {
        // Killing it makes it report that it failed, and answering that from a
        // destructor would call a slot of an object which is being destroyed.
        disconnect(mProcess, nullptr, this, nullptr);
        mProcess->kill();
        mProcess->waitForFinished(1000);
    }
}

bool WhisperSpeechToTextCachedModelsJob::canStart() const
{
    // Looking at the cache is huggingface_hub's job, and it lives in the virtualenv.
    return !WhisperSpeechToTextUtils::pythonScriptPath().isEmpty() && !WhisperSpeechToTextUtils::venvPython().isEmpty();
}

QStringList WhisperSpeechToTextCachedModelsJob::parseCachedModels(const QByteArray &output)
{
    QStringList models;
    // The script answers one json line per model, the same events a download uses.
    const QList<QByteArray> lines = output.split('\n');
    for (const QByteArray &line : lines) {
        const WhisperSpeechToTextDownloadModelJob::DownloadEvent event = WhisperSpeechToTextDownloadModelJob::parseEvent(line);
        if (event.type == "cached"_L1 && !event.model.isEmpty()) {
            models.append(event.model);
        }
    }
    return models;
}

void WhisperSpeechToTextCachedModelsJob::start()
{
    if (!canStart()) {
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Impossible to start WhisperSpeechToTextCachedModelsJob";
        Q_EMIT cachedModelsFailed();
        deleteLater();
        return;
    }
    auto process = new QProcess(this);
    mProcess = process;
    connect(process, &QProcess::finished, this, [this, process](int exitCode, QProcess::ExitStatus exitStatus) {
        process->deleteLater();
        if (exitStatus != QProcess::NormalExit || exitCode != 0) {
            qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "whisper cached models listing failed. Exit code:" << exitCode;
            Q_EMIT cachedModelsFailed();
        } else {
            // Nothing cached is a legitimate answer: it is what a fresh install is.
            Q_EMIT cachedModelsLoaded(parseCachedModels(process->readAllStandardOutput()));
        }
        deleteLater();
    });
    connect(process, &QProcess::errorOccurred, this, [this, process](QProcess::ProcessError error) {
        // finished() is not emitted when the process could not be started at all.
        if (error != QProcess::FailedToStart) {
            return;
        }
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Unable to start" << process->program() << process->errorString();
        process->deleteLater();
        Q_EMIT cachedModelsFailed();
        deleteLater();
    });
    process->start(WhisperSpeechToTextUtils::venvPython(), {WhisperSpeechToTextUtils::pythonScriptPath(), u"download"_s, u"--all"_s});
}

#include "moc_whisperspeechtotextcachedmodelsjob.cpp"
