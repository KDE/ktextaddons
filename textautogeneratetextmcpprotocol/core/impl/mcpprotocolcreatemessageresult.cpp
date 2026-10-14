/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcreatemessageresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <type_traits>
#include <utility>
#include <variant>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCreateMessageResult::McpProtocolCreateMessageResult() = default;

bool McpProtocolCreateMessageResult::operator==(const McpProtocolCreateMessageResult &other) const = default;

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
    const QJsonValue contentValue = obj.value("content"_L1);
    if (!contentValue.isObject() && !contentValue.isArray()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCreateMessageResult: missing required field 'content'";
        return {};
    }
    const McpProtocolUtils::CreateMessageResultContent content = McpProtocolUtils::createMessageResultContentFromJson(contentValue);
    if (contentValue.isObject()) {
        // A rejected content block is default-constructed
        const bool contentIsValid = std::visit(
            [](const auto &c) -> bool {
                using T = std::decay_t<decltype(c)>;
                return !(c == T());
            },
            content);
        if (!contentIsValid) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCreateMessageResult: invalid field 'content'";
            return {};
        }
    }
    const QJsonValue modelValue = obj.value("model"_L1);
    if (!modelValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCreateMessageResult: missing required field 'model'";
        return {};
    }
    const QJsonValue roleValue = obj.value("role"_L1);
    if (!roleValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCreateMessageResult: missing required field 'role'";
        return {};
    }
    const McpProtocolUtils::Role role = McpProtocolUtils::convertRoleFromString(roleValue.toString());
    if (role == McpProtocolUtils::Role::Unknown) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolCreateMessageResult: invalid field 'role'" << roleValue.toString();
        return {};
    }
    McpProtocolCreateMessageResult result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    result.setContent(content);
    result.setModel(modelValue.toString());
    result.setRole(role);
    if (obj.contains("stopReason"_L1)) {
        result.setStopReason(obj.value("stopReason"_L1).toString());
    }
    return result;
}

QJsonObject McpProtocolCreateMessageResult::toJson(const McpProtocolCreateMessageResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    obj["content"_L1] = McpProtocolUtils::createMessageResultContentToJson(result.content());
    obj["model"_L1] = result.model();
    // Unknown value is not valid, don't write it
    if (result.role() != McpProtocolUtils::Role::Unknown) {
        obj["role"_L1] = McpProtocolUtils::convertRoleToString(result.role());
    }
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

void McpProtocolCreateMessageResult::setContent(McpProtocolUtils::CreateMessageResultContent newContent)
{
    mContent = std::move(newContent);
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
