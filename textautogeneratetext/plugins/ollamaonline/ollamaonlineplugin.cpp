/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaonlineplugin.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "core/textautogeneratetextutils.h"
#include "ollamaonlineconfiguredialog.h"
#include <KLocalizedString>

using namespace Qt::Literals::StringLiterals;
OllamaOnlinePlugin::OllamaOnlinePlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                       TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                                       QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, instance, parent}
{
}

OllamaOnlinePlugin::~OllamaOnlinePlugin()
{
}

void OllamaOnlinePlugin::load(const KConfigGroup &config)
{
}

void OllamaOnlinePlugin::save(KConfigGroup &config)
{
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
    OllamaOnlineConfigureDialog d(/*mOllamaManager, */ parentWidget);
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
    /*
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
                                                   */
}

void OllamaOnlinePlugin::sendToAssistant(const SendToAssistantInfo &info)
{
    /*
    const TextAutoGenerateText::TextAutoGenerateTextRequest req = convertSendToAssistantInfoToTextRequest(info);
    auto reply = mOllamaManager->getChatCompletion(req);
    const QByteArray messageUuid = info.messageUuid;
    const QByteArray chatId = info.chatId;
    mConnections.insert(
        reply,
        QPair<QByteArray, QMetaObject::Connection>(messageUuid, connect(reply, &OllamaReply::contentAdded, this, [reply, messageUuid, chatId, this]() {
                                                       manager()->replaceContent(chatId, messageUuid, reply->readResponse(), {}); // TODO
                                                   })));
    mConnections.insert(
        reply,
        QPair<QByteArray, QMetaObject::Connection>(messageUuid, connect(reply, &OllamaReply::finished, this, [reply, messageUuid, chatId, this] {
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
                                                   */
}

QString OllamaOnlinePlugin::displayName() const
{
    return {};
    // return mOllamaSettings->displayName();
}

void OllamaOnlinePlugin::setDisplayName(const QString &newName)
{
    // mOllamaSettings->setDisplayName(newName);
}

QString OllamaOnlinePlugin::currentModel() const
{
    return {};
    /*
    if (mOllamaSettings->currentModel().isEmpty()) {
        return fallBackModel();
    }
    return mOllamaSettings->currentModel();
    */
}

void OllamaOnlinePlugin::setCurrentModel(const QString &m)
{
    /*
    mOllamaSettings->setCurrentModel(m);
    Q_EMIT configChanged();
    Q_EMIT currentModelChanged();
    */
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
#include "moc_ollamaonlineplugin.cpp"
