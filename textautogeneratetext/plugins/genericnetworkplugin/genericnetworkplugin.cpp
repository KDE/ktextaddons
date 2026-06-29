/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericnetworkplugin.h"
#include "autogeneratetext_genericnetwork_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratereply.h"
#include "core/textautogeneratetextinstance.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "core/textautogeneratetextrequest.h"
#include "core/textautogeneratetextutils.h"
#include "genericnetworkconfiguredialog.h"
#include "genericnetworkmanager.h"
#include "genericnetworkserverinfo.h"
#include "genericnetworksettings.h"
#include "plugincommonsaveloadpassword.h"

using namespace Qt::Literals::StringLiterals;
GenericNetworkPlugin::GenericNetworkPlugin(TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                                           TextAutoGenerateText::TextAutoGenerateManager *manager,
                                           QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, instance, parent}
    , mSettings(new GenericNetworkSettings)
    , mGenericManager(new GenericNetworkManager(mSettings, this))
{
    const GenericNetworkServerInfo info;
    mGenericManager->setPluginNetworkType(info.pluginNetworkTypeFromString(instance->pluginIdentifier()));
    connect(mGenericManager,
            &GenericNetworkManager::modelsLoadDone,
            this,
            [this](const TextAutoGenerateText::TextAutoGenerateManagerBase::ModelsInfo &modelinfo) {
                if (modelinfo.hasError) {
                    setReady(false);
                    Q_EMIT downloadErrorOccurred(modelinfo.errorOccured);
                    mModels.clear();
                } else {
                    mModels = modelinfo.models;
                    setReady(true);
                }
            });
    connect(this, &GenericNetworkPlugin::loadApiKeyDone, this, [this]() {
        if (this->manager()->textAutoGenerateTextInstancesManager()->isCurrentInstance(instanceUuid())) {
            mGenericManager->loadModels();
        }
    });
}

GenericNetworkPlugin::~GenericNetworkPlugin()
{
    delete mSettings;
}

void GenericNetworkPlugin::remove()
{
    removeApiKey();
}

void GenericNetworkPlugin::removeApiKey()
{
    auto saveLoadJob = new PluginCommonSaveLoadPassword(this);
    saveLoadJob->removeApiKey(passwordServiceName(), instanceUuid());
}

QString GenericNetworkPlugin::passwordServiceName() const
{
    return QStringLiteral("GenericPluginAutoGenerateText");
}

void GenericNetworkPlugin::loadApiKey()
{
    auto saveLoadJob = new PluginCommonSaveLoadPassword(this);
    connect(saveLoadJob, &PluginCommonSaveLoadPassword::loadApiKeyDone, this, [this](const QString &data) {
        mGenericManager->setApiKey(data);
        Q_EMIT loadApiKeyDone();
    });
    saveLoadJob->loadApiKey(passwordServiceName(), instanceUuid());
}

void GenericNetworkPlugin::load(const KConfigGroup &config)
{
    mSettings->load(config);
    loadApiKey();
}

void GenericNetworkPlugin::save(KConfigGroup &config)
{
    mSettings->save(config);

    auto saveLoadJob = new PluginCommonSaveLoadPassword(this);
    saveLoadJob->writePassword(passwordServiceName(), instanceUuid(), mGenericManager->apiKey());
}

QString GenericNetworkPlugin::engineName() const
{
    return name();
}

void GenericNetworkPlugin::sendToAssistant(const SendToAssistantInfo &info)
{
    const TextAutoGenerateText::TextAutoGenerateTextRequest req = convertSendToAssistantInfoToTextRequest(info);
    auto reply = mGenericManager->getChatCompletion(req);
    if (!reply) {
        return;
    }
    const QByteArray messageUuid = info.messageUuid;
    const QByteArray chatId = info.chatId;
    mConnections.insert(reply,
                        QPair<QByteArray, QMetaObject::Connection>(
                            messageUuid,
                            connect(reply, &TextAutoGenerateText::TextAutoGenerateReply::contentAdded, this, [reply, messageUuid, chatId, this]() {
                                manager()->replaceContent(chatId, messageUuid, reply->readResponse(), {}); // TODO
                            })));
    mConnections.insert(reply,
                        QPair<QByteArray, QMetaObject::Connection>(
                            messageUuid,
                            connect(reply, &TextAutoGenerateText::TextAutoGenerateReply::finished, this, [reply, messageUuid, chatId, this] {
                                const auto response = reply->readResponse();
                                if (response.hasToolCallArguments()) {
                                    manager()->callTools(chatId, messageUuid, response.info);
                                } else {
                                    manager()->changeInProgress(chatId, messageUuid, false);
                                }

                                qCDebug(AUTOGENERATETEXT_GENERICNETWORK_PLUGIN_LOG) << " progress finished";
                                mConnections.remove(reply);
                                reply->deleteLater();
                                // Q_EMIT finished(message); // TODO add message as argument ???
                            })));
}

void GenericNetworkPlugin::askToAssistant(const QString &msg)
{
    TextAutoGenerateText::TextAutoGenerateTextRequest req;
    QJsonArray array;
    QJsonObject obj;
    obj["role"_L1] = u"user"_s;
    obj["content"_L1] = msg;
    array.append(obj);

    req.setMessages(array);
    req.setModel(currentModel());
    auto reply = mGenericManager->getCompletion(req);
    if (!reply) {
        return;
    }
    const QByteArray uuid = TextAutoGenerateText::TextAutoGenerateTextUtils::generateUUid();
    mConnections.insert(
        reply,
        QPair<QByteArray, QMetaObject::Connection>(uuid, connect(reply, &TextAutoGenerateText::TextAutoGenerateReply::contentAdded, this, [reply, this]() {
                                                       Q_EMIT askToAssistantAnswer(reply->readResponse());
                                                   })));
    mConnections.insert(
        reply,
        QPair<QByteArray, QMetaObject::Connection>(uuid, connect(reply, &TextAutoGenerateText::TextAutoGenerateReply::finished, this, [reply, this] {
                                                       Q_EMIT askToAssistantDone();
                                                       mConnections.remove(reply);
                                                       reply->deleteLater();
                                                       // Q_EMIT finished(message); // TODO add message as argument ???
                                                   })));
}

void GenericNetworkPlugin::cancelRequest(const QByteArray &uuid)
{
    if (uuid.isEmpty()) {
        clear();
    } else {
        for (const auto &connection : std::as_const(mConnections)) {
            if (connection.first == uuid) {
                disconnect(connection.second);
                // mConnections.take(connection.);
            }
        }
    }
}

QString GenericNetworkPlugin::name() const
{
    const GenericNetworkServerInfo info;
    return info.pluginName(mGenericManager->pluginNetworkType());
}

QString GenericNetworkPlugin::translatedPluginName() const
{
    return mGenericManager->translatedPluginName();
}

void GenericNetworkPlugin::showConfigureDialog(QWidget *parentWidget)
{
    GenericNetworkConfigureDialog d(mGenericManager, parentWidget);
    if (d.exec()) {
        Q_EMIT configChanged();
    }
}

QString GenericNetworkPlugin::displayName() const
{
    return mSettings->displayName();
}

void GenericNetworkPlugin::setDisplayName(const QString &newName)
{
    mSettings->setDisplayName(newName);
}

QString GenericNetworkPlugin::currentModel() const
{
    if (mSettings->currentModel().isEmpty()) {
        return fallBackModel();
    }
    return mSettings->currentModel();
}

void GenericNetworkPlugin::setCurrentModel(const QString &m)
{
    mSettings->setCurrentModel(m);
    Q_EMIT configChanged();
    Q_EMIT currentModelChanged();
}

TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType GenericNetworkPlugin::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Network;
}

bool GenericNetworkPlugin::hasVisionSupport() const
{
    return mGenericManager->hasVisionSupport(currentModel());
}

bool GenericNetworkPlugin::hasToolsSupport() const
{
    return mGenericManager->hasToolsSupport(currentModel());
}

bool GenericNetworkPlugin::hasOcrSupport() const
{
    return mGenericManager->hasOcrSupport(currentModel());
}

bool GenericNetworkPlugin::hasAudioSupport() const
{
    return mGenericManager->hasAudioSupport(currentModel());
}

bool GenericNetworkPlugin::hasThinkSupport() const
{
    return mGenericManager->hasThinkSupport(currentModel());
}

bool GenericNetworkPlugin::hasSystemMessageSupport() const
{
    return mGenericManager->hasSystemMessageSupport();
}

bool GenericNetworkPlugin::hasTextOnlySupport() const
{
    return mGenericManager->hasTextOnlySupport();
}

#include "moc_genericnetworkplugin.cpp"
