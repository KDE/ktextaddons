/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaonlineplugin.h"
#include "autogeneratetext_ollamaonline_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "core/textautogeneratetextutils.h"
#include "ollamacommonmodelutils.h"
#include "ollamacommonreply.h"
#include "ollamaonlineconfiguredialog.h"
#include "ollamaonlinemanager.h"
#include "ollamaonlinesettings.h"
#include "plugincommonsaveloadpassword.h"
#include <KLocalizedString>
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
    connect(mOllamaOnlineManager, &OllamaOnlineManager::errorOccurred, this, &OllamaOnlinePlugin::errorOccurred);
    connect(mOllamaOnlineManager, &OllamaOnlineManager::modelsLoadDone, this, [this](const OllamaOnlineManager::ModelsInfo &modelinfo) {
        if (modelinfo.hasError) {
            setReady(false);
            Q_EMIT downloadErrorOccurred(modelinfo.errorOccured);
            mModels.clear();
        } else {
            mModels = modelinfo.models;
            setReady(true);
            const QList<OllamaCommonModelAvailableInfo> displayAvailablesModels = OllamaCommonModelUtils::extractAvailableModel(modelinfo);
            mOllamaOnlineManager->setAvailableInfos(displayAvailablesModels);
        }
    });
}

OllamaOnlinePlugin::~OllamaOnlinePlugin()
{
    delete mOllamaOnlineSettings;
}

void OllamaOnlinePlugin::load(const KConfigGroup &config)
{
    mOllamaOnlineSettings->load(config);
    loadApiKey();
}

QString OllamaOnlinePlugin::passwordServiceName() const
{
    return QStringLiteral("OllamaOnlinePluginAutoGenerateText");
}

void OllamaOnlinePlugin::save(KConfigGroup &config)
{
    mOllamaOnlineSettings->save(config);

    auto saveLoadJob = new PluginCommonSaveLoadPassword(this);
    saveLoadJob->writePassword(passwordServiceName(), instanceUuid(), mOllamaOnlineManager->apiKey());
}

void OllamaOnlinePlugin::removeApiKey()
{
    auto saveLoadJob = new PluginCommonSaveLoadPassword(this);
    saveLoadJob->removeApiKey(passwordServiceName(), instanceUuid());
}

void OllamaOnlinePlugin::loadApiKey()
{
    auto saveLoadJob = new PluginCommonSaveLoadPassword(this);
    connect(saveLoadJob, &PluginCommonSaveLoadPassword::loadApiKeyDone, this, [this](const QString &data) {
        mOllamaOnlineManager->setApiKey(data);
        Q_EMIT loadApiKeyDone();
    });
    saveLoadJob->loadApiKey(passwordServiceName(), instanceUuid());
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
                                                   })));
}

void OllamaOnlinePlugin::sendToAssistant(const SendToAssistantInfo &info)
{
    const TextAutoGenerateText::TextAutoGenerateTextRequest req = convertSendToAssistantInfoToTextRequest(info);
    auto reply = mOllamaOnlineManager->getChatCompletion(req);
    if (!reply) {
        return;
    }
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

bool OllamaOnlinePlugin::hasThinkSupport() const
{
    return mOllamaOnlineSettings->thoughtProcessing() && mOllamaOnlineManager->hasThinkSupport(currentModel());
}

void OllamaOnlinePlugin::remove()
{
    removeApiKey();
}

QString OllamaOnlinePlugin::shareNamePrompt() const
{
    return OllamaCommonModelUtils::generateUserPrompt(mOllamaOnlineSettings->shareNameType());
}

#include "moc_ollamaonlineplugin.cpp"
