/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextmodelsjob.h"
#include "speechtotextwhisperinstall_lib_debug.h"
#include "whisperspeechtotextutils.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>

using namespace Qt::Literals::StringLiterals;

namespace
{
// "models" only prints a table the script has built in: it does not import
// faster-whisper, so the interpreter of the system is enough as long as the
// virtualenv is not there yet.
[[nodiscard]] QString pythonListingModels()
{
    if (const QString venvPython = WhisperSpeechToTextUtils::venvPython(); !venvPython.isEmpty()) {
        return venvPython;
    }
    return WhisperSpeechToTextUtils::pythonVersionPath();
}
}

bool WhisperSpeechToTextModelsJob::ModelInfo::isValid() const
{
    return !identifier.isEmpty();
}

bool WhisperSpeechToTextModelsJob::ModelInfo::operator==(const ModelInfo &other) const
{
    return identifier == other.identifier && name == other.name && sizeMib == other.sizeMib && multilingual == other.multilingual
        && isDefault == other.isDefault;
}

WhisperSpeechToTextModelsJob::WhisperSpeechToTextModelsJob(QObject *parent)
    : QObject{parent}
{
}

WhisperSpeechToTextModelsJob::~WhisperSpeechToTextModelsJob()
{
    // The widget which asked for the listing can be closed before the answer:
    // ending the process here is what spares a warning from QProcess, which
    // would kill it anyway.
    if (mProcess && mProcess->state() != QProcess::NotRunning) {
        // Killing it makes it report that it failed, and answering that from a
        // destructor would call a slot of an object which is being destroyed.
        disconnect(mProcess, nullptr, this, nullptr);
        mProcess->kill();
        mProcess->waitForFinished(1000);
    }
}

WhisperSpeechToTextModelsJob::ModelInfos WhisperSpeechToTextModelsJob::parseModels(const QByteArray &json)
{
    ModelInfos models;
    const QJsonArray array = QJsonDocument::fromJson(json).object().value("models"_L1).toArray();
    models.reserve(array.count());
    for (const auto &value : array) {
        const QJsonObject obj = value.toObject();
        ModelInfo info;
        info.identifier = obj.value("id"_L1).toString();
        if (!info.isValid()) {
            // A model nothing can be loaded with is not one to offer.
            continue;
        }
        // The script names them after their identifier, but it is free not to.
        info.name = obj.value("name"_L1).toString();
        if (info.name.isEmpty()) {
            info.name = info.identifier;
        }
        info.sizeMib = obj.value("sizeMib"_L1).toInt();
        info.multilingual = obj.value("multilingual"_L1).toBool();
        info.isDefault = obj.value("default"_L1).toBool();
        models.append(std::move(info));
    }
    return models;
}

QString WhisperSpeechToTextModelsJob::defaultModel(const ModelInfos &models)
{
    for (const ModelInfo &info : models) {
        if (info.isDefault) {
            return info.identifier;
        }
    }
    return {};
}

bool WhisperSpeechToTextModelsJob::canStart() const
{
    return !WhisperSpeechToTextUtils::pythonScriptPath().isEmpty() && !pythonListingModels().isEmpty();
}

void WhisperSpeechToTextModelsJob::start()
{
    if (!canStart()) {
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Impossible to start WhisperSpeechToTextModelsJob";
        Q_EMIT modelsFailed();
        deleteLater();
        return;
    }
    auto process = new QProcess(this);
    mProcess = process;
    connect(process, &QProcess::finished, this, [this, process](int exitCode, QProcess::ExitStatus exitStatus) {
        process->deleteLater();
        const ModelInfos models = parseModels(process->readAllStandardOutput());
        if (exitStatus != QProcess::NormalExit || exitCode != 0 || models.isEmpty()) {
            qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "whisper models listing failed. Exit code:" << exitCode << process->readAllStandardError();
            Q_EMIT modelsFailed();
        } else {
            Q_EMIT modelsLoaded(models);
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
        Q_EMIT modelsFailed();
        deleteLater();
    });
    process->start(pythonListingModels(), {WhisperSpeechToTextUtils::pythonScriptPath(), u"models"_s});
}

WhisperSpeechToTextModelsJob::ModelInfos WhisperSpeechToTextModelsJob::modelsSynchronously(int timeoutMs)
{
    const QString scriptPath = WhisperSpeechToTextUtils::pythonScriptPath();
    const QString python = pythonListingModels();
    if (scriptPath.isEmpty() || python.isEmpty()) {
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "Unable to find" << WhisperSpeechToTextUtils::pythonScript();
        return {};
    }
    QProcess process;
    process.start(python, {scriptPath, u"models"_s});
    if (!process.waitForFinished(timeoutMs)) {
        qCWarning(SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG) << "whisper models listing did not answer:" << process.errorString();
        return {};
    }
    return parseModels(process.readAllStandardOutput());
}

QDebug operator<<(QDebug d, const WhisperSpeechToTextModelsJob::ModelInfo &t)
{
    d.space() << "identifier" << t.identifier;
    d.space() << "name" << t.name;
    d.space() << "sizeMib" << t.sizeMib;
    d.space() << "multilingual" << t.multilingual;
    d.space() << "isDefault" << t.isDefault;
    return d;
}

#include "moc_whisperspeechtotextmodelsjob.cpp"
