/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericnetworkplugin.h"
#include "autogeneratetext_genericnetwork_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratereply.h"
#include "core/textautogeneratetextinstance.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "core/textautogeneratetextrequest.h"
#include "genericnetworkconfiguredialog.h"
#include "genericnetworkmanager.h"
#include "genericnetworkserverinfo.h"
#include "genericnetworksettings.h"
#include <qt6keychain/keychain.h>

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
                    Q_EMIT errorOccurred(modelinfo.errorOccured);
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
    auto deleteJob = new QKeychain::DeletePasswordJob(QStringLiteral("GenericPluginAutoGenerateText"));
    deleteJob->setKey(QString::fromLatin1(instanceUuid()));
    connect(deleteJob, &QKeychain::Job::finished, this, [this](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error()) {
            qCWarning(AUTOGENERATETEXT_GENERICNETWORK_PLUGIN_LOG) << "We have an error during deleting password " << job->errorString();
        } else {
            mGenericManager->setApiKey(job->textData());
            Q_EMIT loadApiKeyDone();
        }
    });
    deleteJob->start();
}

void GenericNetworkPlugin::loadApiKey()
{
    auto readJob = new QKeychain::ReadPasswordJob(QStringLiteral("GenericPluginAutoGenerateText"));
    connect(readJob, &QKeychain::Job::finished, this, [this](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error()) {
            qCWarning(AUTOGENERATETEXT_GENERICNETWORK_PLUGIN_LOG) << "We have an error during reading password " << job->errorString();
        } else {
            mGenericManager->setApiKey(job->textData());
            Q_EMIT loadApiKeyDone();
        }
    });
    readJob->setKey(QString::fromLatin1(instanceUuid()));
    readJob->start();
}

void GenericNetworkPlugin::load(const KConfigGroup &config)
{
    mSettings->setDisplayName(config.readEntry(u"Name"_s));
    mSettings->setCurrentModel(config.readEntry(u"CurrentModel"_s));
    mSettings->setTemperature(config.readEntry(u"Temperature"_s, 0.8));
    mSettings->setMaxTokens(config.readEntry(u"MaxToken"_s, 2048));
    mSettings->setSeed(config.readEntry(u"Seed"_s, 0));
    loadApiKey();
}

void GenericNetworkPlugin::save(KConfigGroup &config)
{
    config.writeEntry(u"Name"_s, mSettings->displayName());
    config.writeEntry(u"CurrentModel"_s, mSettings->currentModel());
    config.writeEntry(u"MaxToken"_s, mSettings->maxTokens());
    config.writeEntry(u"Temperature"_s, mSettings->temperature());
    config.writeEntry(u"Seed"_s, mSettings->seed());
    auto writeJob = new QKeychain::WritePasswordJob(QStringLiteral("GenericPluginAutoGenerateText"));
    connect(writeJob, &QKeychain::Job::finished, this, [](QKeychain::Job *baseJob) {
        if (baseJob->error() != QKeychain::Error::NoError) {
            qCWarning(AUTOGENERATETEXT_GENERICNETWORK_PLUGIN_LOG) << "Error writing password using QKeychain:" << baseJob->errorString();
        }
    });
    writeJob->setKey(QString::fromLatin1(instanceUuid()));
    writeJob->setTextData(mGenericManager->apiKey());
    writeJob->start();
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
#if 0
                                // TODO add context + info
                            message.context = message.llmReply->context();
                            message.info = message.llmReply->info();
#endif
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
    const QByteArray uuid = QUuid::createUuid().toByteArray(QUuid::Id128);
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
#if 0
                                // TODO add context + info
                            message.context = message.llmReply->context();
                            message.info = message.llmReply->info();
#endif
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

#include "moc_genericnetworkplugin.cpp"
