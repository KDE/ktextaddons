/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lmstudiomanager.h"
#include "autogeneratetext_lmstudio_debug.h"
#include "autogeneratetext_lmstudio_generate_json_debug.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "lmstudioreply.h"
#include "lmstudiosettings.h"
#include "modelsmanager/lmstudiomodelinstalledinfo.h"

#include <KLocalizedString>

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <qnetworkrequest.h>

using namespace Qt::Literals::StringLiterals;

LMStudioManager::LMStudioManager(LMStudioSettings *settings, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateManagerBase{parent}
    , mLMStudioSettings(settings)
{
}

LMStudioManager::~LMStudioManager() = default;

bool LMStudioManager::hasVisionSupport([[maybe_unused]] const QString &modelName) const
{
    return hasCategorySupport(modelName, TextAutoGenerateText::TextAutoGenerateManager::Category::Vision);
}

bool LMStudioManager::hasToolsSupport([[maybe_unused]] const QString &modelName) const
{
    return hasCategorySupport(modelName, TextAutoGenerateText::TextAutoGenerateManager::Category::Tools);
}

bool LMStudioManager::hasOcrSupport([[maybe_unused]] const QString &modelName) const
{
    return false;
}

bool LMStudioManager::hasAudioSupport([[maybe_unused]] const QString &modelName) const
{
    return false;
}

bool LMStudioManager::hasThinkSupport([[maybe_unused]] const QString &modelName) const
{
    return hasCategorySupport(modelName, TextAutoGenerateText::TextAutoGenerateManager::Category::Reasoning);
}

LMStudioSettings *LMStudioManager::lmStudioSettings() const
{
    return mLMStudioSettings;
}

QString LMStudioManager::apiKey() const
{
    return mApiKey;
}

void LMStudioManager::setApiKey(const QString &newApiKey)
{
    mApiKey = newApiKey;
}

QList<LMStudioModelInstalledInfo> LMStudioManager::installedInfos() const
{
    return mInstalledInfos;
}

void LMStudioManager::setInstalledInfos(const QList<LMStudioModelInstalledInfo> &newInstalledInfos)
{
    mInstalledInfos = newInstalledInfos;
}

void LMStudioManager::loadModels()
{
    if (mCheckConnect) {
        disconnect(mCheckConnect);
    }
    mInstalledInfos.clear();
    QUrl url = mLMStudioSettings->serverUrl();
    url.setPath(u"/api/v1/models"_s);
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    if (!mApiKey.isEmpty()) {
        req.setRawHeader("Authorization", "Bearer " + mApiKey.toLatin1());
    }

    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    connect(rep, &QNetworkReply::finished, this, [this, rep] {
        if (rep->error() != QNetworkReply::NoError) {
            ModelsInfo info;
            info.errorOccured = i18n("Failed to connect to interface at %1: %2", mLMStudioSettings->serverUrl().toString(), rep->errorString());
            info.hasError = true;
            Q_EMIT modelsLoadDone(info);
            return;
        }

        ModelsInfo info;
        const auto json = QJsonDocument::fromJson(rep->readAll());
        const auto models = json["models"_L1].toArray();
        for (const auto &model : models) {
            LMStudioModelInstalledInfo installed;
            installed.parseInfo(model.toObject());

            TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier i;
            i.modelName = installed.name();
            i.identifier = installed.model();

            info.models.push_back(std::move(i));
            mInstalledInfos.append(std::move(installed));
        }

        // sort list of models
        std::sort(mInstalledInfos.begin(), mInstalledInfos.end(), [](const LMStudioModelInstalledInfo &left, const LMStudioModelInstalledInfo &right) {
            return left.name().toLower() < right.name().toLower();
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

TextAutoGenerateText::TextAutoGenerateReply *LMStudioManager::getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QUrl url = mLMStudioSettings->serverUrl();
    // Use OpenAI API exposed by LM Studio
    url.setPath(u"/v1/completions"_s);
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    if (!mApiKey.isEmpty()) {
        req.setRawHeader("Authorization", "Bearer " + mApiKey.toLatin1());
    }

    QJsonObject data;
    data["model"_L1] = request.model();
    data["prompt"_L1] = request.message();
    qCDebug(AUTOGENERATETEXT_LMSTUDIO_GENERATE_JSON_LOG) << " Json: " << data;

    auto reply = new LMStudioReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        LMStudioReply::RequestTypes::StreamingGenerate,
        this};
    connect(reply, &TextAutoGenerateText::TextAutoGenerateReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
    });
    connect(reply, &TextAutoGenerateText::TextAutoGenerateReply::errorOccurred, this, [this](QNetworkReply::NetworkError e) {
        Q_EMIT errorOccurred(e);
    });
    return reply;
}

TextAutoGenerateText::TextAutoGenerateReply *LMStudioManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    QUrl url = mLMStudioSettings->serverUrl();
    // Use OpenAI API exposed by LM Studio
    url.setPath(u"/v1/chat/completions"_s);
    QNetworkRequest req{url};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    if (!mApiKey.isEmpty()) {
        req.setRawHeader("Authorization", "Bearer " + mApiKey.toLatin1());
    }

    QJsonObject data;
    data["model"_L1] = request.model();
    data["messages"_L1] = request.messages();
    data["stream"_L1] = true;
    qCDebug(AUTOGENERATETEXT_LMSTUDIO_GENERATE_JSON_LOG) << " Json: " << data;

    auto reply = new LMStudioReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        LMStudioReply::RequestTypes::StreamingChat,
        this};
    connect(reply, &TextAutoGenerateText::TextAutoGenerateReply::finished, this, [this, reply] {
        Q_EMIT finished(reply->readResponse());
    });
    connect(reply, &TextAutoGenerateText::TextAutoGenerateReply::errorOccurred, this, [this](QNetworkReply::NetworkError e) {
        Q_EMIT errorOccurred(e);
    });
    return reply;
}

bool LMStudioManager::hasCategorySupport(const QString &modelName, TextAutoGenerateText::TextAutoGenerateManager::Category cat) const
{
    if (modelName.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_LMSTUDIO_LOG) << " modelName is empty. it's a bug";
        return false;
    }
    auto matchesModelName = [&](const LMStudioModelInstalledInfo &info) {
        return info.model() == modelName;
    };
    auto it = std::find_if(mInstalledInfos.constBegin(), mInstalledInfos.constEnd(), matchesModelName);
    if (it == mInstalledInfos.constEnd()) {
        qCWarning(AUTOGENERATETEXT_LMSTUDIO_LOG) << " modelName is not installed " << modelName;
        return false;
    }
    return it->categories() & cat;
}

QDebug operator<<(QDebug d, const LMStudioManager &t)
{
    d.space() << "lmStudioSettings:" << t.lmStudioSettings();
    return d;
}

#include "moc_lmstudiomanager.cpp"
