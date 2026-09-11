/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "texttospeechkokoroinstallpythonevenvjob.h"
#include "texttospeech_kokoroinstall_lib_debug.h"
#include "texttospeechkokoroutils.h"

#include <QDir>
#include <QProcess>

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;
TextToSpeechKokoroInstallPythonEvenvJob::TextToSpeechKokoroInstallPythonEvenvJob(QObject *parent)
    : QObject{parent}
{
}

TextToSpeechKokoroInstallPythonEvenvJob::~TextToSpeechKokoroInstallPythonEvenvJob() = default;

bool TextToSpeechKokoroInstallPythonEvenvJob::canStart() const
{
    // Without the interpreter kokoro needs there is no venv to create.
    return !TextToSpeechKokoroUtils::pythonVersionPath().isEmpty() && !TextToSpeechKokoroUtils::defaultVenvPath().isEmpty();
}

void TextToSpeechKokoroInstallPythonEvenvJob::start()
{
    if (!canStart()) {
        qCWarning(KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG) << "Impossible to start TextToSpeechKokoroInstallPythonEvenvJob";
        Q_EMIT installFailed();
        deleteLater();
        return;
    }
    const QString venvPath = TextToSpeechKokoroUtils::defaultVenvPath();
    // A previous environment can be broken or built against another python, so it is replaced.
    if (QDir venvDir(venvPath); venvDir.exists() && !venvDir.removeRecursively()) {
        qCWarning(KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG) << "Impossible to remove existing venv:" << venvPath;
        Q_EMIT installFailed();
        deleteLater();
        return;
    }

    auto process = new QProcess(this);
    connect(process, &QProcess::finished, this, [this, process, venvPath](int exitCode, QProcess::ExitStatus exitStatus) {
        process->deleteLater();
        if (exitStatus != QProcess::NormalExit || exitCode != 0) {
            qCWarning(KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG) << "Unable to create venv" << venvPath << process->readAllStandardError();
            Q_EMIT installFailed();
        } else {
            Q_EMIT installDone();
        }
        deleteLater();
    });
    connect(process, &QProcess::errorOccurred, this, [this, process](QProcess::ProcessError error) {
        // finished() is not emitted when the process could not be started at all.
        if (error == QProcess::FailedToStart) {
            qCWarning(KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG) << "Unable to start" << process->program();
            process->deleteLater();
            Q_EMIT installFailed();
            deleteLater();
        }
    });
    process->start(TextToSpeechKokoroUtils::pythonVersionPath(), {u"-m"_s, u"venv"_s, venvPath});
}

#include "moc_texttospeechkokoroinstallpythonevenvjob.cpp"
