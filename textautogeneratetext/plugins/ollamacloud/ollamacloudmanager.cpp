/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on code from alpaka
*/
#include "ollamacloudmanager.h"
#include "autogeneratetext_ollamacloud_debug.h"
#include "autogeneratetext_ollamacloud_generate_json_debug.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "ollamacloudsettings.h"
#include "ollamacommonreply.h"
#include "ollamacommonutils.h"

#include <KLocalizedString>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginManager>

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>

using namespace Qt::Literals::StringLiterals;
OllamaCloudManager::OllamaCloudManager(OllamaCloudSettings *settings, QObject *parent)
    : OllamaCommonManager{parent}
    , mOllamaCloudSettings(settings)
{
}

OllamaCloudManager::~OllamaCloudManager() = default;

QUrl OllamaCloudManager::instanceUrl()
{
    return QUrl(u"https://ollama.com"_s);
}

void OllamaCloudManager::loadModels()
{
    if (mCheckConnect) {
        disconnect(mCheckConnect);
    }
    QUrl url = instanceUrl();
    url.setPath(OllamaCommonUtils::tagsPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    if (mApiKey.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMACLOUD_LOG) << "Api key is missing";
    } else {
        req.setRawHeader("Authorization", "Bearer " + mApiKey.toLatin1());
    }

    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    mCheckConnect = connect(rep, &QNetworkReply::finished, this, [this, rep] {
        if (rep->error() != QNetworkReply::NoError) {
            ModelsInfo info;
            info.errorOccured = i18n("Failed to connect to interface at %1: %2", instanceUrl().toString(), rep->errorString());
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

TextAutoGenerateText::TextAutoGenerateReply *OllamaCloudManager::getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QUrl url = instanceUrl();
    url.setPath(OllamaCommonUtils::completionPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    if (mApiKey.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMACLOUD_LOG) << "Api key is missing";
    } else {
        req.setRawHeader("Authorization", "Bearer " + mApiKey.toLatin1());
    }

    QJsonObject data;
    data["prompt"_L1] = request.message();
    data["model"_L1] = request.model();
    qCDebug(AUTOGENERATETEXT_OLLAMACLOUD_GENERATE_JSON_LOG) << " Json: " << data;
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

TextAutoGenerateText::TextAutoGenerateReply *OllamaCloudManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QUrl url = instanceUrl();
    url.setPath(OllamaCommonUtils::chatPath());
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    if (mApiKey.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMACLOUD_LOG) << "Api key is missing";
    } else {
        req.setRawHeader("Authorization", "Bearer " + mApiKey.toLatin1());
    }

    QJsonObject data;
    data["model"_L1] = request.model();
    data["messages"_L1] = request.messages();

    data["temperature"_L1] = mOllamaCloudSettings->temperature();
    if (!request.tools().isEmpty()) {
        data["tools"_L1] = TextAutoGenerateText::TextAutoGenerateTextToolPluginManager::self()->generateToolsArray(request.tools());
    }
    if (mOllamaCloudSettings->seed() != 0) {
        data["seed"_L1] = mOllamaCloudSettings->seed();
    }
    addKeepAliveType(data, mOllamaCloudSettings->keepAliveType(), mOllamaCloudSettings->keepAliveMinutes());
    data["num_ctx"_L1] = mOllamaCloudSettings->contextWindowSize();
    data["think"_L1] = request.thinking();

    // qDebug() << " OllamaCloudManager::getChatCompletion json: " << data;
    qCDebug(AUTOGENERATETEXT_OLLAMACLOUD_GENERATE_JSON_LOG) << " Json: " << data;
    auto reply = new OllamaCommonReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        OllamaCommonReply::RequestTypes::StreamingChat,
        this};
    connect(reply, &OllamaCommonReply::finished, this, [this, reply]() {
        Q_EMIT finished(reply->readResponse());
    });
    return reply;
}

OllamaCloudSettings *OllamaCloudManager::ollamaCloudSettings() const
{
    return mOllamaCloudSettings;
}

QString OllamaCloudManager::apiKey() const
{
    return mApiKey;
}

void OllamaCloudManager::setApiKey(const QString &newApiKey)
{
    mApiKey = newApiKey;
}

QList<OllamaCommonModelAvailableInfo> OllamaCloudManager::availableInfos() const
{
    return mAvailableInfos;
}

void OllamaCloudManager::setAvailableInfos(const QList<OllamaCommonModelAvailableInfo> &newAvailableInfos)
{
    mAvailableInfos = newAvailableInfos;
}

bool OllamaCloudManager::hasCategorySupport(const QString &modelName, TextAutoGenerateText::TextAutoGenerateManager::Category cat) const
{
    if (modelName.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMACLOUD_GENERATE_JSON_LOG) << " modelName is empty. it's a bug";
        return false;
    }
    const auto matchesModelName = [&](const OllamaCommonModelAvailableInfo &info) {
        const static QRegularExpression reg(u":.*"_s);
        QString newModelName = modelName;
        newModelName.remove(reg);
        return info.name() == newModelName;
    };
    const auto it = std::find_if(mAvailableInfos.constBegin(), mAvailableInfos.constEnd(), matchesModelName);
    if (it == mAvailableInfos.constEnd()) {
        qCWarning(AUTOGENERATETEXT_OLLAMACLOUD_GENERATE_JSON_LOG) << " modelName is not installed " << modelName;
        return false;
    }
    return it->categories() & cat;
}

#include "moc_ollamacloudmanager.cpp"
