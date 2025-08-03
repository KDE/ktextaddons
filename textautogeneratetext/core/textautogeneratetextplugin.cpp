/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextplugin.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratemessage.h"
#include "core/textautogeneratetextinstance.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>

#include <QDateTime>
#include <QUuid>

using namespace TextAutoGenerateText;

class TextAutoGenerateText::TextAutoGenerateTextPluginPrivate
{
public:
    explicit TextAutoGenerateTextPluginPrivate(TextAutoGenerateManager *manager_, TextAutoGenerateText::TextAutoGenerateTextInstance *instance_)
        : manager(manager_)
        , instance(instance_)
    {
    }
    bool hasError = false;
    bool isReady = false;
    TextAutoGenerateManager *const manager;
    TextAutoGenerateText::TextAutoGenerateTextInstance *const instance;
};

TextAutoGenerateTextPlugin::TextAutoGenerateTextPlugin(TextAutoGenerateManager *manager,
                                                       TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                                                       QObject *parent)
    : QObject{parent}
    , d(new TextAutoGenerateText::TextAutoGenerateTextPluginPrivate(manager, instance))
{
}

TextAutoGenerateTextPlugin::~TextAutoGenerateTextPlugin() = default;

QByteArray TextAutoGenerateTextPlugin::instanceUuid() const
{
    return d->instance->instanceUuid();
}

void TextAutoGenerateTextPlugin::load(const KConfigGroup &config)
{
    Q_UNUSED(config);
    // reimpl
}

void TextAutoGenerateTextPlugin::save(KConfigGroup &config)
{
    Q_UNUSED(config);
    // reimpl
}

void TextAutoGenerateTextPlugin::remove()
{
    // reimpl
}

QList<TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier> TextAutoGenerateTextPlugin::models() const
{
    return mModels;
}

void TextAutoGenerateTextPlugin::setHasError(bool error)
{
    d->hasError = error;
}

bool TextAutoGenerateTextPlugin::ready() const
{
    return d->isReady;
}

void TextAutoGenerateTextPlugin::setReady(bool newReady)
{
    d->isReady = newReady;
    Q_EMIT initializedDone();
}

void TextAutoGenerateTextPlugin::editMessage(const QByteArray &chatId, const QByteArray &uuid, const QString &str)
{
    if (ready()) {
        auto messageModel = d->manager->messagesModelFromChatId(chatId);
        if (messageModel) {
            const QByteArray llmUuid = messageModel->editMessage(uuid, str);

            SendToAssistantInfo info;
            info.message = str;
            info.messageUuid = llmUuid;
            info.chatId = chatId;
            info.messagesArray = messageModel->convertToOllamaChat();

            initializeProgress(info);
        } else {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to find model for chatId:" << chatId;
        }
    }
}

void TextAutoGenerateTextPlugin::initializeProgress(const SendToAssistantInfo &info)
{
    // Start progress
    d->manager->changeInProgress(info.chatId, info.messageUuid, true);
    sendToAssistant(info);
}

void TextAutoGenerateTextPlugin::sendMessage(const QByteArray &chatId, const QString &str)
{
    if (ready()) {
        auto messageModel = d->manager->messagesModelFromChatId(chatId);
        if (!messageModel) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << " Model Message not found" << chatId;
            return;
        }
        // User Message
        TextAutoGenerateMessage msg;
        msg.setSender(TextAutoGenerateMessage::Sender::User);
        msg.setContent(str);
        const auto dt = QDateTime::currentSecsSinceEpoch();
        msg.setDateTime(dt);
        msg.setUuid(QUuid::createUuid().toByteArray(QUuid::Id128));

        // LLM Message
        TextAutoGenerateMessage msgLlm;
        msgLlm.setInProgress(true);
        msgLlm.setSender(TextAutoGenerateMessage::Sender::Assistant);
        msgLlm.setDateTime(dt);
        msgLlm.setUuid(QUuid::createUuid().toByteArray(QUuid::Id128));
        msgLlm.setEngineName(engineName());
        msgLlm.setModelName(currentModel());
        msgLlm.setInstanceName(d->instance->displayName());

        const QByteArray llmUuid = msgLlm.uuid();
        msg.setAnswerUuid(llmUuid);

        d->manager->addMessage(chatId, std::move(msg));
        SendToAssistantInfo info;
        info.message = str;
        info.messageUuid = llmUuid;
        info.chatId = d->manager->currentChatId();
        info.messagesArray = messageModel->convertToOllamaChat();

        d->manager->addMessage(chatId, std::move(msgLlm));
        // qDebug() << " info " << info;
        initializeProgress(info);
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Plugin is not valid:";
    }
}

TextAutoGenerateManager *TextAutoGenerateTextPlugin::manager() const
{
    return d->manager;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextPlugin::SendToAssistantInfo &t)
{
    d.space() << "message:" << t.message;
    d.space() << "messageUuid:" << t.messageUuid;
    d.space() << "chatId:" << t.chatId;
    d.space() << "messagesArray:" << t.messagesArray;
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier &t)
{
    d.space() << "modelName:" << t.modelName;
    d.space() << "identifier:" << t.identifier;
    return d;
}

bool TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier::isValid() const
{
    return !modelName.isEmpty() && !identifier.isEmpty();
}

void TextAutoGenerateTextPlugin::clear()
{
    for (const auto &connection : std::as_const(mConnections)) {
        disconnect(connection.second);
    }
    mConnections.clear();
    // TODO clear all thread
}

void TextAutoGenerateTextPlugin::cancelRequest(const QByteArray &uuid)
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

QString TextAutoGenerateTextPlugin::convertEngineType(TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType type)
{
    switch (type) {
    case TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Local:
        return i18n("Local");
    case TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Network:
        return i18n("Network");
    }
    Q_UNREACHABLE();
    return {};
}

QString TextAutoGenerateTextPlugin::fallBackModel() const
{
    // Fallback to first model
    if (!mModels.isEmpty()) {
        return mModels.constFirst().identifier;
    }
    qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Current model is empty. It will failed to work.";
    return {};
}

#include "moc_textautogeneratetextplugin.cpp"
