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

using namespace TextAutogenerateText;

class TextAutogenerateText::TextAutogenerateTextPluginPrivate
{
public:
    bool hasError = false;
    bool isReady = false;
    QString currentModel;
};

TextAutogenerateTextPlugin::TextAutogenerateTextPlugin(QObject *parent)
    : QObject{parent}
    , d(new TextAutogenerateText::TextAutogenerateTextPluginPrivate)
{
}

TextAutogenerateTextPlugin::~TextAutogenerateTextPlugin() = default;

void TextAutogenerateTextPlugin::setHasError(bool error)
{
    d->hasError = error;
}

bool TextAutogenerateTextPlugin::ready() const
{
    return d->isReady;
}

void TextAutogenerateTextPlugin::setReady(bool newReady)
{
    d->isReady = newReady;
    Q_EMIT initializedDone();
}

void TextAutogenerateTextPlugin::editMessage(const QByteArray &uuid, const QString &str)
{
    if (ready()) {
        const QByteArray llmUuid = TextAutogenerateManager::self()->textAutoGenerateChatModel()->editMessage(uuid, str);
        sendToLLM(str, llmUuid);
    }
}

void TextAutogenerateTextPlugin::sendMessage(const QString &str)
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

        TextAutogenerateManager::self()->textAutoGenerateChatModel()->addMessage(std::move(msg));
        TextAutogenerateManager::self()->textAutoGenerateChatModel()->addMessage(std::move(msgLlm));
        sendToLLM(str, llmUuid);
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Plugin is not valid:";
    }
}

QString TextAutogenerateTextPlugin::currentModel() const
{
    return d->currentModel;
}

void TextAutogenerateTextPlugin::setCurrentModel(const QString &newCurrentModel)
{
    d->currentModel = newCurrentModel;
}

#include "moc_textautogeneratetextplugin.cpp"
