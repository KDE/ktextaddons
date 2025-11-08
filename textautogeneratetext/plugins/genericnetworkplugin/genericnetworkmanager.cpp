/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmanager.h"
#include "autogeneratetext_genericnetwork_debug.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "core/textautogeneratetextrequest.h"
#include "genericnetworkreply.h"
#include "genericnetworkserverinfo.h"
#include "genericnetworksettings.h"
#include "modelsmanager/genericnetworkmodelavailableinfos.h"
#include <KLocalizedString>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPluginManager>
using namespace Qt::Literals::StringLiterals;
GenericNetworkManager::GenericNetworkManager(GenericNetworkSettings *settings, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateManagerBase{parent}
    , mGenericNetworkSettings(settings)
    , mServerInfo(new GenericNetworkServerInfo)
{
}

GenericNetworkManager::~GenericNetworkManager()
{
    delete mServerInfo;
}

void GenericNetworkManager::loadModels()
{
    if (mCheckConnect) {
        disconnect(mCheckConnect);
    }
    QNetworkRequest req{QUrl::fromUserInput(apiUrl() + u"models"_s)};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    if (mApiKey.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "Api key is missing";
    }
    req.setRawHeader("Authorization", "Bearer " + mApiKey.toLatin1());

    auto rep = TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->get(req);
    mCheckConnect = connect(rep, &QNetworkReply::finished, this, [this, rep] {
        if (rep->error() != QNetworkReply::NoError) {
            ModelsInfo info;
            info.errorOccured = i18n("Failed to connect to interface at %1: %2", apiUrl(), rep->errorString());
            info.hasError = true;
            Q_EMIT modelsLoadDone(std::move(info));
            return;
        }

        GenericNetworkModelAvailableInfos infos;
        const auto json = QJsonDocument::fromJson(rep->readAll());
        const auto models = json["data"_L1].toArray();
        infos.parseModelsInfo(models);
        mInfos = infos.infos();
        ModelsInfo info;
        // qDebug() << " json " << json;
        for (const auto &parsedInfo : infos.infos()) {
            TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier i;
            i.identifier = parsedInfo.identifier();
            if (parsedInfo.modelName().isEmpty()) {
                i.modelName = i.identifier;
            } else {
                i.modelName = parsedInfo.modelName();
            }
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
        Q_EMIT modelsLoadDone(std::move(info));
    });
}

TextAutoGenerateText::TextAutoGenerateReply *GenericNetworkManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    if (mApiKey.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_GENERICNETWORK_LOG) << "Api key is missing";
        return nullptr;
    }
    QNetworkRequest req{QUrl::fromUserInput(apiUrl() + chatPath())};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);
    req.setRawHeader("Accept", "application/json"_ba);
    req.setRawHeader("Authorization", "Bearer " + mApiKey.toLatin1());
    QJsonObject data;
    data["model"_L1] = request.model();
    data["messages"_L1] = request.messages();
    data["temperature"_L1] = mGenericNetworkSettings->temperature();
    data["stream"_L1] = true;
    if (!request.tools().isEmpty()) {
        data["tools"_L1] = TextAutoGenerateText::TextAutoGenerateTextToolPluginManager::self()->generateToolsArray(request.tools());
        // data["tool_choice"_L1] = u"none"_s;
    }
    if (mGenericNetworkSettings->maxTokens() > 0) {
        data["max_tokens"_L1] = mGenericNetworkSettings->maxTokens();
    }
    if (mGenericNetworkSettings->seed() > 0) {
        data["seed"_L1] = mGenericNetworkSettings->seed();
    }
    qCDebug(AUTOGENERATETEXT_GENERICNETWORK_LOG) << " Json: " << data << " req " << req.url();
    auto reply = new GenericNetworkReply{
        TextAutoGenerateText::TextAutoGenerateEngineAccessManager::self()->networkManager()->post(req, QJsonDocument(data).toJson(QJsonDocument::Compact)),
        GenericNetworkReply::RequestTypes::StreamingChat,
        this};
    connect(reply, &GenericNetworkReply::finished, this, [this, reply] {
        const auto response = reply->readResponse();
        qDebug() << "response  " << response;
        Q_EMIT finished(response);
    });
    return reply;
}

TextAutoGenerateText::TextAutoGenerateReply *GenericNetworkManager::getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    // TODO
    return getChatCompletion(request);
}

GenericNetworkManager::PluginNetworkType GenericNetworkManager::pluginNetworkType() const
{
    return mPluginNetworkType;
}

void GenericNetworkManager::setPluginNetworkType(PluginNetworkType newPluginNetworkType)
{
    mPluginNetworkType = newPluginNetworkType;
}

QString GenericNetworkManager::webSite() const
{
    return mServerInfo->webSite(mPluginNetworkType);
}

QString GenericNetworkManager::chatPath() const
{
    return mServerInfo->chatCompletionPath(mPluginNetworkType);
}

QString GenericNetworkManager::apiUrl() const
{
    return mServerInfo->apiUrl(mPluginNetworkType);
}

QString GenericNetworkManager::description() const
{
    return mServerInfo->description(mPluginNetworkType);
}

QString GenericNetworkManager::pluginName() const
{
    return mServerInfo->pluginName(mPluginNetworkType);
}

QString GenericNetworkManager::translatedPluginName() const
{
    return mServerInfo->translatedName(mPluginNetworkType);
}

GenericNetworkSettings *GenericNetworkManager::genericNetworkSettings() const
{
    return mGenericNetworkSettings;
}

QList<GenericNetworkModelAvailableInfo> GenericNetworkManager::infos() const
{
    return mInfos;
}

void GenericNetworkManager::setInfos(const QList<GenericNetworkModelAvailableInfo> &newInfos)
{
    mInfos = newInfos;
}

QString GenericNetworkManager::apiKey() const
{
    return mApiKey;
}

void GenericNetworkManager::setApiKey(const QString &newApiKey)
{
    mApiKey = newApiKey;
}

bool GenericNetworkManager::hasVisionSupport(const QString &currentModel) const
{
    return mServerInfo->hasToolsSupport(currentModel, mPluginNetworkType);
}

bool GenericNetworkManager::hasToolsSupport(const QString &currentModel) const
{
    return mServerInfo->hasToolsSupport(currentModel, mPluginNetworkType);
}

bool GenericNetworkManager::hasOcrSupport(const QString &currentModel) const
{
    return mServerInfo->hasOcrSupport(currentModel, mPluginNetworkType);
}

bool GenericNetworkManager::hasAudioSupport(const QString &currentModel) const
{
    return mServerInfo->hasAudioSupport(currentModel, mPluginNetworkType);
}

#include "moc_genericnetworkmanager.cpp"
