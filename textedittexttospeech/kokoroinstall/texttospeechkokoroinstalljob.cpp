/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokoroinstalljob.h"
#include "texttospeech_kokoroinstall_lib_debug.h"
#include "texttospeechkokoroutils.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;

namespace
{
// espeak-ng is a system package, pip knows nothing about it.
[[nodiscard]] bool isPythonModule(const QString &module)
{
    return module != "espeak-ng"_L1;
}

// torch pulls the whole cuda stack from pypi, the cpu-only index is enough here.
[[nodiscard]] QStringList pipArguments(const QString &module)
{
    QStringList arguments{u"install"_s};
    if (module == "torch"_L1) {
        arguments << u"--index-url"_s << u"https://download.pytorch.org/whl/cpu"_s;
    }
    arguments << module;
    return arguments;
}
}

TextToSpeechKokoroInstallJob::TextToSpeechKokoroInstallJob(QObject *parent)
    : QObject{parent}
{
}

TextToSpeechKokoroInstallJob::~TextToSpeechKokoroInstallJob() = default;

bool TextToSpeechKokoroInstallJob::canStart() const
{
    // Without the venv there is no pip to install the modules with.
    return !mModules.isEmpty() && !TextToSpeechKokoroUtils::venvPip().isEmpty();
}

QStringList TextToSpeechKokoroInstallJob::modules() const
{
    return mModules;
}

void TextToSpeechKokoroInstallJob::setModules(const QStringList &newModules)
{
    mModules = newModules;
}

void TextToSpeechKokoroInstallJob::start()
{
    if (!canStart()) {
        qCWarning(KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG) << "Impossible to start TextToSpeechKokoroInstallJob";
        Q_EMIT installFailed();
        deleteLater();
        return;
    }
    mRemainingModules.clear();
    for (const QString &module : std::as_const(mModules)) {
        if (!isPythonModule(module)) {
            continue;
        }
        // torch first: installing kokoro before it would pull the cuda build of torch from pypi.
        if (module == "torch"_L1) {
            mRemainingModules.prepend(module);
        } else {
            mRemainingModules.append(module);
        }
    }

    mProcess = new QProcess(this);
    // pip reports its progress on stdout, its warnings on stderr.
    mProcess->setProcessChannelMode(QProcess::MergedChannels);
    connect(mProcess, &QProcess::readyReadStandardOutput, this, [this]() {
        Q_EMIT installMessage(QString::fromUtf8(mProcess->readAllStandardOutput()));
    });
    connect(mProcess, &QProcess::finished, this, &TextToSpeechKokoroInstallJob::slotFinished);
    connect(mProcess, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error) {
        // finished() is not emitted when the process could not be started at all.
        if (error == QProcess::FailedToStart) {
            failed(u"Unable to start "_s + mProcess->program());
        }
    });
    installNextModule();
}

void TextToSpeechKokoroInstallJob::installNextModule()
{
    if (mRemainingModules.isEmpty()) {
        Q_EMIT installDone();
        deleteLater();
        return;
    }
    const QString module = mRemainingModules.takeFirst();
    mProcess->start(TextToSpeechKokoroUtils::venvPip(), pipArguments(module));
}

void TextToSpeechKokoroInstallJob::slotFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus != QProcess::NormalExit || exitCode != 0) {
        failed(u"Unable to install module. Exit code: "_s + QString::number(exitCode));
        return;
    }
    installNextModule();
}

void TextToSpeechKokoroInstallJob::failed(const QString &errorMessage)
{
    qCWarning(KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG) << errorMessage;
    Q_EMIT installMessage(errorMessage);
    Q_EMIT installFailed();
    deleteLater();
}

#include "moc_texttospeechkokoroinstalljob.cpp"
