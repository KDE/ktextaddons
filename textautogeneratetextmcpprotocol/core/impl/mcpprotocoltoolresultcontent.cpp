/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltoolresultcontent.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"

#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolToolResultContent::McpProtocolToolResultContent() = default;

QByteArray McpProtocolToolResultContent::type()
{
    return "tool_result"_ba;
}

bool McpProtocolToolResultContent::operator==(const McpProtocolToolResultContent &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolResultContent &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "isError:" << t.isError();
    d.space() << "toolUseId:" << t.toolUseId();
    d.space() << "structuredContent:" << t.structuredContent();
    QJsonArray arr_content;
    const auto content = t.content();
    for (const auto &v : content) {
        arr_content.append(McpProtocolUtils::contentBlocktoJson(v));
    }
    d.space() << "content:" << arr_content;
    return d;
}

McpProtocolToolResultContent McpProtocolToolResultContent::fromJson(const QJsonObject &obj)
{
    if (obj.value("type"_L1).toString() != QString::fromLatin1(type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'type' must be" << type() << ", got:" << obj.value("type"_L1).toString();
        return {};
    }
    McpProtocolToolResultContent tool;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        tool.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue contentValue = obj.value("content"_L1); contentValue.isArray()) {
        const QJsonArray arr = contentValue.toArray();
        QList<McpProtocolUtils::ContentBlock> contents;
        contents.reserve(arr.count());
        for (const auto &v : arr) {
            // Ignore unknown content
            if (auto block = McpProtocolUtils::contentBlockFromJson(v)) {
                contents.append(std::move(*block));
            }
        }
        tool.setContent(std::move(contents));
    }
    if (obj.contains("isError"_L1)) {
        tool.setIsError(obj.value("isError"_L1).toBool());
    }
    if (const QJsonValue structuredContentValue = obj.value("structuredContent"_L1); structuredContentValue.isObject()) {
        const QJsonObject mapObj_structuredContent = structuredContentValue.toObject();
        QMap<QString, QJsonValue> map_structuredContent;
        for (auto it = mapObj_structuredContent.constBegin(); it != mapObj_structuredContent.constEnd(); ++it) {
            map_structuredContent.insert(it.key(), it.value());
        }
        tool.setStructuredContent(std::move(map_structuredContent));
    }
    tool.setToolUseId(obj.value("toolUseId"_L1).toString());
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
    const auto content = tool.content();
    for (const auto &v : content) {
        arr_content.append(McpProtocolUtils::contentBlocktoJson(v));
    }
    obj.insert("content"_L1, arr_content);
    if (tool.isError().has_value()) {
        obj.insert("isError"_L1, *tool.isError());
    }
    if (const auto structuredContent = tool.structuredContent(); structuredContent.has_value()) {
        QJsonObject map_structuredContent;
        for (auto it = structuredContent->constBegin(); it != structuredContent->constEnd(); ++it) {
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

void McpProtocolToolResultContent::setContent(QList<McpProtocolUtils::ContentBlock> newContent)
{
    mContent = std::move(newContent);
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
