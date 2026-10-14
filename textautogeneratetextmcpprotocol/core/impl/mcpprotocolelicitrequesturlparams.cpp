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

bool TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::operator==(const McpProtocolElicitRequestURLParams &other) const = default;

bool McpProtocolElicitRequestURLParams::isValid() const
{
    // Empty message is allowed: only check that it was set (fromJson() returns a default object on error)
    return !mElicitationId.isEmpty() && !mMessage.isNull() && !mUrl.isEmpty();
}

McpProtocolElicitRequestURLParams TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams::fromJson(const QJsonObject &obj)
{
    const QJsonValue elicitationIdValue = obj.value("elicitationId"_L1);
    if (!elicitationIdValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolElicitRequestURLParams: missing required field 'elicitationId'";
        return {};
    }
    const QJsonValue messageValue = obj.value("message"_L1);
    if (!messageValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolElicitRequestURLParams: missing required field 'message'";
        return {};
    }
    const QJsonValue urlValue = obj.value("url"_L1);
    if (!urlValue.isString()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolElicitRequestURLParams: missing required field 'url'";
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
    result.setElicitationId(elicitationIdValue.toString());
    result.setMessage(messageValue.toString());
    if (const QJsonValue taskValue = obj.value("task"_L1); taskValue.isObject()) {
        result.setTask(McpProtocolTaskMetadata::fromJson(taskValue.toObject()));
    }
    result.setUrl(urlValue.toString());
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
