/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechkokorocheckjob.h"
#include "texttospeech_kokoro_lib_debug.h"
#include "texttospeechkokoroutils.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>

using namespace Qt::Literals::StringLiterals;
using namespace TextEditTextToSpeech;
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
        qCWarning(KOKORO_TEXT_TO_SPEECH_LIB_LOG) << "Impossible to start TextToSpeechKokoroCheckJob";
        deleteLater();
        return;
    }
    auto process = new QProcess(this);
    // stderr carries the logs of the script, only stdout carries the json.
    connect(process, &QProcess::finished, this, [this, process](int, QProcess::ExitStatus) {
        process->deleteLater();
        // "check" exits with 1 when kokoro is not usable, which is not an error here.
        const QJsonObject obj = QJsonDocument::fromJson(process->readAllStandardOutput()).object();
        if (obj.value("available"_L1).toBool()) {
            Q_EMIT packagesInstalled();
        } else {
            QStringList missing;
            const QJsonArray array = obj.value("missing"_L1).toArray();
            for (const auto &value : array) {
                missing.append(value.toString());
            }
            if (obj.value("espeakNg"_L1).toString().isEmpty()) {
                missing.append(u"espeak-ng"_s);
            }
            Q_EMIT needToInstallPackages(missing);
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
#include "moc_texttospeechkokorocheckjob.cpp"
