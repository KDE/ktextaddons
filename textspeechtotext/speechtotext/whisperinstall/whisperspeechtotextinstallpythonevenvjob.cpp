/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstallpythonevenvjob.h"
#include "speechtotextwhisperinstall_lib_debug.h"
#include "whisperspeechtotextutils.h"

#include <QDir>
#include <QProcess>

using namespace Qt::Literals::StringLiterals;

WhisperSpeechToTextInstallPythonEvenvJob::WhisperSpeechToTextInstallPythonEvenvJob(QObject *parent)
    : QObject{parent}
{
}

WhisperSpeechToTextInstallPythonEvenvJob::~WhisperSpeechToTextInstallPythonEvenvJob() = default;

bool WhisperSpeechToTextInstallPythonEvenvJob::canStart() const
{
    // Without the interpreter whisper needs there is no venv to create.
    return !WhisperSpeechToTextUtils::pythonVersionPath().isEmpty() && !WhisperSpeechToTextUtils::defaultVenvPath().isEmpty();
}

void WhisperSpeechToTextInstallPythonEvenvJob::start()
{
    if (!canStart()) {
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Impossible to start WhisperSpeechToTextInstallPythonEvenvJob";
        Q_EMIT installFailed();
        deleteLater();
        return;
    }
    const QString venvPath = WhisperSpeechToTextUtils::defaultVenvPath();
    // A previous environment can be broken or built against another python, so it is replaced.
    if (QDir venvDir(venvPath); venvDir.exists() && !venvDir.removeRecursively()) {
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Impossible to remove existing venv:" << venvPath;
        Q_EMIT installFailed();
        deleteLater();
        return;
    }

    auto process = new QProcess(this);
    connect(process, &QProcess::finished, this, [this, process, venvPath](int exitCode, QProcess::ExitStatus exitStatus) {
        process->deleteLater();
        if (exitStatus != QProcess::NormalExit || exitCode != 0) {
            qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Unable to create venv" << venvPath << process->readAllStandardError();
            Q_EMIT installFailed();
        } else if (WhisperSpeechToTextUtils::venvPip().isEmpty()) {
            // python -m venv can return 0 and still not have produced a usable pip.
            qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Virtualenv created without pip:" << WhisperSpeechToTextUtils::defaultVenvPip();
            Q_EMIT installFailed();
        } else {
            Q_EMIT installDone();
        }
        deleteLater();
    });
    connect(process, &QProcess::errorOccurred, this, [this, process](QProcess::ProcessError error) {
        // finished() is not emitted when the process could not be started at all.
        if (error == QProcess::FailedToStart) {
            qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Unable to start" << process->program();
            process->deleteLater();
            Q_EMIT installFailed();
            deleteLater();
        }
    });
    process->start(WhisperSpeechToTextUtils::pythonVersionPath(), {u"-m"_s, u"venv"_s, venvPath});
}

#include "moc_whisperspeechtotextinstallpythonevenvjob.cpp"
