/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextplugin.h"
#include "core/textautogeneratechatmodel.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratemessage.h"
#include "textautogeneratetextcore_debug.h"

#include <QDateTime>

using namespace TextAutogenerateText;

class TextAutogenerateText::TextAutogenerateTextPluginPrivate
{
public:
    bool hasError = false;
    bool isReady = false;
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
}

void TextAutogenerateTextPlugin::sendMessage(const QString &str)
{
    if (ready()) {
        TextAutoGenerateMessage msg;
        msg.setSender(TextAutoGenerateMessage::Sender::User);
        msg.setContent(str);
        msg.setDateTime(QDateTime::currentSecsSinceEpoch());
        TextAutogenerateManager::self()->textAutoGenerateChatModel()->addMessage(std::move(msg));
        // TODO add question to LLM
        // TODO
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Plugin is not valid:";
    }
}

#include "moc_textautogeneratetextplugin.cpp"
