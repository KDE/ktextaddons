/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmanager.h"
#include "core/textautogenerateengineaccessmanager.h"
#include "genericnetworkserverinfo.h"
#include "genericnetworksettings.h"
#include "modelsmanager/genericnetworkmodelavailableinfos.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
using namespace Qt::Literals::StringLiterals;
GenericNetworkManager::GenericNetworkManager(GenericNetworkSettings *settings, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateManagerBase{parent}
    , mGenericNetworkSettings(settings)
{
}

GenericNetworkManager::~GenericNetworkManager() = default;

void GenericNetworkManager::loadModels()
{
    if (mCheckConnect) {
        disconnect(mCheckConnect);
    }
    QNetworkRequest req{QUrl::fromUserInput(apiUrl() + u"models"_s)};
    req.setHeader(QNetworkRequest::ContentTypeHeader, u"application/json"_s);

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
        ModelsInfo info;
        // qDebug() << " json " << json;
        for (const auto &parsedInfo : infos.infos()) {
            TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier i;
            i.modelName = parsedInfo.modelName();
            i.identifier = parsedInfo.identifier();
            info.models.push_back(std::move(i));
        }
        info.isReady = !info.models.isEmpty();
        info.hasError = false;
        Q_EMIT modelsLoadDone(std::move(info));
    });
}

TextAutoGenerateText::TextAutoGenerateReply *GenericNetworkManager::getCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    // TODO
    return {};
}

TextAutoGenerateText::TextAutoGenerateReply *GenericNetworkManager::getChatCompletion(const TextAutoGenerateText::TextAutoGenerateTextRequest &request)
{
    // TODO
    return {};
}

GenericNetworkManager::PluginNetworkType GenericNetworkManager::pluginNetworkType() const
{
    return mPluginNetworkType;
}

void GenericNetworkManager::setPluginNetworkType(PluginNetworkType newPluginNetworkType)
{
    mPluginNetworkType = newPluginNetworkType;
}

QString GenericNetworkManager::translatedName() const
{
    const GenericNetworkServerInfo info;
    return info.translatedName(mPluginNetworkType);
}

QString GenericNetworkManager::webSite() const
{
    const GenericNetworkServerInfo info;
    return info.webSite(mPluginNetworkType);
}

QString GenericNetworkManager::apiUrl() const
{
    const GenericNetworkServerInfo info;
    return info.apiUrl(mPluginNetworkType);
}

QString GenericNetworkManager::description() const
{
    const GenericNetworkServerInfo info;
    return info.description(mPluginNetworkType);
}

QString GenericNetworkManager::pluginName() const
{
    const GenericNetworkServerInfo info;
    return info.pluginName(mPluginNetworkType);
}

QString GenericNetworkManager::translatedPluginName() const
{
    const GenericNetworkServerInfo info;
    return info.translatedName(mPluginNetworkType);
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

#include "moc_genericnetworkmanager.cpp"
