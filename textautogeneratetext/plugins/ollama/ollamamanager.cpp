/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on code from alpaka
*/
#include "ollamamanager.h"
#include "autogeneratetext_ollama_debug.h"
#include "autogeneratetext_ollama_generate_json_debug.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "ollamacommonmodelavailableinfosmanager.h"
#include "ollamacommonreply.h"
#include "ollamacommonutils.h"
#include "ollamasettings.h"
#include "ollamastartprocessjob.h"
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginManager>

#include <KLocalizedString>

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

using namespace Qt::Literals::StringLiterals;
OllamaManager::OllamaManager(OllamaSettings *settings, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateManagerBase{parent}
    , mOllamaSettings(settings)
{
    OllamaCommonModelAvailableInfosManager managerModelInfosManager;
    if (managerModelInfosManager.loadAvailableModels()) {
        mAvailableInfos = managerModelInfosManager.modelInfos();
    }
}

OllamaManager::~OllamaManager() = default;

void OllamaManager::deleteModel(const QString &modelName)
{
    QUrl url = mOllamaSettings->serverUrl();
    url.setPath(OllamaCommonUtils::deletePath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    QJsonObject data;
    data["model"_L1] = modelName;
    auto reply = new OllamaCommonReply{TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->sendCustomRequest(
                                           req,
                                           "DELETE",
                                           QJsonDocument(data).toJson(QJsonDocument::Compact)),
                                       OllamaCommonReply::RequestTypes::DeleteModel,
                                       this};
    connect(reply, &OllamaCommonReply::finished, this, [this] {
        // TODO verify it.
        // if (reply->error() == QNetworkReply::NoError) {
        Q_EMIT refreshInstalledModels();
        //}
    });
}

void OllamaManager::showModelInfo(const QString &modelName)
{
    QUrl url = mOllamaSettings->serverUrl();
    url.setPath(OllamaCommonUtils::modelInfoPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

    QJsonObject data;
    data["model"_L1] = modelName;

    auto reply = new OllamaCommonReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaCommonReply::RequestTypes::ShowModelInfo,
        this};
    connect(reply, &OllamaCommonReply::finished, this, [this, reply] {
        const auto readResponse = reply->readResponse();
        qDebug() << " readResponse : " << readResponse;
        Q_EMIT finished(readResponse);
        Q_EMIT showModelInfoDone(readResponse.response);
    });
}

void OllamaManager::createModel(const CreateModelInfo &info)
{
    if (!info.isValid()) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Invalid info";
        return;
    }

    QUrl url = mOllamaSettings->serverUrl();
    url.setPath(OllamaCommonUtils::createPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    QJsonObject data;
    data["model"_L1] = info.modelName;
    data["from"_L1] = info.fromModelName;
    if (!info.systemPrompt.isEmpty()) {
        data["system"_L1] = info.systemPrompt;
    }

    auto reply = new OllamaCommonReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaCommonReply::RequestTypes::CreateModel,
        this};
    connect(reply, &OllamaCommonReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
        Q_EMIT refreshInstalledModels();
    });
    /*
    connect(reply, &OllamaCommonReply::downloadInProgress, this, [this, modelName](const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info) {
        Q_EMIT downloadInProgress(modelName, info);
    });
    */
}

QList<OllamaModelInstalledInfo> OllamaManager::installedInfos() const
{
    return mInstalledInfos;
}

void OllamaManager::setInstalledInfos(const QList<OllamaModelInstalledInfo> &newInstalledInfos)
{
    mInstalledInfos = newInstalledInfos;
}

OllamaCommonReply *OllamaManager::downloadModel(const QString &modelName)
{
    QUrl url = mOllamaSettings->serverUrl();
    url.setPath(OllamaCommonUtils::pullPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    QJsonObject data;
    data["model"_L1] = modelName;

    auto reply = new OllamaCommonReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaCommonReply::RequestTypes::DownloadModel,
        this};
    connect(reply, &OllamaCommonReply::finished, this, [this, reply, modelName] {
        Q_EMIT finished(reply->readResponse());
        Q_EMIT downloadDone(modelName);
        Q_EMIT refreshInstalledModels();
    });
    connect(reply, &OllamaCommonReply::canceled, this, [this, modelName] {
        Q_EMIT canceled(modelName);
    });

    connect(reply, &OllamaCommonReply::downloadInProgress, this, [this, modelName](const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info) {
        Q_EMIT downloadInProgress(modelName, info);
    });
    connect(reply, &OllamaCommonReply::downloadError, this, [this, modelName](const QString &errorStr) {
        Q_EMIT downloadError(modelName, errorStr);
    });
    return reply;
}

void OllamaManager::getVersion()
{
    QUrl url = mOllamaSettings->serverUrl();
    url.setPath(OllamaCommonUtils::versionPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    mCheckConnect = connect(rep, &QNetworkReply::finished, this, [rep] {
        if (rep->error() != QNetworkReply::NoError) {
            /*
            ModelsInfo info;
            info.errorOccured = i18n("Failed to connect to interface at %1: %2", OllamaSettings::serverUrl().toString(), rep->errorString());
            info.hasError = true;
            Q_EMIT modelsLoadDone(std::move(info));
            */
            return;
        }

        const auto json = QJsonDocument::fromJson(rep->readAll());
        qDebug() << "json " << json;
        // TODO implement it.
        /*
        ModelsInfo info;
        const auto models = json["models"_L1].toArray();
        for (const QJsonValue &model : models) {
            info.models.push_back(model["name"_L1].toString());
        }
        info.isReady = !info.models.isEmpty();
        info.hasError = false;
        Q_EMIT modelsLoadDone(std::move(info));
        */
    });
}

void OllamaManager::loadModels()
{
    if (mCheckConnect) {
        disconnect(mCheckConnect);
    }
    mInstalledInfos.clear();
    QUrl url = mOllamaSettings->serverUrl();
    url.setPath(OllamaCommonUtils::tagsPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);

    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    mCheckConnect = connect(rep, &QNetworkReply::finished, this, [this, rep] {
        if (rep->error() != QNetworkReply::NoError) {
            ModelsInfo info;
            info.errorOccured = i18n("Failed to connect to interface at %1: %2", mOllamaSettings->serverUrl().toString(), rep->errorString());
            info.hasError = true;
            Q_EMIT modelsLoadDone(info);
            return;
        }
        ModelsInfo info;
        const auto json = QJsonDocument::fromJson(rep->readAll());
        const auto models = json["models"_L1].toArray();
        for (const auto &model : models) {
            OllamaModelInstalledInfo installed;
            installed.parseInfo(model.toObject());
            TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier i;
            i.modelName = installed.generateModelName();
            i.identifier = installed.name();

            QString installedName = installed.model();
            const int position = installedName.indexOf(u':');
            installedName = installedName.first(position);
            auto matchesModelName = [installedName](const OllamaCommonModelAvailableInfo &availableInfo) {
                return availableInfo.name() == installedName;
            };
            auto it = std::find_if(mAvailableInfos.constBegin(), mAvailableInfos.constEnd(), matchesModelName);
            if (it != mAvailableInfos.constEnd()) {
                installed.setCategories((*it).categories());
                installed.setLanguages((*it).languages());
                installed.setModelUrl((*it).url());
            }
            info.models.push_back(std::move(i));
            mInstalledInfos.append(std::move(installed));
        }

        // sort list of models
        std::sort(mInstalledInfos.begin(), mInstalledInfos.end(), [](const OllamaModelInstalledInfo &left, const OllamaModelInstalledInfo &right) {
            return left.generateModelName().toLower() < right.generateModelName().toLower();
        });

        std::sort(info.models.begin(),
                  info.models.end(),
                  [](const TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier &left,
                     const TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier &right) {
                      return left.modelName.toLower() < right.modelName.toLower();
                  });

        info.isReady = !info.models.isEmpty();
        info.hasError = false;
        Q_EMIT modelsLoadDone(info);
    });
}

TextAutoGenerateText::TextAutoGenerateReply *OllamaManager::getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QUrl url = mOllamaSettings->serverUrl();
    url.setPath(OllamaCommonUtils::completionPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    QJsonObject data;
    // data["model"_L1] = request.model().isEmpty() ? m_models.constFirst() : request.model();
    data["prompt"_L1] = request.message();
    data["model"_L1] = request.model();
    // TODO add prompt here too
#if 0
    if (!mOllamaSettings->systemPrompt().isEmpty()) {
        data["system"_L1] = mOllamaSettings->systemPrompt();
    }
#endif
    qCDebug(AUTOGENERATETEXT_OLLAMA_GENERATE_JSON_LOG) << " Json: " << data;
    auto reply = new OllamaCommonReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaCommonReply::RequestTypes::StreamingGenerate,
        this};
    connect(reply, &OllamaCommonReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
    });
    connect(reply, &OllamaCommonReply::errorOccurred, this, [this](QNetworkReply::NetworkError e) {
        Q_EMIT errorOccurred(e);
    });
    return reply;
}

TextAutoGenerateText::TextAutoGenerateReply *OllamaManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QUrl url = mOllamaSettings->serverUrl();
    url.setPath(OllamaCommonUtils::chatPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    QJsonObject data;
    data["model"_L1] = request.model();
    data["messages"_L1] = request.messages();
    data["temperature"_L1] = mOllamaSettings->temperature();
    if (!request.tools().isEmpty()) {
        data["tools"_L1] = TextAutoGenerateText::TextAutoGenerateTextToolPluginManager::self()->generateToolsArray(request.tools());
    }
    if (mOllamaSettings->seed() != 0) {
        data["seed"_L1] = mOllamaSettings->seed();
    }
    switch (mOllamaSettings->keepAliveType()) {
    case OllamaSettings::KeepAliveType::KeepAliveForever:
        data["keep_alive"_L1] = -1;
        break;
    case OllamaSettings::KeepAliveType::SetTimer:
        data["keep_alive"_L1] = mOllamaSettings->keepAliveMinutes() * 60;
        break;
    case OllamaSettings::KeepAliveType::UnloadAfterUse:
        data["keep_alive"_L1] = 1;
        break;
    case OllamaSettings::KeepAliveType::Unknown:
        break;
    }
    data["num_ctx"_L1] = mOllamaSettings->contextWindowSize();

    data["think"_L1] = request.thinking();

    qDebug() << " OllamaManager::getChatCompletion json: " << data;
    qCDebug(AUTOGENERATETEXT_OLLAMA_GENERATE_JSON_LOG) << " Json: " << data;
    auto reply = new OllamaCommonReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaCommonReply::RequestTypes::StreamingChat,
        this};
    connect(reply, &OllamaCommonReply::finished, this, [this, reply]() {
        Q_EMIT finished(reply->readResponse());
    });
    connect(reply, &OllamaCommonReply::errorOccurred, this, [this](QNetworkReply::NetworkError e) {
        Q_EMIT errorOccurred(e);
    });
    return reply;
}

bool OllamaManager::isAlreadyInstalled(const QString &modelName) const
{
    if (modelName.isEmpty()) {
        return {};
    }
    auto matchesModelName = [&](const OllamaModelInstalledInfo &info) {
        return info.model() == modelName;
    };
    auto it = std::find_if(mInstalledInfos.constBegin(), mInstalledInfos.constEnd(), matchesModelName);
    if (it == mInstalledInfos.constEnd()) {
        return false;
    }
    return true;
}

OllamaSettings *OllamaManager::ollamaSettings() const
{
    return mOllamaSettings;
}

QList<OllamaCommonModelAvailableInfo> OllamaManager::availableInfos() const
{
    return mAvailableInfos;
}

void OllamaManager::setAvailableInfos(const QList<OllamaCommonModelAvailableInfo> &newAvailableInfos)
{
    mAvailableInfos = newAvailableInfos;
}

QDebug operator<<(QDebug d, const OllamaManager::CreateModelInfo &t)
{
    d.space() << "modelName:" << t.modelName;
    d.space() << "fromModelName:" << t.fromModelName;
    d.space() << "systemPrompt:" << t.systemPrompt;
    return d;
}

bool OllamaManager::CreateModelInfo::isValid() const
{
    return !modelName.isEmpty();
}

bool OllamaManager::hasVisionSupport(const QString &modelName) const
{
    return hasCategorySupport(modelName, TextAutoGenerateText::TextAutoGenerateManager::Category::Vision);
}

bool OllamaManager::hasToolsSupport(const QString &modelName) const
{
    return hasCategorySupport(modelName, TextAutoGenerateText::TextAutoGenerateManager::Category::Tools);
}

bool OllamaManager::hasOcrSupport([[maybe_unused]] const QString &modelName) const
{
    return false;
}

bool OllamaManager::hasAudioSupport([[maybe_unused]] const QString &modelName) const
{
    return false;
}

bool OllamaManager::hasThinkSupport(const QString &modelName) const
{
    return hasCategorySupport(modelName, TextAutoGenerateText::TextAutoGenerateManager::Category::Reasoning);
}

bool OllamaManager::hasCategorySupport(const QString &modelName, TextAutoGenerateText::TextAutoGenerateManager::Category cat) const
{
    if (modelName.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << " modelName is empty. it's a bug";
        return false;
    }
    auto matchesModelName = [&](const OllamaModelInstalledInfo &info) {
        return info.model() == modelName;
    };
    auto it = std::find_if(mInstalledInfos.constBegin(), mInstalledInfos.constEnd(), matchesModelName);
    if (it == mInstalledInfos.constEnd()) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << " modelName is not installed " << modelName;
        return false;
    }
    return it->categories() & cat;
}

void OllamaManager::startOllama()
{
    auto job = new OllamaStartProcessJob(this, this);
    connect(job, &OllamaStartProcessJob::ollamaStarted, this, [this]() {
        Q_EMIT ollamaStarted();
    });
    connect(job, &OllamaStartProcessJob::ollamaFailed, this, [this](const QString &errorStr) {
        Q_EMIT ollamaFailed(errorStr);
    });
    if (job->start()) {
        mOllamaStartProcessJob = job;
    }
}

QByteArray OllamaManager::ollamaOutputData() const
{
    if (mOllamaStartProcessJob) {
        return mOllamaStartProcessJob->processOutputData();
    }
    return {};
}

#include "moc_ollamamanager.cpp"
