/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltoolresultcontent.h"
#include "mcpprotocolaudiocontent.h"
#include "mcpprotocolblobresourcecontents.h"
#include "mcpprotocolcancellednotification.h"
#include "mcpprotocolembeddedresource.h"
#include "mcpprotocolimagecontent.h"
#include "mcpprotocolinitializednotification.h"
#include "mcpprotocolprogressnotification.h"
#include "mcpprotocolresourcelink.h"
#include "mcpprotocolrootslistchangednotification.h"
#include "mcpprotocoltaskstatusnotification.h"
#include "mcpprotocoltextcontent.h"
#include "mcpprotocoltextresourcecontents.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"

#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolToolResultContent::McpProtocolToolResultContent() = default;

McpProtocolToolResultContent::~McpProtocolToolResultContent() = default;

QByteArray McpProtocolToolResultContent::type()
{
    return QByteArrayLiteral("tool_result");
}

// bool McpProtocolToolResultContent::operator==(const McpProtocolToolResultContent &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolResultContent &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "isError:" << t.isError();
    d.space() << "toolUseId:" << t.toolUseId();
    d.space() << "structuredContent:" << t.structuredContent();
    // d.space() << "content:" << t.content();
    return d;
}

McpProtocolToolResultContent McpProtocolToolResultContent::fromJson(const QJsonObject &obj)
{
    McpProtocolToolResultContent tool;

    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        tool.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("content"_L1) && obj["content"_L1].isArray()) {
        const QJsonArray arr = obj["content"_L1].toArray();
        QList<McpProtocolUtils::ContentBlock> contents;
        for (const auto &v : arr) {
            contents.append(McpProtocolUtils::contentBlockFromJson(v));
        }
        tool.setContent(contents);
    }
    if (obj.contains("isError"_L1)) {
        tool.setIsError(obj.value("isError"_L1).toBool());
    }
    if (obj.contains("structuredContent"_L1) && obj["structuredContent"_L1].isObject()) {
        const QJsonObject mapObj_structuredContent = obj["structuredContent"_L1].toObject();
        QMap<QString, QJsonValue> map_structuredContent;
        for (auto it = mapObj_structuredContent.constBegin(); it != mapObj_structuredContent.constEnd(); ++it) {
            map_structuredContent.insert(it.key(), it.value());
        }
        tool.setStructuredContent(map_structuredContent);
    }
    tool.setToolUseId(obj.value("toolUseId"_L1).toString());
    if (obj.value("type"_L1).toString() != QString::fromLatin1(type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'type' must be 'tool_result', got: " << obj.value("type"_L1).toString();
    }
    return tool;
}

QJsonObject McpProtocolToolResultContent::toJson(const McpProtocolToolResultContent &tool)
{
    QJsonObject obj;
    obj["toolUseId"_L1] = tool.toolUseId();
    obj["type"_L1] = QString::fromLatin1(type());

    if (tool.meta().has_value()) {
        obj.insert("_meta"_L1, McpProtocolMeta::toJson(*tool.meta()));
    }
    QJsonArray arr_content;
    for (const auto &v : tool.content()) {
        arr_content.append(McpProtocolUtils::contentBlocktoJson(v));
    }
    obj.insert("content"_L1, arr_content);
    if (tool.isError().has_value()) {
        obj.insert("isError"_L1, *tool.isError());
    }
    if (tool.structuredContent().has_value()) {
        QJsonObject map_structuredContent;
        for (auto it = tool.structuredContent()->constBegin(); it != tool.structuredContent()->constEnd(); ++it) {
            map_structuredContent.insert(it.key(), it.value());
        }
        obj.insert("structuredContent"_L1, map_structuredContent);
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolToolResultContent::meta() const
{
    return mMeta;
}

void McpProtocolToolResultContent::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QList<McpProtocolUtils::ContentBlock> McpProtocolToolResultContent::content() const
{
    return mContent;
}

void McpProtocolToolResultContent::setContent(const QList<McpProtocolUtils::ContentBlock> &newContent)
{
    mContent = newContent;
}

std::optional<bool> McpProtocolToolResultContent::isError() const
{
    return mIsError;
}

void McpProtocolToolResultContent::setIsError(std::optional<bool> newIsError)
{
    mIsError = newIsError;
}

std::optional<QMap<QString, QJsonValue>> McpProtocolToolResultContent::structuredContent() const
{
    return mStructuredContent;
}

void McpProtocolToolResultContent::setStructuredContent(std::optional<QMap<QString, QJsonValue>> newStructuredContent)
{
    mStructuredContent = std::move(newStructuredContent);
}

QString McpProtocolToolResultContent::toolUseId() const
{
    return mToolUseId;
}

void McpProtocolToolResultContent::setToolUseId(const QString &newToolUseId)
{
    mToolUseId = newToolUseId;
}
