/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgetpromptresult.h"
#include <QDebug>
#include <QJsonObject>

#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolGetPromptResult::McpProtocolGetPromptResult() = default;

McpProtocolGetPromptResult::~McpProtocolGetPromptResult() = default;

bool McpProtocolGetPromptResult::operator==(const McpProtocolGetPromptResult &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolGetPromptResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "description:" << t.description();
    d.space() << "messages:" << t.messages();
    return d;
}

McpProtocolGetPromptResult McpProtocolGetPromptResult::fromJson(const QJsonObject &obj)
{
    McpProtocolGetPromptResult prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("description"_L1)) {
        prompt.setDescription(obj.value("description"_L1).toString());
    }
    if (obj.contains("messages"_L1) && obj["messages"_L1].isArray()) {
        const QJsonArray arr = obj["messages"_L1].toArray();
        QList<McpProtocolPromptMessage> msgs;
        for (const QJsonValue &v : arr) {
            msgs.append(McpProtocolPromptMessage::fromJson(v.toObject()));
        }
        prompt.setMessages(msgs);
    }
    return prompt;
}

QJsonObject McpProtocolGetPromptResult::toJson(const McpProtocolGetPromptResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.description().has_value()) {
        obj["description"_L1] = *boolean.description();
    }
    QJsonArray messages;
    for (const auto &v : boolean.messages()) {
        messages.append(McpProtocolPromptMessage::toJson(v));
    }
    obj.insert("messages"_L1, messages);
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolGetPromptResult::meta() const
{
    return mMeta;
}

void McpProtocolGetPromptResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolGetPromptResult::description() const
{
    return mDescription;
}

void McpProtocolGetPromptResult::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

QList<McpProtocolPromptMessage> McpProtocolGetPromptResult::messages() const
{
    return mMessages;
}

void McpProtocolGetPromptResult::setMessages(const QList<McpProtocolPromptMessage> &newMessage)
{
    mMessages = newMessage;
}
