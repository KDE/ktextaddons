/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaplugin.h"
#include "autogeneratetext_ollama_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "core/textautogeneratetextutils.h"
#include "ollamacommonmodelutils.h"
#include "ollamacommonreply.h"
#include "ollamaconfiguredialog.h"
#include "ollamamanager.h"
#include "ollamasettings.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaPlugin::OllamaPlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                           TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                           QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, instance, parent}
    , mOllamaSettings(new OllamaSettings)
    , mOllamaManager(new OllamaManager(mOllamaSettings, this))
{
    connect(mOllamaManager, &OllamaManager::modelsLoadDone, this, [this](const OllamaManager::ModelsInfo &modelinfo) {
        if (modelinfo.hasError) {
            setReady(false);
            Q_EMIT downloadErrorOccurred(modelinfo.errorOccured);
            mModels.clear();
        } else {
            mModels = modelinfo.models;
            setReady(true);
        }
    });
    connect(mOllamaManager, &OllamaManager::downloadDone, this, &OllamaPlugin::downloadModelFinished);
    connect(mOllamaManager, &OllamaManager::errorOccurred, this, &OllamaPlugin::errorOccurred);

    connect(manager, &TextAutoGenerateText::TextAutoGenerateManager::loadEngineDone, this, [this]() {
        if (this->manager()->textAutoGenerateTextInstancesManager()->isCurrentInstance(instanceUuid())) {
            mOllamaManager->loadModels();
        }
    });
    connect(mOllamaManager, &OllamaManager::finished, this, [this](const TextAutoGenerateText::TextAutoGenerateReply::Response &replyResponse) {
        if (replyResponse.hasToolCallArguments()) {
            Q_EMIT callTools(replyResponse.info);
        }
    });
    connect(this->manager(), &TextAutoGenerateText::TextAutoGenerateManager::startOllamaRequested, this, [this]() {
        slotOllamaRequested();
    });
    connect(mOllamaManager, &OllamaManager::ollamaStarted, this, &OllamaPlugin::slotOllamaStarted);
    connect(mOllamaManager, &OllamaManager::ollamaFailed, this, &OllamaPlugin::slotOllamaFailed);
}

OllamaPlugin::~OllamaPlugin()
{
    delete mOllamaSettings;
}

void OllamaPlugin::slotOllamaStarted()
{
    Q_EMIT this->manager()->ollamaProcessOk(true);
}

void OllamaPlugin::slotOllamaFailed([[maybe_unused]] const QString &errorStr)
{
    Q_EMIT this->manager()->ollamaFailed();
}

void OllamaPlugin::slotOllamaRequested()
{
    mOllamaManager->startOllama();
}

void OllamaPlugin::load(const KConfigGroup &config)
{
    mOllamaSettings->load(config);
}

void OllamaPlugin::save(KConfigGroup &config)
{
    mOllamaSettings->save(config);
}

TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType OllamaPlugin::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Local;
}

QString OllamaPlugin::translatedPluginName() const
{
    return i18n("Ollama");
}

void OllamaPlugin::showConfigureDialog(QWidget *parentWidget)
{
    OllamaConfigureDialog d(mOllamaManager, parentWidget);
    if (d.exec()) {
        Q_EMIT configChanged();
    }
}

QString OllamaPlugin::engineName() const
{
    return "ollama"_L1;
}

void OllamaPlugin::askToAssistant(const QString &msg)
{
    TextAutoGenerateText::TextAutoGenerateTextRequest req;
    req.setMessage(msg);
    req.setModel(currentModel());
    auto reply = mOllamaManager->getCompletion(req);
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

void OllamaPlugin::sendToAssistant(const SendToAssistantInfo &info)
{
    const TextAutoGenerateText::TextAutoGenerateTextRequest req = convertSendToAssistantInfoToTextRequest(info);
    auto reply = mOllamaManager->getChatCompletion(req);
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
}

QString OllamaPlugin::displayName() const
{
    return mOllamaSettings->displayName();
}

void OllamaPlugin::setDisplayName(const QString &newName)
{
    mOllamaSettings->setDisplayName(newName);
}

QString OllamaPlugin::currentModel() const
{
    if (mOllamaSettings->currentModel().isEmpty()) {
        return fallBackModel();
    }
    return mOllamaSettings->currentModel();
}

void OllamaPlugin::setCurrentModel(const QString &m)
{
    mOllamaSettings->setCurrentModel(m);
    Q_EMIT configChanged();
    Q_EMIT currentModelChanged();
}

bool OllamaPlugin::hasVisionSupport() const
{
    return mOllamaManager->hasVisionSupport(currentModel());
}

bool OllamaPlugin::hasToolsSupport() const
{
    return mOllamaManager->hasToolsSupport(currentModel());
}

bool OllamaPlugin::hasOcrSupport() const
{
    return mOllamaManager->hasOcrSupport(currentModel());
}

bool OllamaPlugin::hasAudioSupport() const
{
    return mOllamaManager->hasAudioSupport(currentModel());
}

bool OllamaPlugin::hasThinkSupport() const
{
    return mOllamaSettings->thoughtProcessing() && mOllamaManager->hasThinkSupport(currentModel());
}

QString OllamaPlugin::shareNamePrompt() const
{
    return OllamaCommonModelUtils::generateUserPrompt(mOllamaSettings->shareNameType());
}

#include "moc_ollamaplugin.cpp"
