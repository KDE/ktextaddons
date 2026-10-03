/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolembeddedresource.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolEmbeddedResource::McpProtocolEmbeddedResource() = default;

QByteArray McpProtocolEmbeddedResource::type()
{
    return "resource"_ba;
}

bool McpProtocolEmbeddedResource::operator==(const McpProtocolEmbeddedResource &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolEmbeddedResource &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "annotations:" << t.annotations();
    d.space() << "resource:" << McpProtocolUtils::embeddedResourceResourceToJson(t.resource());
    return d;
}

McpProtocolEmbeddedResource McpProtocolEmbeddedResource::fromJson(const QJsonObject &obj)
{
    McpProtocolEmbeddedResource resource;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolEmbeddedResource::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG)
            << "McpProtocolEmbeddedResource: field 'type' must be" << McpProtocolEmbeddedResource::type() << "got:" << obj.value("type"_L1).toString();
        return {};
    }
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        resource.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    if (const QJsonValue annotationsValue = obj.value("annotations"_L1); annotationsValue.isObject()) {
        resource.setAnnotations(McpProtocolAnnotations::fromJson(annotationsValue.toObject()));
    }
    if (obj.contains("resource"_L1)) {
        if (auto resourceContents = McpProtocolUtils::embeddedResourceResourceFromJson(obj["resource"_L1])) {
            resource.setResource(std::move(*resourceContents));
        }
    }
    return resource;
}

QJsonObject McpProtocolEmbeddedResource::toJson(const McpProtocolEmbeddedResource &embeddedResource)
{
    QJsonObject obj;
    if (embeddedResource.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*embeddedResource.meta());
    }

    obj["resource"_L1] = McpProtocolUtils::embeddedResourceResourceToJson(embeddedResource.resource());
    obj["type"_L1] = QString::fromLatin1(McpProtocolEmbeddedResource::type());
    if (embeddedResource.annotations().has_value()) {
        obj["annotations"_L1] = McpProtocolAnnotations::toJson(*embeddedResource.annotations());
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

void McpProtocolEmbeddedResource::setResource(McpProtocolUtils::EmbeddedResourceResource newResource)
{
    mResource = std::move(newResource);
}
