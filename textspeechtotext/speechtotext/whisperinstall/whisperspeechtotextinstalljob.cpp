/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstalljob.h"
#include "speechtotextwhisperinstall_lib_debug.h"
#include "whisperspeechtotextutils.h"

using namespace Qt::Literals::StringLiterals;

WhisperSpeechToTextInstallJob::WhisperSpeechToTextInstallJob(QObject *parent)
    : QObject{parent}
{
}

WhisperSpeechToTextInstallJob::~WhisperSpeechToTextInstallJob() = default;

bool WhisperSpeechToTextInstallJob::canStart() const
{
    // Without the virtualenv there is no pip to install the modules with.
    return !mModules.isEmpty() && !WhisperSpeechToTextUtils::venvPip().isEmpty();
}

QStringList WhisperSpeechToTextInstallJob::modules() const
{
    return mModules;
}

void WhisperSpeechToTextInstallJob::setModules(const QStringList &newModules)
{
    mModules = newModules;
}

void WhisperSpeechToTextInstallJob::start()
{
    if (!canStart()) {
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Impossible to start WhisperSpeechToTextInstallJob";
        Q_EMIT installFailed();
        deleteLater();
        return;
    }
    mRemainingModules = mModules;

    mProcess = new QProcess(this);
    // pip reports its progress on stdout, its warnings on stderr.
    mProcess->setProcessChannelMode(QProcess::MergedChannels);
    connect(mProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        Q_EMIT installMessage(QString::fromUtf8(mProcess->readAllStandardOutput()));
    });
    connect(mProcess, &QProcess::finished, this, &WhisperSpeechToTextInstallJob::slotFinished);
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        // finished() is not emitted when the process could not be started at all.
        if (error == QProcess::FailedToStart) {
            failed(u"Unable to start "_s + mProcess->program());
        }
    });
    installNextModule();
}

void WhisperSpeechToTextInstallJob::installNextModule()
{
    if (mRemainingModules.isEmpty()) {
        Q_EMIT installDone();
        deleteLater();
        return;
    }
    const QString module = mRemainingModules.takeFirst();
    mProcess->start(WhisperSpeechToTextUtils::venvPip(), {u"install"_s, module});
}

void WhisperSpeechToTextInstallJob::slotFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus != QProcess::NormalExit || exitCode != 0) {
        failed(u"Unable to install module. Exit code: "_s + QString::number(exitCode));
        return;
    }
    installNextModule();
}

void WhisperSpeechToTextInstallJob::failed(const QString &errorMessage)
{
    qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << errorMessage;
    Q_EMIT installMessage(errorMessage);
    Q_EMIT installFailed();
    deleteLater();
}

#include "moc_whisperspeechtotextinstalljob.cpp"
