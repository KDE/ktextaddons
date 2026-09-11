/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokorocheckjob.h"
#include "texttospeech_kokoroinstall_lib_debug.h"
#include "texttospeechkokoroutils.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;

namespace
{
// "check" exits with 1 when kokoro is not usable, which is not an error here:
// only the json printed on stdout matters, stderr carries the logs of the script.
[[nodiscard]] TextToSpeechKokoroCheckJob::CheckResult parseCheckResult(const QByteArray &json)
{
    TextToSpeechKokoroCheckJob::CheckResult result;
    const QJsonObject obj = QJsonDocument::fromJson(json).object();
    if (obj.value("available"_L1).toBool()) {
        return result;
    }
    const QJsonArray array = obj.value("missing"_L1).toArray();
    for (const auto &value : array) {
        result.missing.append(value.toString());
    }
    if (obj.value("espeakNg"_L1).toString().isEmpty()) {
        result.missing.append(u"espeak-ng"_s);
    }
    // An empty or unreadable answer says nothing about what to install.
    result.needToReinstall = result.missing.isEmpty();
    return result;
}
}

bool TextToSpeechKokoroCheckJob::CheckResult::isValid() const
{
    return !needToReinstall && missing.isEmpty();
}

QString TextToSpeechKokoroCheckJob::CheckResult::errorString() const
{
    if (needToReinstall) {
        return i18n("Kokoro is not usable. Please reinstall it.");
    }
    if (!missing.isEmpty()) {
        return i18n("Kokoro is not installed. Missing: %1", missing.join(", "_L1));
    }
    return {};
}

TextToSpeechKokoroCheckJob::TextToSpeechKokoroCheckJob(QObject *parent)
    : QObject{parent}
{
}

TextToSpeechKokoroCheckJob::~TextToSpeechKokoroCheckJob() = default;

bool TextToSpeechKokoroCheckJob::canStart() const
{
    return !TextEditTextToSpeech::TextToSpeechKokoroUtils::pythonScriptPath().isEmpty();
}

void TextToSpeechKokoroCheckJob::start()
{
    if (!canStart()) {
        Q_EMIT needToReinstall();
        qCWarning(KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG) << "Impossible to start TextToSpeechKokoroCheckJob";
        deleteLater();
        return;
    }
    auto process = new QProcess(this);
    connect(process, &QProcess::finished, this, [this, process](int, QProcess::ExitStatus) {
        process->deleteLater();
        const CheckResult result = parseCheckResult(process->readAllStandardOutput());
        if (result.isValid()) {
            Q_EMIT packagesInstalled();
        } else if (result.needToReinstall) {
            Q_EMIT needToReinstall();
        } else {
            Q_EMIT needToInstallPackages(result.missing);
        }
        deleteLater();
    });
    const QString pythonScript = TextToSpeechKokoroUtils::venvPython();
    // Without the venv there is nothing to check: the packages live in it.
    if (pythonScript.isEmpty()) {
        Q_EMIT needToInstallPackages({u"kokoro"_s, u"torch"_s});
        deleteLater();
        return;
    }
    process->start(pythonScript, {TextToSpeechKokoroUtils::pythonScriptPath(), u"check"_s});
}

TextToSpeechKokoroCheckJob::CheckResult TextToSpeechKokoroCheckJob::checkSynchronously(int timeoutMs)
{
    CheckResult result;
    const QString scriptPath = TextToSpeechKokoroUtils::pythonScriptPath();
    if (scriptPath.isEmpty()) {
        qCWarning(KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG) << "Unable to find" << TextToSpeechKokoroUtils::pythonScript();
        result.needToReinstall = true;
        return result;
    }
    const QString pythonScript = TextToSpeechKokoroUtils::venvPython();
    // Without the venv there is nothing to check: the packages live in it.
    if (pythonScript.isEmpty()) {
        result.missing = {u"kokoro"_s, u"torch"_s};
        return result;
    }
    QProcess process;
    process.start(pythonScript, {scriptPath, u"check"_s});
    if (!process.waitForFinished(timeoutMs)) {
        qCWarning(KOKORO_INSTALL_TEXT_TO_SPEECH_LIB_LOG) << "kokoro check did not answer:" << process.errorString();
        result.needToReinstall = true;
        return result;
    }
    return parseCheckResult(process.readAllStandardOutput());
}

#include "moc_texttospeechkokorocheckjob.cpp"
