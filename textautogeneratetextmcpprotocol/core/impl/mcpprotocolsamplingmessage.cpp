/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsamplingmessage.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSamplingMessage::McpProtocolSamplingMessage() = default;
QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSamplingMessage &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "role:" << t.role();
    d.space() << "content:" << McpProtocolUtils::createMessageResultContentToJson(t.content());
    return d;
}

bool McpProtocolSamplingMessage::operator==(const McpProtocolSamplingMessage &other) const = default;

McpProtocolSamplingMessage McpProtocolSamplingMessage::fromJson(const QJsonObject &obj)
{
    if (!obj.contains("content"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: content";
        return {};
    }
    if (!obj.contains("role"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: role";
        return {};
    }
    McpProtocolSamplingMessage message;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        message.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    message.setContent(McpProtocolUtils::createMessageResultContentFromJson(obj["content"_L1]));
    message.setRole(McpProtocolUtils::convertRoleFromString(obj.value("role"_L1).toString()));
    return message;
}

QJsonObject McpProtocolSamplingMessage::toJson(const McpProtocolSamplingMessage &message)
{
    QJsonObject obj;
    if (message.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*message.meta());
    }
    obj["content"_L1] = McpProtocolUtils::createMessageResultContentToJson(message.content());
    obj["role"_L1] = McpProtocolUtils::convertRoleToString(message.role());
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolSamplingMessage::meta() const
{
    return mMeta;
}

void McpProtocolSamplingMessage::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

McpProtocolUtils::CreateMessageResultContent McpProtocolSamplingMessage::content() const
{
    return mContent;
}

void McpProtocolSamplingMessage::setContent(const McpProtocolUtils::CreateMessageResultContent &newContent)
{
    mContent = newContent;
}

McpProtocolUtils::Role McpProtocolSamplingMessage::role() const
{
    return mRole;
}

void McpProtocolSamplingMessage::setRole(McpProtocolUtils::Role newRole)
{
    mRole = newRole;
}
