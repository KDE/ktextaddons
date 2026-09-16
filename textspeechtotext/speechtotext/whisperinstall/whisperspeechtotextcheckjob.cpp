/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextcheckjob.h"
#include "speechtotextwhisperinstall_lib_debug.h"
#include "whisperspeechtotextutils.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>

using namespace Qt::Literals::StringLiterals;

bool WhisperSpeechToTextCheckJob::CheckResult::isValid() const
{
    return !needToReinstall && missing.isEmpty();
}

QString WhisperSpeechToTextCheckJob::CheckResult::errorString() const
{
    if (needToReinstall) {
        return i18n("Whisper is not usable. Please reinstall it.");
    }
    if (!missing.isEmpty()) {
        return i18n("Whisper is not installed. Missing: %1", missing.join(", "_L1));
    }
    return {};
}

WhisperSpeechToTextCheckJob::WhisperSpeechToTextCheckJob(QObject *parent)
    : QObject{parent}
{
}

WhisperSpeechToTextCheckJob::~WhisperSpeechToTextCheckJob() = default;

// "check" exits with 1 when whisper is not usable, which is not an error here:
// only the json printed on stdout matters, stderr carries the logs of the script.
WhisperSpeechToTextCheckJob::CheckResult WhisperSpeechToTextCheckJob::parseCheckResult(const QByteArray &json)
{
    CheckResult result;
    const QJsonObject obj = QJsonDocument::fromJson(json).object();
    if (obj.isEmpty()) {
        // An empty or unreadable answer says nothing about what to install.
        result.needToReinstall = true;
        return result;
    }
    result.pythonExecutable = obj.value("python"_L1).toString();
    result.sampleRate = obj.value("sampleRate"_L1).toInt();
    result.channels = obj.value("channels"_L1).toInt();
    if (obj.value("available"_L1).toBool()) {
        return result;
    }
    const QJsonArray array = obj.value("missing"_L1).toArray();
    for (const auto &value : array) {
        const QString module = value.toString();
        if (!module.isEmpty()) {
            result.missing.append(module);
        }
    }
    // Not available but nothing named: the script is there but broken.
    result.needToReinstall = result.missing.isEmpty();
    return result;
}

bool WhisperSpeechToTextCheckJob::canStart() const
{
    return !WhisperSpeechToTextUtils::pythonScriptPath().isEmpty();
}

void WhisperSpeechToTextCheckJob::start()
{
    if (!canStart()) {
        Q_EMIT needToReinstall();
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Impossible to start WhisperSpeechToTextCheckJob";
        deleteLater();
        return;
    }
    const QString python = WhisperSpeechToTextUtils::venvPython();
    // Without the virtualenv there is nothing to check: the modules live in it.
    if (python.isEmpty()) {
        Q_EMIT needToInstallPackages(WhisperSpeechToTextUtils::requiredModules());
        deleteLater();
        return;
    }
    auto process = new QProcess(this);
    connect(process, &QProcess::finished, this, [this, process](int, QProcess::ExitStatus) {
        process->deleteLater();
        const CheckResult result = parseCheckResult(process->readAllStandardOutput());
        if (result.isValid()) {
            Q_EMIT packagesInstalled(result);
        } else if (result.needToReinstall) {
            Q_EMIT needToReinstall();
        } else {
            Q_EMIT needToInstallPackages(result.missing);
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
        Q_EMIT needToReinstall();
        deleteLater();
    });
    process->start(python, {WhisperSpeechToTextUtils::pythonScriptPath(), u"check"_s});
}

WhisperSpeechToTextCheckJob::CheckResult WhisperSpeechToTextCheckJob::checkSynchronously(int timeoutMs)
{
    CheckResult result;
    const QString scriptPath = WhisperSpeechToTextUtils::pythonScriptPath();
    if (scriptPath.isEmpty()) {
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Unable to find" << WhisperSpeechToTextUtils::pythonScript();
        result.needToReinstall = true;
        return result;
    }
    const QString python = WhisperSpeechToTextUtils::venvPython();
    // Without the virtualenv there is nothing to check: the modules live in it.
    if (python.isEmpty()) {
        result.missing = WhisperSpeechToTextUtils::requiredModules();
        return result;
    }
    QProcess process;
    process.start(python, {scriptPath, u"check"_s});
    if (!process.waitForFinished(timeoutMs)) {
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "whisper check did not answer:" << process.errorString();
        result.needToReinstall = true;
        return result;
    }
    return parseCheckResult(process.readAllStandardOutput());
}

#include "moc_whisperspeechtotextcheckjob.cpp"
