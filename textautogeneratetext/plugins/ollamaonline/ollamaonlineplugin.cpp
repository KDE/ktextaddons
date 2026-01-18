/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaonlineplugin.h"
#include "autogeneratetext_ollamaonline_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "core/textautogeneratetextutils.h"
#include "ollamacommonreply.h"
#include "ollamaonlineconfiguredialog.h"
#include "ollamaonlinemanager.h"
#include "ollamaonlinesettings.h"
#include <KLocalizedString>
#include <qt6keychain/keychain.h>
using namespace Qt::Literals::StringLiterals;
OllamaOnlinePlugin::OllamaOnlinePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                       TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                                       QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, instance, parent}
    , mOllamaOnlineSettings(new OllamaOnlineSettings)
    , mOllamaOnlineManager(new OllamaOnlineManager(mOllamaOnlineSettings, this))
{
    connect(this, &OllamaOnlinePlugin::loadApiKeyDone, this, [this]() {
        if (this->manager()->textAutoGenerateTextInstancesManager()->isCurrentInstance(instanceUuid())) {
            mOllamaOnlineManager->loadModels();
        }
    });
    connect(mOllamaOnlineManager, &OllamaOnlineManager::modelsLoadDone, this, [this](const OllamaOnlineManager::ModelsInfo &modelinfo) {
        if (modelinfo.hasError) {
            setReady(false);
            Q_EMIT errorOccurred(modelinfo.errorOccured);
            mModels.clear();
        } else {
            mModels = modelinfo.models;
            setReady(true);
        }
    });
}

OllamaOnlinePlugin::~OllamaOnlinePlugin()
{
    delete mOllamaOnlineSettings;
}

void OllamaOnlinePlugin::load(const KConfigGroup &config)
{
    mOllamaOnlineSettings->setDisplayName(config.readEntry(u"Name"_s));
    if (config.hasKey(u"ServerUrl"_s)) {
        mOllamaOnlineSettings->setServerUrl(config.readEntry(u"ServerUrl"_s, QUrl()));
    }
    mOllamaOnlineSettings->setCurrentModel(config.readEntry(u"CurrentModel"_s));
    loadApiKey();
}

QString OllamaOnlinePlugin::passwordServiceName() const
{
    return QStringLiteral("OllamaOnlinePluginAutoGenerateText");
}

void OllamaOnlinePlugin::save(KConfigGroup &config)
{
    config.writeEntry(u"Name"_s, mOllamaOnlineSettings->displayName());
    config.writeEntry(u"ServerUrl"_s, mOllamaOnlineSettings->serverUrl());
    config.writeEntry(u"CurrentModel"_s, mOllamaOnlineSettings->currentModel());
    auto writeJob = new QKeychain::WritePasswordJob(passwordServiceName());
    connect(writeJob, &QKeychain::Job::finished, this, [](QKeychain::Job *baseJob) {
        if (baseJob->error() != QKeychain::Error::NoError) {
            qCWarning(AUTOGENERATETEXT_OLLAMAONLINE_PLUGIN_LOG) << "Error writing password using QKeychain:" << baseJob->errorString();
        }
    });
    writeJob->setKey(QString::fromLatin1(instanceUuid()));
    writeJob->setTextData(mOllamaOnlineManager->apiKey());
    writeJob->start();
}

void OllamaOnlinePlugin::removeApiKey()
{
    auto deleteJob = new QKeychain::DeletePasswordJob(passwordServiceName());
    deleteJob->setKey(QString::fromLatin1(instanceUuid()));
    connect(deleteJob, &QKeychain::Job::finished, this, [this](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error()) {
            qCWarning(AUTOGENERATETEXT_OLLAMAONLINE_PLUGIN_LOG) << "We have an error during deleting password " << job->errorString();
        } else {
            mOllamaOnlineManager->setApiKey(job->textData());
            Q_EMIT loadApiKeyDone();
        }
    });
    deleteJob->start();
}

void OllamaOnlinePlugin::loadApiKey()
{
    auto readJob = new QKeychain::ReadPasswordJob(passwordServiceName());
    connect(readJob, &QKeychain::Job::finished, this, [this](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error()) {
            qCWarning(AUTOGENERATETEXT_OLLAMAONLINE_PLUGIN_LOG) << "We have an error during reading password " << job->errorString();
        } else {
            mOllamaOnlineManager->setApiKey(job->textData());
            Q_EMIT loadApiKeyDone();
        }
    });
    readJob->setKey(QString::fromLatin1(instanceUuid()));
    readJob->start();
}

TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType OllamaOnlinePlugin::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Network;
}

QString OllamaOnlinePlugin::translatedPluginName() const
{
    return i18n("Ollama Online");
}

void OllamaOnlinePlugin::showConfigureDialog(QWidget *parentWidget)
{
    OllamaOnlineConfigureDialog d(mOllamaOnlineManager, parentWidget);
    if (d.exec()) {
        Q_EMIT configChanged();
    }
}

QString OllamaOnlinePlugin::engineName() const
{
    return "ollamaonline"_L1;
}

void OllamaOnlinePlugin::askToAssistant(const QString &msg)
{
    TextAutoGenerateText::TextAutoGenerateTextRequest req;
    req.setMessage(msg);
    req.setModel(currentModel());
    auto reply = mOllamaOnlineManager->getCompletion(req);
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

void OllamaOnlinePlugin::sendToAssistant(const SendToAssistantInfo &info)
{
    const TextAutoGenerateText::TextAutoGenerateTextRequest req = convertSendToAssistantInfoToTextRequest(info);
    auto reply = mOllamaOnlineManager->getChatCompletion(req);
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
                                                       qCDebug(AUTOGENERATETEXT_OLLAMAONLINE_PLUGIN_LOG) << " progress finished";
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

QString OllamaOnlinePlugin::displayName() const
{
    return mOllamaOnlineSettings->displayName();
}

void OllamaOnlinePlugin::setDisplayName(const QString &newName)
{
    mOllamaOnlineSettings->setDisplayName(newName);
}

QString OllamaOnlinePlugin::currentModel() const
{
    if (mOllamaOnlineSettings->currentModel().isEmpty()) {
        return fallBackModel();
    }
    return mOllamaOnlineSettings->currentModel();
}

void OllamaOnlinePlugin::setCurrentModel(const QString &m)
{
    mOllamaOnlineSettings->setCurrentModel(m);
    Q_EMIT configChanged();
    Q_EMIT currentModelChanged();
}

bool OllamaOnlinePlugin::hasVisionSupport() const
{
    return false;
}

bool OllamaOnlinePlugin::hasToolsSupport() const
{
    return false;
}

bool OllamaOnlinePlugin::hasOcrSupport() const
{
    return false;
}

bool OllamaOnlinePlugin::hasAudioSupport() const
{
    return false;
}

void OllamaOnlinePlugin::remove()
{
    removeApiKey();
}

#include "moc_ollamaonlineplugin.cpp"
