/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgetpromptresult.h"
#include <QDebug>
#include <QJsonObject>

#include <QJsonArray>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetPromptResult::McpProtocolGetPromptResult() = default;

bool McpProtocolGetPromptResult::operator==(const McpProtocolGetPromptResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "description:" << t.description();
    d.space() << "messages:" << t.messages();
    return d;
}

McpProtocolGetPromptResult McpProtocolGetPromptResult::fromJson(const QJsonObject &obj)
{
    McpProtocolGetPromptResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (obj.contains("description"_L1)) {
        result.setDescription(obj.value("description"_L1).toString());
    }
    if (const QJsonValue messagesValue = obj.value("messages"_L1); messagesValue.isArray()) {
        const QJsonArray arr = messagesValue.toArray();
        QList<McpProtocolPromptMessage> msgs;
        msgs.reserve(arr.count());
        for (const auto &v : arr) {
            msgs.append(McpProtocolPromptMessage::fromJson(v.toObject()));
        }
        result.setMessages(std::move(msgs));
    }
    return result;
}

QJsonObject McpProtocolGetPromptResult::toJson(const McpProtocolGetPromptResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    if (result.description().has_value()) {
        obj["description"_L1] = *result.description();
    }
    QJsonArray messages;
    for (const auto &v : result.messages()) {
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

void McpProtocolGetPromptResult::setMessages(QList<McpProtocolPromptMessage> newMessages)
{
    mMessages = std::move(newMessages);
}
