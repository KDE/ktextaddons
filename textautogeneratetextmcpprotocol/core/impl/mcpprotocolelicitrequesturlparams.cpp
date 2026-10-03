/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolelicitrequesturlparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitRequestURLParams::McpProtocolElicitRequestURLParams() = default;

QByteArray McpProtocolElicitRequestURLParams::mode()
{
    return "url"_ba;
}

McpProtocolElicitRequestURLParams::Meta McpProtocolElicitRequestURLParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitRequestURLParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    QJsonObject additionalProperties = obj;
    additionalProperties.remove("progressToken"_L1);
    meta.setAdditionalProperties(additionalProperties);
    return meta;
}

QJsonObject McpProtocolElicitRequestURLParams::Meta::toJson(const McpProtocolElicitRequestURLParams::Meta &meta)
{
    QJsonObject obj = meta.additionalProperties();
    if (meta.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*meta.progressToken());
    }
    return obj;
}

std::optional<McpProtocolElicitRequestURLParams::Meta> McpProtocolElicitRequestURLParams::meta() const
{
    return mMeta;
}

void McpProtocolElicitRequestURLParams::setMeta(std::optional<Meta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolElicitRequestURLParams::elicitationId() const
{
    return mElicitationId;
}

void McpProtocolElicitRequestURLParams::setElicitationId(const QString &newElicitationId)
{
    mElicitationId = newElicitationId;
}

QString McpProtocolElicitRequestURLParams::message() const
{
    return mMessage;
}

void McpProtocolElicitRequestURLParams::setMessage(const QString &newMessage)
{
    mMessage = newMessage;
}

std::optional<McpProtocolTaskMetadata> McpProtocolElicitRequestURLParams::task() const
{
    return mTask;
}

void McpProtocolElicitRequestURLParams::setTask(std::optional<McpProtocolTaskMetadata> newTask)
{
    mTask = std::move(newTask);
}

QString McpProtocolElicitRequestURLParams::url() const
{
    return mUrl;
}

void McpProtocolElicitRequestURLParams::setUrl(const QString &newUrl)
{
    mUrl = newUrl;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "url:" << t.url();
    d.space() << "task:" << t.task();
    d.space() << "elicitationId:" << t.elicitationId();
    d.space() << "message:" << t.message();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
    d.space() << "additionalProperties:" << t.additionalProperties();
    return d;
}

std::optional<McpProtocolUtils::ProgressToken> McpProtocolElicitRequestURLParams::Meta::progressToken() const
{
    return mProgressToken;
}

void McpProtocolElicitRequestURLParams::Meta::setProgressToken(std::optional<McpProtocolUtils::ProgressToken> newProgressToken)
{
    mProgressToken = std::move(newProgressToken);
}

QJsonObject McpProtocolElicitRequestURLParams::Meta::additionalProperties() const
{
    return mAdditionalProperties;
}

void McpProtocolElicitRequestURLParams::Meta::setAdditionalProperties(const QJsonObject &newAdditionalProperties)
{
    mAdditionalProperties = newAdditionalProperties;
}

bool TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::Meta::operator==(const McpProtocolElicitRequestURLParams::Meta &other) const =
    default;

bool TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::operator==(const McpProtocolElicitRequestURLParams &other) const = default;

McpProtocolElicitRequestURLParams TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::fromJson(const QJsonObject &obj)
{
    if (!obj.contains("elicitationId"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: elicitationId";
        return {};
    }
    if (!obj.contains("message"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: message";
        return {};
    }
    if (!obj.contains("mode"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: mode";
        return {};
    }
    if (!obj.contains("url"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: url";
        return {};
    }
    if (obj.value("mode"_L1).toString() != QString::fromLatin1(McpProtocolElicitRequestURLParams::mode())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolElicitRequestURLParams: field 'mode' must be" << McpProtocolElicitRequestURLParams::mode()
                                                       << "got:" << obj.value("mode"_L1).toString();
        return {};
    }
    McpProtocolElicitRequestURLParams result;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        result.setMeta(McpProtocolElicitRequestURLParams::Meta::fromJson(metaValue.toObject()));
    }
    result.setElicitationId(obj.value("elicitationId"_L1).toString());
    result.setMessage(obj.value("message"_L1).toString());
    if (const QJsonValue taskValue = obj.value("task"_L1); taskValue.isObject()) {
        result.setTask(McpProtocolTaskMetadata::fromJson(taskValue.toObject()));
    }
    result.setUrl(obj.value("url"_L1).toString());
    return result;
}

QJsonObject TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::toJson(const McpProtocolElicitRequestURLParams &params)
{
    QJsonObject obj;
    obj["elicitationId"_L1] = params.elicitationId();
    obj["message"_L1] = params.message();
    obj["mode"_L1] = QString::fromLatin1(McpProtocolElicitRequestURLParams::mode());
    obj["url"_L1] = params.url();
    if (params.meta().has_value()) {
        obj.insert("_meta"_L1, McpProtocolElicitRequestURLParams::Meta::toJson(*params.meta()));
    }
    if (params.task().has_value()) {
        obj["task"_L1] = McpProtocolTaskMetadata::toJson(*params.task());
    }
    return obj;
}
