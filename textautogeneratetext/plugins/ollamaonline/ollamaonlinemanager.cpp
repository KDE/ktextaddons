/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on code from alpaka
*/
#include "ollamaonlinemanager.h"
#include "autogeneratetext_ollamaonline_debug.h"
#include "autogeneratetext_ollamaonline_generate_json_debug.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "ollamacommonreply.h"
#include "ollamacommonutils.h"
#include "ollamaonlinesettings.h"

#include <KLocalizedString>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginManager>

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

using namespace Qt::Literals::StringLiterals;
OllamaOnlineManager::OllamaOnlineManager(OllamaOnlineSettings *settings, QObject *parent)
    : OllamaCommonManager{parent}
    , mOllamaOnlineSettings(settings)
{
}

OllamaOnlineManager::~OllamaOnlineManager() = default;

QUrl OllamaOnlineManager::instanceUrl()
{
    return mOllamaOnlineSettings->serverUrl();
}

void OllamaOnlineManager::getVersion()
{
    QUrl url = mOllamaOnlineSettings->serverUrl();
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

void OllamaOnlineManager::loadModels()
{
    if (mCheckConnect) {
        disconnect(mCheckConnect);
    }
    QUrl url = mOllamaOnlineSettings->serverUrl();
    url.setPath(OllamaCommonUtils::tagsPath());
    QNetworkRequest req{url};

    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    if (mApiKey.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMAONLINE_LOG) << "Api key is missing";
    } else {
        req.setRawHeader("Authorization", "Bearer " + mApiKey.toLatin1());
    }

    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    mCheckConnect = connect(rep, &QNetworkReply::finished, this, [this, rep] {
        if (rep->error() != QNetworkReply::NoError) {
            ModelsInfo info;
            info.errorOccured = i18n("Failed to connect to interface at %1: %2", mOllamaOnlineSettings->serverUrl().toString(), rep->errorString());
            info.hasError = true;
            Q_EMIT modelsLoadDone(info);
            return;
        }
        ModelsInfo info;
        const auto json = QJsonDocument::fromJson(rep->readAll());
        // qDebug() << " json " << json;
        const auto models = json["models"_L1].toArray();
        for (const QJsonValue &model : models) {
            TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier i;
            i.modelName = model["name"_L1].toString();
            i.identifier = model["model"_L1].toString();
            info.models.push_back(std::move(i));
        }
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

TextAutoGenerateText::TextAutoGenerateReply *OllamaOnlineManager::getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QUrl url = mOllamaOnlineSettings->serverUrl();
    url.setPath(OllamaCommonUtils::completionPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    if (mApiKey.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMAONLINE_LOG) << "Api key is missing";
    } else {
        req.setRawHeader("Authorization", "Bearer " + mApiKey.toLatin1());
    }

    QJsonObject data;
    data["prompt"_L1] = request.message();
    data["model"_L1] = request.model();
    qCDebug(AUTOGENERATETEXT_OLLAMAONLINE_GENERATE_JSON_LOG) << " Json: " << data;
    auto reply = new OllamaCommonReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaCommonReply::RequestTypes::StreamingGenerate,
        this};
    connect(reply, &OllamaCommonReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
    });
    return reply;
}

TextAutoGenerateText::TextAutoGenerateReply *OllamaOnlineManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QUrl url = mOllamaOnlineSettings->serverUrl();
    url.setPath(OllamaCommonUtils::chatPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    if (mApiKey.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMAONLINE_LOG) << "Api key is missing";
    } else {
        req.setRawHeader("Authorization", "Bearer " + mApiKey.toLatin1());
    }

    QJsonObject data;
    data["model"_L1] = request.model();
    data["messages"_L1] = request.messages();

    data["temperature"_L1] = mOllamaOnlineSettings->temperature();
    if (!request.tools().isEmpty()) {
        data["tools"_L1] = TextAutoGenerateText::TextAutoGenerateTextToolPluginManager::self()->generateToolsArray(request.tools());
    }
    if (mOllamaOnlineSettings->seed() != 0) {
        data["seed"_L1] = mOllamaOnlineSettings->seed();
    }
    switch (mOllamaOnlineSettings->keepAliveType()) {
    case OllamaCommonSettings::KeepAliveType::KeepAliveForever:
        data["keep_alive"_L1] = -1;
        break;
    case OllamaCommonSettings::KeepAliveType::SetTimer:
        data["keep_alive"_L1] = mOllamaOnlineSettings->keepAliveMinutes() * 60;
        break;
    case OllamaCommonSettings::KeepAliveType::UnloadAfterUse:
        data["keep_alive"_L1] = 1;
        break;
    case OllamaCommonSettings::KeepAliveType::Unknown:
        break;
    }
    data["num_ctx"_L1] = mOllamaOnlineSettings->contextWindowSize();

    data["think"_L1] = request.thinking();

    qDebug() << " OllamaOnlineManager::getChatCompletion json: " << data;
    qCDebug(AUTOGENERATETEXT_OLLAMAONLINE_GENERATE_JSON_LOG) << " Json: " << data;
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

OllamaOnlineSettings *OllamaOnlineManager::ollamaOnlineSettings() const
{
    return mOllamaOnlineSettings;
}

QString OllamaOnlineManager::apiKey() const
{
    return mApiKey;
}

void OllamaOnlineManager::setApiKey(const QString &newApiKey)
{
    mApiKey = newApiKey;
}

QList<OllamaCommonModelAvailableInfo> OllamaOnlineManager::availableInfos() const
{
    return mAvailableInfos;
}

void OllamaOnlineManager::setAvailableInfos(const QList<OllamaCommonModelAvailableInfo> &newAvailableInfos)
{
    mAvailableInfos = newAvailableInfos;
}

#include "moc_ollamaonlinemanager.cpp"
