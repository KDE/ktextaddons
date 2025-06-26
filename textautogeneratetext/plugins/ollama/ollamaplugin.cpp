/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaplugin.h"
#include "autogeneratetext_ollama_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "ollamaconfiguredialog.h"
#include "ollamamanager.h"
#include "ollamareply.h"
#include "ollamasettings.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaPlugin::OllamaPlugin(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, parent}
    , mOllamaSettings(new OllamaSettings)
    , mManager(new OllamaManager(mOllamaSettings, this))
{
    connect(mManager, &OllamaManager::modelsLoadDone, this, [this](const OllamaManager::ModelsInfo &modelinfo) {
        if (modelinfo.hasError) {
            setReady(false);
            Q_EMIT errorOccurred(modelinfo.errorOccured);
            mModels.clear();
        } else {
            mModels = modelinfo.models;
            setReady(true);
        }
    });
    mManager->loadModels();
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
    if (config.hasKey(u"SystemPrompt"_s)) {
        mOllamaSettings->setSystemPrompt(config.readEntry(u"SystemPrompt"_s));
    }
    mOllamaSettings->setCurrentModel(config.readEntry(u"CurrentModel"_s));
}

void OllamaPlugin::save(KConfigGroup &config)
{
    config.writeEntry(u"Name"_s, mOllamaSettings->displayName());
    config.writeEntry(u"Seed"_s, mOllamaSettings->seed());
    config.writeEntry(u"ServerUrl"_s, mOllamaSettings->serverUrl());
    config.writeEntry(u"SystemPrompt"_s, mOllamaSettings->systemPrompt());
    config.writeEntry(u"Temperature"_s, mOllamaSettings->temperature());
    config.writeEntry(u"CurrentModel"_s, mOllamaSettings->currentModel());
}

QString OllamaPlugin::translatedPluginName() const
{
    return i18n("Ollama");
}

void OllamaPlugin::showConfigureDialog(QWidget *parentWidget)
{
    OllamaConfigureDialog d(mManager, parentWidget);
    if (d.exec()) {
        Q_EMIT configChanged();
    }
}

void OllamaPlugin::clear()
{
    for (const auto &connection : std::as_const(mConnections)) {
        disconnect(connection.second);
    }
    mConnections.clear();
    // TODO clear all thread
}

void OllamaPlugin::setPrompt(const QString &text)
{
    // TODO
}

QString OllamaPlugin::engineName() const
{
    return "ollama"_L1;
}

void OllamaPlugin::cancelRequest(const QByteArray &uuid)
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

void OllamaPlugin::askToAssistant(const QString &msg)
{
    TextAutoGenerateText::TextAutoGenerateTextRequest req;
    req.setMessage(msg);
    req.setModel(currentModel());
    auto reply = mManager->getCompletion(req);
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
    TextAutoGenerateText::TextAutoGenerateTextRequest req;
    req.setMessage(info.message);
    req.setModel(currentModel());
    req.setMessages(info.messagesArray);
    auto reply = mManager->getChatCompletion(req);
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
    return mOllamaSettings->currentModel();
}

void OllamaPlugin::setCurrentModel(const QString &m)
{
    mOllamaSettings->setCurrentModel(m);
}

#include "moc_ollamaplugin.cpp"
