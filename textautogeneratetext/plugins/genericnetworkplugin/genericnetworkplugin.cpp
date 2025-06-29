/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericnetworkplugin.h"
#include "autogeneratetext_genericnetwork_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratereply.h"
#include "core/textautogeneratetextinstance.h"
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
    mGenericManager->loadModels();
}

GenericNetworkPlugin::~GenericNetworkPlugin()
{
    delete mSettings;
}

void GenericNetworkPlugin::load(const KConfigGroup &config)
{
    mSettings->setDisplayName(config.readEntry(u"Name"_s));
    mSettings->setCurrentModel(config.readEntry(u"CurrentModel"_s));
    mSettings->setTemperature(config.readEntry(u"Temperature"_s, 0.8));
    mSettings->setMaxTokens(config.readEntry(u"MaxToken"_s, 2048));
    auto readJob = new QKeychain::ReadPasswordJob(QStringLiteral("GenericPluginAutoGenerateText"));
    connect(readJob, &QKeychain::Job::finished, this, [this](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error()) {
            qCWarning(AUTOGENERATETEXT_GENERICNETWORK_PLUGIN_LOG) << "We have an error during reading password " << job->errorString();
        } else {
            mGenericManager->setApiKey(job->textData());
        }
    });
    readJob->setKey(QString::fromLatin1(instanceUuid()));
    readJob->start();
}

void GenericNetworkPlugin::save(KConfigGroup &config)
{
    config.writeEntry(u"Name"_s, mSettings->displayName());
    config.writeEntry(u"CurrentModel"_s, mSettings->currentModel());
    config.writeEntry(u"MaxToken"_s, mSettings->maxTokens());
    config.writeEntry(u"Temperature"_s, mSettings->temperature());
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

void GenericNetworkPlugin::clear()
{
}

void GenericNetworkPlugin::setPrompt(const QString &text)
{
    // TODO
}

QString GenericNetworkPlugin::engineName() const
{
    return name();
}

void GenericNetworkPlugin::sendToAssistant(const SendToAssistantInfo &info)
{
    TextAutoGenerateText::TextAutoGenerateTextRequest req;
    req.setMessage(info.message);
    req.setModel(currentModel());
    req.setMessages(info.messagesArray);
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
                                manager()->replaceContent(chatId, messageUuid, reply->readResponse());
                            })));
    mConnections.insert(reply,
                        QPair<QByteArray, QMetaObject::Connection>(
                            messageUuid,
                            connect(reply, &TextAutoGenerateText::TextAutoGenerateReply::finished, this, [reply, messageUuid, chatId, this] {
                                manager()->changeInProgress(chatId, messageUuid, false);
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
    // TODO
}

void GenericNetworkPlugin::cancelRequest(const QByteArray &uuid)
{
    // TODO
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
    return mSettings->currentModel();
}

void GenericNetworkPlugin::setCurrentModel(const QString &m)
{
    mSettings->setCurrentModel(m);
    Q_EMIT configChanged();
}

#include "moc_genericnetworkplugin.cpp"
