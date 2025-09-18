/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on code from alpaka
*/
#include "ollamamanager.h"
#include "autogeneratetext_ollama_debug.h"
#include "autogeneratetext_ollama_generate_json_debug.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "ollamareply.h"
#include "ollamasettings.h"
#include "ollamautils.h"
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginManager>

#include <KLocalizedString>

#include <QBuffer>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

using namespace Qt::Literals::StringLiterals;
OllamaManager::OllamaManager(OllamaSettings *settings, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateManagerBase{parent}
    , mOllamaSettings(settings)
{
}

OllamaManager::~OllamaManager() = default;

void OllamaManager::deleteModel(const QString &modelName)
{
    QNetworkRequest req{QUrl::fromUserInput(mOllamaSettings->serverUrl().toString() + OllamaUtils::deletePath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    QJsonObject data;
    data["model"_L1] = modelName;
    auto reply = new OllamaReply{TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->sendCustomRequest(
                                     req,
                                     "DELETE",
                                     QJsonDocument(data).toJson(QJsonDocument::Compact)),
                                 OllamaReply::RequestTypes::DeleteModel,
                                 this};
    connect(reply, &OllamaReply::finished, this, [this] {
        // TODO verify it.
        // if (reply->error() == QNetworkReply::NoError) {
        Q_EMIT refreshInstalledModels();
        //}
    });
}

void OllamaManager::showModelInfo(const QString &modelName)
{
    // TODO
}

void OllamaManager::createModel(const CreateModelInfo &info)
{
    if (!info.isValid()) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Invalid info";
        return;
    }
    QNetworkRequest req{QUrl::fromUserInput(mOllamaSettings->serverUrl().toString() + OllamaUtils::createPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    QJsonObject data;
    data["model"_L1] = info.modelName;
    data["from"_L1] = info.fromModelName;
    if (!info.systemPrompt.isEmpty()) {
        data["system"_L1] = info.systemPrompt;
    }

    auto reply = new OllamaReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaReply::RequestTypes::CreateModel,
        this};
    connect(reply, &OllamaReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
        Q_EMIT refreshInstalledModels();
    });
    /*
    connect(reply, &OllamaReply::downloadInProgress, this, [this, modelName](const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info) {
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

OllamaReply *OllamaManager::downloadModel(const QString &modelName)
{
    QNetworkRequest req{QUrl::fromUserInput(mOllamaSettings->serverUrl().toString() + OllamaUtils::pullPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    QJsonObject data;
    data["model"_L1] = modelName;

    auto reply = new OllamaReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaReply::RequestTypes::DownloadModel,
        this};
    connect(reply, &OllamaReply::finished, this, [this, reply, modelName] {
        Q_EMIT finished(reply->readResponse());
        Q_EMIT downloadDone(modelName);
        Q_EMIT refreshInstalledModels();
    });
    connect(reply, &OllamaReply::downloadInProgress, this, [this, modelName](const TextAutoGenerateText::TextAutoGenerateReply::DownloadModelInfo &info) {
        Q_EMIT downloadInProgress(modelName, info);
    });
    return reply;
}

void OllamaManager::getVersion()
{
    QNetworkRequest req{QUrl::fromUserInput(mOllamaSettings->serverUrl().toString() + OllamaUtils::versionPath())};
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
    QNetworkRequest req{QUrl::fromUserInput(mOllamaSettings->serverUrl().toString() + OllamaUtils::tagsPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);

    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    mCheckConnect = connect(rep, &QNetworkReply::finished, this, [this, rep] {
        if (rep->error() != QNetworkReply::NoError) {
            ModelsInfo info;
            info.errorOccured = i18n("Failed to connect to interface at %1: %2", mOllamaSettings->serverUrl().toString(), rep->errorString());
            info.hasError = true;
            Q_EMIT modelsLoadDone(std::move(info));
            return;
        }

        ModelsInfo info;
        const auto json = QJsonDocument::fromJson(rep->readAll());
        const auto models = json["models"_L1].toArray();
        for (const QJsonValue &model : models) {
            OllamaModelInstalledInfo installed;
            installed.parseInfo(model.toObject());
            TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier i;
            i.modelName = installed.generateModelName();
            i.identifier = installed.name();
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
        Q_EMIT modelsLoadDone(std::move(info));
    });
}

TextAutoGenerateText::TextAutoGenerateReply *OllamaManager::getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QNetworkRequest req{QUrl::fromUserInput(mOllamaSettings->serverUrl().toString() + OllamaUtils::completionPath())};
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
    qCDebug(AUTOGENERATETEXT_OLLAMA_GENERATE_JSON_LOG) << " JSon " << data;
    auto reply = new OllamaReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaReply::RequestTypes::StreamingGenerate,
        this};
    connect(reply, &OllamaReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
    });
    return reply;
}

TextAutoGenerateText::TextAutoGenerateReply *OllamaManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QNetworkRequest req{QUrl::fromUserInput(mOllamaSettings->serverUrl().toString() + OllamaUtils::chatPath())};
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
    qDebug() << " OllamaManager::getChatCompletion json: " << data;
    qCDebug(AUTOGENERATETEXT_OLLAMA_GENERATE_JSON_LOG) << " JSon: " << data;
    auto reply = new OllamaReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaReply::RequestTypes::StreamingChat,
        this};
    connect(reply, &OllamaReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
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

#include "moc_ollamamanager.cpp"
