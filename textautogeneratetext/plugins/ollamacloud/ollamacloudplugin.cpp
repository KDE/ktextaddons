/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacloudplugin.h"
#include "autogeneratetext_ollamacloud_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "core/textautogeneratetextutils.h"
#include "ollamacloudconfiguredialog.h"
#include "ollamacloudmanager.h"
#include "ollamacloudsettings.h"
#include "ollamacommonmodelutils.h"
#include "ollamacommonreply.h"
#include <KLocalizedString>
#include <qt6keychain/keychain.h>
using namespace Qt::Literals::StringLiterals;
OllamaCloudPlugin::OllamaCloudPlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                     TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                                     QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, instance, parent}
    , mOllamaCloudSettings(new OllamaCloudSettings)
    , mOllamaCloudManager(new OllamaCloudManager(mOllamaCloudSettings, this))
{
    connect(this, &OllamaCloudPlugin::loadApiKeyDone, this, [this]() {
        if (this->manager()->textAutoGenerateTextInstancesManager()->isCurrentInstance(instanceUuid())) {
            mOllamaCloudManager->loadModels();
        }
    });
    connect(mOllamaCloudManager, &OllamaCloudManager::errorOccurred, this, &OllamaCloudPlugin::errorOccurred);
    connect(mOllamaCloudManager, &OllamaCloudManager::modelsLoadDone, this, [this](const OllamaCloudManager::ModelsInfo &modelinfo) {
        if (modelinfo.hasError) {
            setReady(false);
            Q_EMIT downloadErrorOccurred(modelinfo.errorOccured);
            mModels.clear();
        } else {
            mModels = modelinfo.models;
            setReady(true);
        }
    });
}

OllamaCloudPlugin::~OllamaCloudPlugin()
{
    delete mOllamaCloudSettings;
}

void OllamaCloudPlugin::load(const KConfigGroup &config)
{
    mOllamaCloudSettings->load(config);
    loadApiKey();
}

QString OllamaCloudPlugin::passwordServiceName() const
{
    return QStringLiteral("OllamaCloudPluginAutoGenerateText");
}

void OllamaCloudPlugin::save(KConfigGroup &config)
{
    mOllamaCloudSettings->save(config);
    auto writeJob = new QKeychain::WritePasswordJob(passwordServiceName());
    connect(writeJob, &QKeychain::Job::finished, this, [](QKeychain::Job *baseJob) {
        if (baseJob->error() != QKeychain::Error::NoError) {
            qCWarning(AUTOGENERATETEXT_OLLAMACLOUD_PLUGIN_LOG) << "Error writing password using QKeychain:" << baseJob->errorString();
        }
    });
    writeJob->setKey(QString::fromLatin1(instanceUuid()));
    writeJob->setTextData(mOllamaCloudManager->apiKey());
    writeJob->start();
}

void OllamaCloudPlugin::removeApiKey()
{
    auto deleteJob = new QKeychain::DeletePasswordJob(passwordServiceName());
    deleteJob->setKey(QString::fromLatin1(instanceUuid()));
    connect(deleteJob, &QKeychain::Job::finished, this, [this](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error()) {
            qCWarning(AUTOGENERATETEXT_OLLAMACLOUD_PLUGIN_LOG) << "We have an error during deleting password " << job->errorString();
        } else {
            mOllamaCloudManager->setApiKey(job->textData());
            Q_EMIT loadApiKeyDone();
        }
    });
    deleteJob->start();
}

void OllamaCloudPlugin::loadApiKey()
{
    auto readJob = new QKeychain::ReadPasswordJob(passwordServiceName());
    connect(readJob, &QKeychain::Job::finished, this, [this](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error()) {
            qCWarning(AUTOGENERATETEXT_OLLAMACLOUD_PLUGIN_LOG) << "We have an error during reading password " << job->errorString();
        } else {
            mOllamaCloudManager->setApiKey(job->textData());
            Q_EMIT loadApiKeyDone();
        }
    });
    readJob->setKey(QString::fromLatin1(instanceUuid()));
    readJob->start();
}

TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType OllamaCloudPlugin::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Network;
}

QString OllamaCloudPlugin::translatedPluginName() const
{
    return i18n("Ollama Cloud");
}

void OllamaCloudPlugin::showConfigureDialog(QWidget *parentWidget)
{
    OllamaCloudConfigureDialog d(mOllamaCloudManager, parentWidget);
    if (d.exec()) {
        Q_EMIT configChanged();
    }
}

QString OllamaCloudPlugin::engineName() const
{
    return "ollamacloud"_L1;
}

void OllamaCloudPlugin::askToAssistant(const QString &msg)
{
    TextAutoGenerateText::TextAutoGenerateTextRequest req;
    req.setMessage(msg);
    req.setModel(currentModel());
    auto reply = mOllamaCloudManager->getCompletion(req);
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
#if 0
                                // TODO add context + info
                            message.context = message.llmReply->context();
                            message.info = message.llmReply->info();
#endif
                                                       // Q_EMIT finished(message); // TODO add message as argument ???
                                                   })));
}

void OllamaCloudPlugin::sendToAssistant(const SendToAssistantInfo &info)
{
    const TextAutoGenerateText::TextAutoGenerateTextRequest req = convertSendToAssistantInfoToTextRequest(info);
    auto reply = mOllamaCloudManager->getChatCompletion(req);
    const QByteArray messageUuid = info.messageUuid;
    const QByteArray chatId = info.chatId;
    mConnections.insert(
        reply,
        QPair<QByteArray, QMetaObject::Connection>(messageUuid, connect(reply, &OllamaCommonReply::contentAdded, this, [reply, messageUuid, chatId, this]() {
                                                       manager()->replaceContent(chatId, messageUuid, reply->readResponse(), {}); // TODO
                                                   })));
    mConnections.insert(
        reply,
        QPair<QByteArray, QMetaObject::Connection>(messageUuid, connect(reply, &OllamaCommonReply::finished, this, [reply, messageUuid, chatId, this] {
                                                       const auto response = reply->readResponse();
                                                       if (response.hasToolCallArguments()) {
                                                           manager()->callTools(chatId, messageUuid, response.info);
                                                       } else {
                                                           manager()->changeInProgress(chatId, messageUuid, false);
                                                       }
                                                       qCDebug(AUTOGENERATETEXT_OLLAMACLOUD_PLUGIN_LOG) << " progress finished";
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

QString OllamaCloudPlugin::displayName() const
{
    return mOllamaCloudSettings->displayName();
}

void OllamaCloudPlugin::setDisplayName(const QString &newName)
{
    mOllamaCloudSettings->setDisplayName(newName);
}

QString OllamaCloudPlugin::currentModel() const
{
    if (mOllamaCloudSettings->currentModel().isEmpty()) {
        return fallBackModel();
    }
    return mOllamaCloudSettings->currentModel();
}

void OllamaCloudPlugin::setCurrentModel(const QString &m)
{
    mOllamaCloudSettings->setCurrentModel(m);
    Q_EMIT configChanged();
    Q_EMIT currentModelChanged();
}

bool OllamaCloudPlugin::hasVisionSupport() const
{
    return false;
}

bool OllamaCloudPlugin::hasToolsSupport() const
{
    return false;
}

bool OllamaCloudPlugin::hasOcrSupport() const
{
    return false;
}

bool OllamaCloudPlugin::hasAudioSupport() const
{
    return false;
}

bool OllamaCloudPlugin::hasThinkSupport() const
{
    return false;
}

void OllamaCloudPlugin::remove()
{
    removeApiKey();
}

QString OllamaCloudPlugin::shareNamePrompt() const
{
    return OllamaCommonModelUtils::generateUserPrompt(mOllamaCloudSettings->shareNameType());
}

#include "moc_ollamacloudplugin.cpp"
