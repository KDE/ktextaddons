/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaplugin.h"
#include "autogeneratetext_ollama_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "ollamaconfiguredialog.h"
#include "ollamamanager.h"
#include "ollamasettings.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaPlugin::OllamaPlugin(TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, parent}
    , mManager(new OllamaManager(this))
{
    if (!loadSettings()) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_PLUGIN_LOG) << "Impossible to load settings";
        return;
    }

    connect(mManager, &OllamaManager::modelsLoadDone, this, [this](const OllamaManager::ModelsInfo &modelinfo) {
        if (modelinfo.hasError) {
            setReady(false);
            Q_EMIT errorOccurred(modelinfo.errorOccured);
        } else {
            setReady(true);
        }
    });
    mManager->loadModels();
}

OllamaPlugin::~OllamaPlugin() = default;

void OllamaPlugin::load(const KConfigGroup &config)
{
    // TODO
}

void OllamaPlugin::save(KConfigGroup &config)
{
    // TODO
}

QStringList OllamaPlugin::models() const
{
    // TODO
    return {};
}

QString OllamaPlugin::name()
{
    return "ollama"_L1;
}

QString OllamaPlugin::translatedPluginName() const
{
    return i18n("Ollama");
}

void OllamaPlugin::showConfigureDialog(QWidget *parentWidget)
{
    OllamaConfigureDialog d(mManager, parentWidget);
    d.exec();
}

bool OllamaPlugin::loadSettings()
{
    setCurrentModel(OllamaSettings::model());
    // TODO verify that server is ok.
    return true;
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
    return name();
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
    mConnections.insert(reply, QPair<QByteArray, QMetaObject::Connection>(uuid, connect(reply, &OllamaReply::contentAdded, this, [reply, this]() {
                                                                              Q_EMIT askToAssistantAnswer(reply->readResponse());
                                                                          })));
    mConnections.insert(reply, QPair<QByteArray, QMetaObject::Connection>(uuid, connect(reply, &OllamaReply::finished, this, [reply, this] {
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

#include "moc_ollamaplugin.cpp"
