/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolelicitrequesturlparams.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitRequestURLParams::McpProtocolElicitRequestURLParams() = default;
McpProtocolElicitRequestURLParams::~McpProtocolElicitRequestURLParams() = default;

McpProtocolElicitRequestURLParams::Meta McpProtocolElicitRequestURLParams::Meta::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitRequestURLParams::Meta meta;
    if (obj.contains("progressToken"_L1)) {
        meta.setProgressToken(McpProtocolUtils::progressTokenFromJson(obj["progressToken"_L1]));
    }
    return meta;
}

QJsonObject McpProtocolElicitRequestURLParams::Meta::toJson(const McpProtocolElicitRequestURLParams::Meta &image)
{
    QJsonObject obj;
    if (image.progressToken().has_value()) {
        obj["progressToken"_L1] = McpProtocolUtils::progressTokenToJson(*image.progressToken());
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
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::Meta &t)
{
    d.space() << "progressToken:" << t.progressToken();
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

bool TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::Meta::operator==(const McpProtocolElicitRequestURLParams::Meta &other) const =
    default;

bool TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::operator==(const McpProtocolElicitRequestURLParams &other) const = default;

McpProtocolElicitRequestURLParams TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitRequestURLParams result;
    if (!obj.contains("elicitationId"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: elicitationId";
        return result;
    }
    if (!obj.contains("message"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: message";
        return result;
    }
    if (!obj.contains("mode"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: mode";
        return result;
    }
    if (!obj.contains("url"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: url";
        return result;
    }
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        result.setMeta(McpProtocolElicitRequestURLParams::Meta::fromJson(obj["_meta"_L1].toObject()));
    }
    result.setElicitationId(obj.value("elicitationId"_L1).toString());
    result.setMessage(obj.value("message"_L1).toString());
    if (obj.value("mode"_L1).toString() != "url"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'mode' must be 'url', got: " << obj.value("mode"_L1).toString();
        return result;
    }
    if (obj.contains("task"_L1) && obj["task"_L1].isObject()) {
        result.setTask(McpProtocolTaskMetadata::fromJson(obj["task"_L1].toObject()));
    }
    result.setUrl(obj.value("url"_L1).toString());
    return result;
}

QJsonObject TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::toJson(const McpProtocolElicitRequestURLParams &params)
{
    QJsonObject obj;
    obj["elicitationId"_L1] = params.elicitationId();
    obj["message"_L1] = params.message();
    obj["mode"_L1] = u"url"_s;
    obj["url"_L1] = params.url();
    if (params.meta().has_value()) {
        obj.insert("_meta"_L1, McpProtocolElicitRequestURLParams::Meta::toJson(*params.meta()));
    }
    if (params.task().has_value()) {
        obj["task"_L1] = McpProtocolTaskMetadata::toJson(*params.task());
    }
    return obj;
}
