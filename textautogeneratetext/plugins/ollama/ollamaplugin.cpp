/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaplugin.h"
#include "autogeneratetext_ollama_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "ollamaconfiguredialog.h"
#include "ollamamanager.h"
#include "ollamareply.h"
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
            Q_EMIT errorOccurred(modelinfo.errorOccured);
            mModels.clear();
        } else {
            mModels = modelinfo.models;
            setReady(true);
        }
    });
    connect(mOllamaManager, &OllamaManager::downloadDone, this, &OllamaPlugin::downloadModelFinished);

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
}

OllamaPlugin::~OllamaPlugin()
{
    delete mOllamaSettings;
}

void OllamaPlugin::load(const KConfigGroup &config)
{
    mOllamaSettings->setDisplayName(config.readEntry(u"Name"_s));
    mOllamaSettings->setSeed(config.readEntry(u"Seed"_s, 0));
    if (config.hasKey(u"ServerUrl"_s)) {
        mOllamaSettings->setServerUrl(config.readEntry(u"ServerUrl"_s, QUrl()));
    }
    if (config.hasKey(u"Temperature"_s)) {
        mOllamaSettings->setTemperature(config.readEntry(u"Temperature"_s, 0.8));
    }
    mOllamaSettings->setCurrentModel(config.readEntry(u"CurrentModel"_s));
}

void OllamaPlugin::save(KConfigGroup &config)
{
    config.writeEntry(u"Name"_s, mOllamaSettings->displayName());
    config.writeEntry(u"Seed"_s, mOllamaSettings->seed());
    config.writeEntry(u"ServerUrl"_s, mOllamaSettings->serverUrl());
    config.writeEntry(u"Temperature"_s, mOllamaSettings->temperature());
    config.writeEntry(u"CurrentModel"_s, mOllamaSettings->currentModel());
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

void OllamaPlugin::sendToAssistant(const SendToAssistantInfo &info)
{
    const TextAutoGenerateText::TextAutoGenerateTextRequest req = convertSendToAssistantInfoToTextRequest(info);
    auto reply = mOllamaManager->getChatCompletion(req);
    const QByteArray messageUuid = info.messageUuid;
    const QByteArray chatId = info.chatId;
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
}

bool OllamaPlugin::hasVisionSupport() const
{
    // TODO
    return false;
}

bool OllamaPlugin::hasToolsSupport() const
{
    // TODO
    return false;
}

#include "moc_ollamaplugin.cpp"
