/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericnetworkplugin.h"
#include "core/textautogeneratereply.h"
#include "core/textautogeneratetextrequest.h"
#include "genericnetworkconfiguredialog.h"
#include "genericnetworkmanager.h"
#include "genericnetworkserverinfo.h"
#include "genericnetworksettings.h"
#include <qt6keychain/keychain.h>

using namespace Qt::Literals::StringLiterals;
GenericNetworkPlugin::GenericNetworkPlugin(const QString &serverIdentifier, TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, parent}
    , mSettings(new GenericNetworkSettings)
    , mGenericManager(new GenericNetworkManager(mSettings, this))
{
    const GenericNetworkServerInfo info;
    mGenericManager->setPluginNetworkType(info.pluginNetworkTypeFromString(serverIdentifier));
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
    mSettings->setTemperature(config.readEntry(u"Temperature"_s, 0.0));
    mSettings->setMaxTokens(config.readEntry(u"MaxToken"_s, 2048));
}

void GenericNetworkPlugin::save(KConfigGroup &config)
{
    config.writeEntry(u"Name"_s, mSettings->displayName());
    config.writeEntry(u"CurrentModel"_s, mSettings->currentModel());
    config.writeEntry(u"MaxToken"_s, mSettings->maxTokens());
    config.writeEntry(u"Temperature"_s, mSettings->temperature());
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
    const QByteArray messageUuid = info.messageUuid;
    const QByteArray chatId = info.chatId;
#if 0 // TODO
    mConnections.insert(
        reply,
        QPair<QByteArray, QMetaObject::Connection>(messageUuid, connect(reply, &OllamaReply::contentAdded, this, [reply, messageUuid, chatId, this]() {
                                                       manager()->replaceContent(chatId, messageUuid, reply->readResponse());
                                                   })));
    mConnections.insert(
        reply,
        QPair<QByteArray, QMetaObject::Connection>(messageUuid, connect(reply, &OllamaReply::finished, this, [reply, messageUuid, chatId, this] {
                                                       manager()->changeInProgress(chatId, messageUuid, false);
                                                       qCDebug(AUTOGENERATETEXT_OLLAMA_PLUGIN_LOG) << " progress finished";
                                                       mConnections.remove(reply);
                                                       reply->deleteLater();
#if 0
                                // TODO add context + info
                            message.context = message.llmReply->context();
                            message.info = message.llmReply->info();
#endif
                                                       // Q_EMIT finished(message); // TODO add message as argument ???
                                                   })));
#endif
}

void GenericNetworkPlugin::askToAssistant(const QString &msg)
{
    // TODO
}

void GenericNetworkPlugin::cancelRequest(const QByteArray &uuid)
{
    // TODO
}

void GenericNetworkPlugin::slotApiKeyRead(QKeychain::Job *baseJob)
{
    /*
    auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
    Q_ASSERT(job);
    if (!job->error()) {
        mMistralManager->setApiKey(job->textData());
    } else {
        qCWarning(AUTOGENERATETEXT_MISTRAL_LOG) << "We have an error during reading password " << job->errorString();
    }
    */
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
}

#include "moc_genericnetworkplugin.cpp"
