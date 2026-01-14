/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on code from alpaka
*/
#include "ollamaonlinemanager.h"
#include "autogeneratetext_ollamaonline_debug.h"
#include "autogeneratetext_ollamaonline_generate_json_debug.h"
#include "core/textautogenerateengineaccessmanager.h"
// #include "ollamareply.h"
#include "ollamaonlinesettings.h"

#include <KLocalizedString>

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

using namespace Qt::Literals::StringLiterals;
OllamaOnlineManager::OllamaOnlineManager(OllamaOnlineSettings *settings, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateManagerBase{parent}
    , mOllamaOnlineSettings(settings)
{
}

OllamaOnlineManager::~OllamaOnlineManager() = default;

void OllamaOnlineManager::showModelInfo(const QString &modelName)
{
    /*
    QNetworkRequest req{QUrl::fromUserInput(mOllamaSettings->serverUrl().toString() + OllamaUtils::modelInfoPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/json"));

    QJsonObject data;
    data["model"_L1] = modelName;

    auto reply = new OllamaReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaReply::RequestTypes::ShowModelInfo,
        this};
    connect(reply, &OllamaReply::finished, this, [this, reply] {
        const auto readResponse = reply->readResponse();
        qDebug() << " readResponse : " << readResponse;
        Q_EMIT finished(readResponse);
        Q_EMIT showModelInfoDone(readResponse.response);
    });
    */
}
void OllamaOnlineManager::getVersion()
{
#if 0
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
#endif
}

void OllamaOnlineManager::loadModels()
{
#if 0
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
            Q_EMIT modelsLoadDone(info);
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

            QString installedName = installed.model();
            const int position = installedName.indexOf(u':');
            installedName = installedName.first(position);
            auto matchesModelName = [&](const OllamaModelAvailableInfo &availableInfo) {
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
#endif
}

TextAutoGenerateText::TextAutoGenerateReply *OllamaOnlineManager::getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
#if 0
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
    qCDebug(AUTOGENERATETEXT_OLLAMA_GENERATE_JSON_LOG) << " Json: " << data;
    auto reply = new OllamaReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaReply::RequestTypes::StreamingGenerate,
        this};
    connect(reply, &OllamaReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
    });
    return reply;
#else
    return nullptr;
#endif
}

TextAutoGenerateText::TextAutoGenerateReply *OllamaOnlineManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
#if 0
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
    qDebug() << " OllamaOnlineManager::getChatCompletion json: " << data;
    qCDebug(AUTOGENERATETEXT_OLLAMA_GENERATE_JSON_LOG) << " Json: " << data;
    auto reply = new OllamaReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaReply::RequestTypes::StreamingChat,
        this};
    connect(reply, &OllamaReply::finished, this, [this, reply]() {
        Q_EMIT finished(reply->readResponse());
    });
    return reply;
#else

    return nullptr;
#endif
}

OllamaOnlineSettings *OllamaOnlineManager::ollamaOnlineSettings() const
{
    return mOllamaOnlineSettings;
}

#include "moc_ollamaonlinemanager.cpp"
