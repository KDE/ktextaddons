/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcreatemessageresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCreateMessageResult::McpProtocolCreateMessageResult() = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "model:" << t.model();
    d.space() << "role:" << t.role();
    d.space() << "stopReason:" << t.stopReason();
    d.space() << "content:" << McpProtocolUtils::createMessageResultContentToJson(t.content());
    return d;
}

McpProtocolCreateMessageResult McpProtocolCreateMessageResult::fromJson(const QJsonObject &obj)
{
    if (!obj.contains("content"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: content";
        return {};
    }
    if (!obj.contains("model"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: model";
        return {};
    }
    if (!obj.contains("role"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: role";
        return {};
    }
    McpProtocolCreateMessageResult prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    prompt.setContent(McpProtocolUtils::createMessageResultContentFromJson(obj["content"_L1]));
    prompt.setModel(obj.value("model"_L1).toString());
    prompt.setRole(McpProtocolUtils::convertRoleFromString(obj.value("role"_L1).toString()));
    if (obj.contains("stopReason"_L1)) {
        prompt.setStopReason(obj.value("stopReason"_L1).toString());
    }
    return prompt;
}

QJsonObject McpProtocolCreateMessageResult::toJson(const McpProtocolCreateMessageResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    obj["content"_L1] = McpProtocolUtils::createMessageResultContentToJson(result.content());
    obj["model"_L1] = result.model();
    obj["role"_L1] = McpProtocolUtils::convertRoleToString(result.role());
    if (result.stopReason().has_value()) {
        obj.insert("stopReason"_L1, *result.stopReason());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolCreateMessageResult::meta() const
{
    return mMeta;
}

void McpProtocolCreateMessageResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

McpProtocolUtils::CreateMessageResultContent McpProtocolCreateMessageResult::content() const
{
    return mContent;
}

void McpProtocolCreateMessageResult::setContent(const McpProtocolUtils::CreateMessageResultContent &newContent)
{
    mContent = newContent;
}

QString McpProtocolCreateMessageResult::model() const
{
    return mModel;
}

void McpProtocolCreateMessageResult::setModel(const QString &newModel)
{
    mModel = newModel;
}

McpProtocolUtils::Role McpProtocolCreateMessageResult::role() const
{
    return mRole;
}

void McpProtocolCreateMessageResult::setRole(McpProtocolUtils::Role newRole)
{
    mRole = newRole;
}

std::optional<QString> McpProtocolCreateMessageResult::stopReason() const
{
    return mStopReason;
}

void McpProtocolCreateMessageResult::setStopReason(std::optional<QString> newStopReason)
{
    mStopReason = std::move(newStopReason);
}
