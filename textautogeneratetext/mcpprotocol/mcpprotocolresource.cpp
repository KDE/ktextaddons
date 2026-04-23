/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresource.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolResource::McpProtocolResource() = default;

McpProtocolResource::~McpProtocolResource() = default;

bool McpProtocolResource::operator==(const McpProtocolResource &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResource &t)
{
    d.space() << "uri:" << t.uri();
    d.space() << "title:" << t.title();
    d.space() << "size:" << t.size();
    d.space() << "name:" << t.name();
    d.space() << "mimeType:" << t.mimeType();
    d.space() << "icons:" << t.icons();
    d.space() << "description:" << t.description();
    d.space() << "annotations:" << t.annotations();
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolResource McpProtocolResource::fromJson(const QJsonObject &obj)
{
    McpProtocolResource prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        const QJsonObject mapObj__meta = obj["_meta"_L1].toObject();
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("annotations"_L1) && obj["annotations"_L1].isObject()) {
        prompt.setAnnotations(McpProtocolAnnotations::fromJson(obj["annotations"_L1].toObject()));
    }
    if (obj.contains("description"_L1)) {
        prompt.setDescription(obj.value("description"_L1).toString());
    }
    if (obj.contains("icons"_L1) && obj["icons"_L1].isArray()) {
        const QJsonArray arr = obj["icons"_L1].toArray();
        QList<McpProtocolIcon> list_icons;
        for (const QJsonValue &v : arr) {
            list_icons.append(McpProtocolIcon::fromJson(v.toObject()));
        }
        prompt.setIcons(list_icons);
    }
    if (obj.contains("mimeType"_L1)) {
        prompt.setMimeType(obj.value("mimeType"_L1).toString());
    }
    prompt.setName(obj.value("name"_L1).toString());
    if (obj.contains("size"_L1)) {
        prompt.setSize(obj.value("size"_L1).toInt());
    }
    if (obj.contains("title"_L1)) {
        prompt.setTitle(obj.value("title"_L1).toString());
    }
    prompt.setUri(obj.value("uri"_L1).toString());

    return prompt;
}

QJsonObject McpProtocolResource::toJson(const McpProtocolResource &boolean)
{
    QJsonObject obj;
    obj["name"_L1] = boolean.name();
    obj["uri"_L1] = boolean.uri();
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.annotations().has_value())
        obj.insert("annotations"_L1, McpProtocolAnnotations::toJson(*boolean.annotations()));
    if (boolean.description().has_value()) {
        obj.insert("description"_L1, *boolean.description());
    }
    if (boolean.icons().has_value()) {
        QJsonArray arr_icons;
        const auto icons = *boolean.icons();
        for (const auto &v : icons) {
            arr_icons.append(McpProtocolIcon::toJson(v));
        }
        obj.insert("icons"_L1, arr_icons);
    }
    if (boolean.mimeType().has_value()) {
        obj.insert("mimeType"_L1, *boolean.mimeType());
    }
    if (boolean.size().has_value()) {
        obj.insert("size"_L1, *boolean.size());
    }
    if (boolean.title().has_value()) {
        obj.insert("title"_L1, *boolean.title());
    }
    return obj;
}

QString McpProtocolResource::uri() const
{
    return mUri;
}

void McpProtocolResource::setUri(const QString &newUri)
{
    mUri = newUri;
}

std::optional<QString> McpProtocolResource::title() const
{
    return mTitle;
}

void McpProtocolResource::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}

std::optional<int> McpProtocolResource::size() const
{
    return mSize;
}

void McpProtocolResource::setSize(std::optional<int> newSize)
{
    mSize = newSize;
}

QString McpProtocolResource::name() const
{
    return mName;
}

void McpProtocolResource::setName(const QString &newName)
{
    mName = newName;
}

std::optional<QString> McpProtocolResource::mimeType() const
{
    return mMimeType;
}

void McpProtocolResource::setMimeType(std::optional<QString> newMimeType)
{
    mMimeType = std::move(newMimeType);
}

std::optional<QList<McpProtocolIcon>> McpProtocolResource::icons() const
{
    return mIcons;
}

void McpProtocolResource::setIcons(std::optional<QList<McpProtocolIcon>> newIcons)
{
    mIcons = std::move(newIcons);
}

std::optional<QString> McpProtocolResource::description() const
{
    return mDescription;
}

void McpProtocolResource::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<McpProtocolAnnotations> McpProtocolResource::annotations() const
{
    return mAnnotations;
}

void McpProtocolResource::setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations)
{
    mAnnotations = std::move(newAnnotations);
}

std::optional<McpProtocolMeta> McpProtocolResource::meta() const
{
    return mMeta;
}

void McpProtocolResource::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}
