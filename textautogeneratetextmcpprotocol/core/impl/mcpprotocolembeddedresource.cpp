/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolembeddedresource.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolEmbeddedResource::McpProtocolEmbeddedResource() = default;

McpProtocolEmbeddedResource::~McpProtocolEmbeddedResource() = default;

QByteArray McpProtocolEmbeddedResource::type()
{
    return "resource"_ba;
}

bool McpProtocolEmbeddedResource::operator==(const McpProtocolEmbeddedResource &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolEmbeddedResource &t)
{
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolEmbeddedResource McpProtocolEmbeddedResource::fromJson(const QJsonObject &obj)
{
    McpProtocolEmbeddedResource prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("annotations"_L1) && obj["annotations"_L1].isObject()) {
        prompt.setAnnotations(McpProtocolAnnotations::fromJson(obj["annotations"_L1].toObject()));
    }
    if (obj.contains("resource"_L1)) {
        prompt.setResource(McpProtocolUtils::embeddedResourceResourceFromJson(obj["resource"_L1]));
    }
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolEmbeddedResource::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'type' must be 'resource', got: " << obj.value("type"_L1).toString();
    }
    return prompt;
}

QJsonObject McpProtocolEmbeddedResource::toJson(const McpProtocolEmbeddedResource &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }

    obj["resource"_L1] = McpProtocolUtils::embeddedResourceResourceToJson(boolean.resource());
    obj["type"_L1] = QString::fromLatin1(McpProtocolEmbeddedResource::type());
    if (boolean.annotations().has_value()) {
        obj["annotations"_L1] = McpProtocolAnnotations::toJson(*boolean.annotations());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolEmbeddedResource::meta() const
{
    return mMeta;
}

void McpProtocolEmbeddedResource::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolAnnotations> McpProtocolEmbeddedResource::annotations() const
{
    return mAnnotations;
}

void McpProtocolEmbeddedResource::setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations)
{
    mAnnotations = std::move(newAnnotations);
}

McpProtocolUtils::EmbeddedResourceResource McpProtocolEmbeddedResource::resource() const
{
    return mResource;
}

void McpProtocolEmbeddedResource::setResource(const McpProtocolUtils::EmbeddedResourceResource &newResource)
{
    mResource = newResource;
}
