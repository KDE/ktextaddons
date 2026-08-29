/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolelicitresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitResult::McpProtocolElicitResult() = default;

McpProtocolElicitResult::~McpProtocolElicitResult() = default;

bool McpProtocolElicitResult::operator==(const McpProtocolElicitResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "action:" << t.action();
    if (t.content().has_value()) {
        d.space() << "content:" << McpProtocolUtils::elicitResultContentToJson(*t.content());
    }
    return d;
}

McpProtocolElicitResult McpProtocolElicitResult::fromJson(const QJsonObject &obj)
{
    if (!obj.contains("action"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: action";
        return {};
    }
    McpProtocolElicitResult prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    prompt.setAction(convertActionFromString(obj.value("action"_L1).toString()));
    if (const QJsonValue contentValue = obj.value("content"_L1); contentValue.isObject()) {
        prompt.setContent(McpProtocolUtils::elicitResultContentFromJson(contentValue.toObject()));
    }
    return prompt;
}

QJsonObject McpProtocolElicitResult::toJson(const McpProtocolElicitResult &result)
{
    QJsonObject obj;
    if (result.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*result.meta());
    }
    obj["action"_L1] = convertActionToString(result.action());
    if (result.content().has_value()) {
        obj["content"_L1] = McpProtocolUtils::elicitResultContentToJson(*result.content());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolElicitResult::meta() const
{
    return mMeta;
}

void McpProtocolElicitResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

McpProtocolElicitResult::Action McpProtocolElicitResult::action() const
{
    return mAction;
}

void McpProtocolElicitResult::setAction(Action newAction)
{
    mAction = newAction;
}

std::optional<QMap<QString, McpProtocolUtils::ElicitResultContentValue>> McpProtocolElicitResult::content() const
{
    return mContent;
}

void McpProtocolElicitResult::setContent(std::optional<QMap<QString, McpProtocolUtils::ElicitResultContentValue>> newContent)
{
    mContent = std::move(newContent);
}

QString McpProtocolElicitResult::convertActionToString(McpProtocolElicitResult::Action action)
{
    switch (action) {
    case Action::Accept:
        return u"accept"_s;
    case Action::Cancel:
        return u"cancel"_s;
    case Action::Decline:
        return u"decline"_s;
    case Action::Unknown:
        return {};
    }
    return {};
}

McpProtocolElicitResult::Action McpProtocolElicitResult::convertActionFromString(const QString &str)
{
    if (str == "accept"_L1) {
        return McpProtocolElicitResult::Action::Accept;
    }
    if (str == "cancel"_L1) {
        return McpProtocolElicitResult::Action::Cancel;
    }
    if (str == "decline"_L1) {
        return McpProtocolElicitResult::Action::Decline;
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid ElicitResult::Action value: " << str;
    return McpProtocolElicitResult::Action::Unknown;
}

#include "moc_mcpprotocolelicitresult.cpp"
