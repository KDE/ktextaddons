/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextplugin.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratemessage.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>

#include <QDateTime>
#include <QUuid>

using namespace TextAutoGenerateText;

class TextAutoGenerateText::TextAutoGenerateTextPluginPrivate
{
public:
    bool hasError = false;
    bool isReady = false;
    QString currentModel;
    TextAutoGenerateManager *manager = nullptr;
};

TextAutoGenerateTextPlugin::TextAutoGenerateTextPlugin(QObject *parent)
    : QObject{parent}
    , d(new TextAutoGenerateText::TextAutoGenerateTextPluginPrivate)
{
}

TextAutoGenerateTextPlugin::~TextAutoGenerateTextPlugin() = default;

void TextAutoGenerateTextPlugin::showConfigureDialog(QWidget *parentWidget)
{
    Q_UNUSED(parentWidget);
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
    sendToAssistant(std::move(info));
}

void TextAutoGenerateTextPlugin::sendMessage(const QByteArray &chatId, const QString &str)
{
    if (ready()) {
        // User Message
        TextAutoGenerateMessage msg;
        msg.setSender(TextAutoGenerateMessage::Sender::User);
        msg.setContent(str);
        msg.setDateTime(QDateTime::currentSecsSinceEpoch());
        msg.setUuid(QUuid::createUuid().toByteArray(QUuid::Id128));

        // LLM Message
        TextAutoGenerateMessage msgLlm;
        msgLlm.setInProgress(true);
        msgLlm.setSender(TextAutoGenerateMessage::Sender::Assistant);
        msgLlm.setDateTime(QDateTime::currentSecsSinceEpoch());
        msgLlm.setUuid(QUuid::createUuid().toByteArray(QUuid::Id128));
        msgLlm.setEngineName(engineName());
        msgLlm.setModelName(currentModel());
        // TODO msgLlm.setInstanceName(currentModel());

        const QByteArray llmUuid = msgLlm.uuid();
        msg.setAnswerUuid(llmUuid);

        d->manager->addMessage(chatId, std::move(msg));
        SendToAssistantInfo info;
        info.message = str;
        info.messageUuid = llmUuid;
        info.chatId = d->manager->currentChatId();
        auto messageModel = d->manager->messagesModelFromChatId(chatId);
        info.messagesArray = messageModel->convertToOllamaChat();

        d->manager->addMessage(chatId, std::move(msgLlm));
        // qDebug() << " info " << info;
        initializeProgress(info);
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Plugin is not valid:";
    }
}

QString TextAutoGenerateTextPlugin::currentModel() const
{
    return d->currentModel;
}

void TextAutoGenerateTextPlugin::setCurrentModel(const QString &newCurrentModel)
{
    d->currentModel = newCurrentModel;
}

void TextAutoGenerateTextPlugin::setManager(TextAutoGenerateManager *manager)
{
    d->manager = manager;
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

#include "moc_textautogeneratetextplugin.cpp"
