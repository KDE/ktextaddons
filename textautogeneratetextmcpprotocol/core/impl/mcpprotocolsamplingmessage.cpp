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
    const QJsonValue contentValue = obj.value("content"_L1);
    if (!contentValue.isObject() && !contentValue.isArray()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSamplingMessage: missing required field 'content'";
        return {};
    }
    const QJsonValue roleValue = obj.value("role"_L1);
    if (!roleValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSamplingMessage: missing required field 'role'";
        return {};
    }
    const McpProtocolUtils::Role role = McpProtocolUtils::convertRoleFromString(roleValue.toString());
    if (role == McpProtocolUtils::Role::Unknown) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolSamplingMessage: invalid field 'role'" << roleValue.toString();
        return {};
    }
    McpProtocolSamplingMessage message;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        message.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    message.setContent(McpProtocolUtils::createMessageResultContentFromJson(contentValue));
    message.setRole(role);
    return message;
}

bool McpProtocolSamplingMessage::isValid() const
{
    return mRole != McpProtocolUtils::Role::Unknown;
}

QJsonObject McpProtocolSamplingMessage::toJson(const McpProtocolSamplingMessage &message)
{
    QJsonObject obj;
    if (message.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*message.meta());
    }
    obj["content"_L1] = McpProtocolUtils::createMessageResultContentToJson(message.content());
    // Unknown value is not valid, don't write it
    if (message.role() != McpProtocolUtils::Role::Unknown) {
        obj["role"_L1] = McpProtocolUtils::convertRoleToString(message.role());
    }
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
