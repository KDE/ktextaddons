/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextplugin.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratemessage.h"
#include "core/textautogeneratemessagesmodel.h"
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

void TextAutoGenerateTextPlugin::editMessage(const QByteArray &uuid, const QString &str)
{
    if (ready()) {
        const QByteArray llmUuid = d->manager->textAutoGenerateMessagesModel()->editMessage(uuid, str);
        sendToLLM(str, llmUuid);
    }
}

void TextAutoGenerateTextPlugin::sendMessage(const QString &str)
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
        msgLlm.setSender(TextAutoGenerateMessage::Sender::LLM);
        msgLlm.setDateTime(QDateTime::currentSecsSinceEpoch());
        msgLlm.setUuid(QUuid::createUuid().toByteArray(QUuid::Id128));
        msgLlm.setEngineName(engineName());
        msgLlm.setModelName(currentModel());

        const QByteArray llmUuid = msgLlm.uuid();
        msg.setAnswerUuid(llmUuid);

        d->manager->addMessage(std::move(msg));
        d->manager->addMessage(std::move(msgLlm));
        sendToLLM(str, llmUuid);
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

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextPlugin::SendToLLMInfo &t)
{
    d.space() << "message:" << t.message;
    d.space() << "messageUuid:" << t.messageUuid;
    d.space() << "chatId:" << t.chatId;
    return d;
}

#include "moc_textautogeneratetextplugin.cpp"
