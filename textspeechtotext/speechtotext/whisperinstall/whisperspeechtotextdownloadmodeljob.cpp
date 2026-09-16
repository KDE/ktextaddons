/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextdownloadmodeljob.h"
#include "speechtotextwhisperinstall_lib_debug.h"
#include "whisperspeechtotextutils.h"
#include <KLocalizedString>
#include <QJsonDocument>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;

bool WhisperSpeechToTextDownloadModelJob::DownloadEvent::isValid() const
{
    return !type.isEmpty();
}

WhisperSpeechToTextDownloadModelJob::WhisperSpeechToTextDownloadModelJob(QObject *parent)
    : QObject{parent}
{
}

WhisperSpeechToTextDownloadModelJob::~WhisperSpeechToTextDownloadModelJob()
{
    // Closing the dialog gives up the download, which huggingface_hub resumes
    // from what it already wrote the next time it is asked for.
    if (mProcess && mProcess->state() != QProcess::NotRunning) {
        // Killing it makes it report that it failed, and answering that from a
        // destructor would call a slot of an object which is being destroyed.
        disconnect(mProcess, nullptr, this, nullptr);
        mProcess->kill();
        mProcess->waitForFinished(1000);
    }
}

QString WhisperSpeechToTextDownloadModelJob::model() const
{
    return mModel;
}

void WhisperSpeechToTextDownloadModelJob::setModel(const QString &model)
{
    mModel = model;
}

bool WhisperSpeechToTextDownloadModelJob::wasCached() const
{
    return mWasCached;
}

bool WhisperSpeechToTextDownloadModelJob::canStart() const
{
    // Unlike the listing, the download needs huggingface_hub, which lives in the
    // virtualenv: there is nothing to download a model with before the install.
    return !mModel.isEmpty() && !WhisperSpeechToTextUtils::pythonScriptPath().isEmpty() && !WhisperSpeechToTextUtils::venvPython().isEmpty();
}

WhisperSpeechToTextDownloadModelJob::DownloadEvent WhisperSpeechToTextDownloadModelJob::parseEvent(const QByteArray &line)
{
    DownloadEvent event;
    const QJsonObject obj = QJsonDocument::fromJson(line).object();
    event.type = obj.value("type"_L1).toString();
    if (!event.isValid()) {
        return event;
    }
    event.model = obj.value("model"_L1).toString();
    event.message = obj.value("message"_L1).toString();
    event.path = obj.value("path"_L1).toString();
    event.received = obj.value("received"_L1).toInteger();
    event.total = obj.value("total"_L1).toInteger();
    if (obj.contains("percent"_L1)) {
        event.percent = obj.value("percent"_L1).toInt();
    }
    return event;
}

void WhisperSpeechToTextDownloadModelJob::start()
{
    if (!canStart()) {
        failed(u"Impossible to start WhisperSpeechToTextDownloadModelJob"_s);
        return;
    }
    mWasCached = false;
    mProcess = new QProcess(this);
    connect(mProcess, &QProcess::readyReadStandardOutput, this, &WhisperSpeechToTextDownloadModelJob::slotReadyReadStandardOutput);
    connect(mProcess, &QProcess::finished, this, &WhisperSpeechToTextDownloadModelJob::slotFinished);
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        // finished() is not emitted when the process could not be started at all.
        if (error == QProcess::FailedToStart) {
            failed(u"Unable to start "_s + mProcess->program());
        }
    });
    mProcess->start(WhisperSpeechToTextUtils::venvPython(), {WhisperSpeechToTextUtils::pythonScriptPath(), u"download"_s, u"--model"_s, mModel});
}

void WhisperSpeechToTextDownloadModelJob::slotReadyReadStandardOutput()
{
    mPendingOutput += mProcess->readAllStandardOutput();
    // The script prints one json line per event, and a read stops anywhere.
    for (qsizetype end = mPendingOutput.indexOf('\n'); end != -1; end = mPendingOutput.indexOf('\n')) {
        const DownloadEvent event = parseEvent(mPendingOutput.left(end));
        mPendingOutput.remove(0, end + 1);
        if (event.isValid()) {
            processEvent(event);
        }
    }
}

void WhisperSpeechToTextDownloadModelJob::processEvent(const DownloadEvent &event)
{
    if (event.type == "progress"_L1) {
        Q_EMIT downloadProgress(event.percent, event.received, event.total);
    } else if (event.type == "start"_L1) {
        Q_EMIT downloadMessage(i18n("Downloading the %1 model…", event.model));
    } else if (event.type == "cached"_L1) {
        mWasCached = true;
        Q_EMIT downloadMessage(i18n("The %1 model is already downloaded.", event.model));
    } else if (event.type == "finished"_L1) {
        Q_EMIT downloadMessage(i18n("The %1 model is downloaded.", event.model));
    } else if (event.type == "error"_L1) {
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Unable to download" << event.model << event.message;
        Q_EMIT downloadMessage(i18n("Unable to download the %1 model: %2", event.model, event.message));
    }
}

void WhisperSpeechToTextDownloadModelJob::slotFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    // The last line has no reason to be lost because the process is gone.
    slotReadyReadStandardOutput();
    mPendingOutput.clear();
    if (exitStatus != QProcess::NormalExit || exitCode != 0) {
        failed(u"Unable to download model "_s + mModel + u". Exit code: "_s + QString::number(exitCode));
        return;
    }
    Q_EMIT downloadModelDone();
    deleteLater();
}

void WhisperSpeechToTextDownloadModelJob::failed(const QString &errorMessage)
{
    qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << errorMessage;
    Q_EMIT downloadModelFailed();
    deleteLater();
}

#include "moc_whisperspeechtotextdownloadmodeljob.cpp"
