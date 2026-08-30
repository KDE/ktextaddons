/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolreadresourceresult.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolBlobResourceContents>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTextResourceContents>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolReadResourceResult::McpProtocolReadResourceResult() = default;

// bool McpProtocolReadResourceResult::operator==(const McpProtocolReadResourceResult &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolReadResourceResult &t)
{
    d.space() << "meta:" << t.meta();
    QJsonArray arr_contents;
    for (const auto &v : t.contents()) {
        arr_contents.append(McpProtocolUtils::embeddedResourceResourceToJson(v));
    }
    d.space() << "contents:" << arr_contents;
    return d;
}

McpProtocolReadResourceResult McpProtocolReadResourceResult::fromJson(const QJsonObject &obj)
{
    McpProtocolReadResourceResult prompt;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue contentsValue = obj.value("contents"_L1); contentsValue.isArray()) {
        QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::EmbeddedResourceResource> resources;
        const QJsonArray arr = contentsValue.toArray();
        resources.reserve(arr.size());
        for (const auto &v : arr) {
            resources.append(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::embeddedResourceResourceFromJson(v));
        }
        prompt.setContents(resources);
    }
    return prompt;
}

QJsonObject McpProtocolReadResourceResult::toJson(const McpProtocolReadResourceResult &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    QJsonArray arr_contents;
    for (const auto &v : boolean.contents()) {
        arr_contents.append(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::embeddedResourceResourceToJson(v));
    }
    obj.insert("contents"_L1, arr_contents);
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolReadResourceResult::meta() const
{
    return mMeta;
}

void McpProtocolReadResourceResult::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QList<McpProtocolUtils::EmbeddedResourceResource> McpProtocolReadResourceResult::contents() const
{
    return mContents;
}

void McpProtocolReadResourceResult::setContents(const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::EmbeddedResourceResource> &newContents)
{
    mContents = newContents;
}
