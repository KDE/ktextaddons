/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresourcelink.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolResourceLink::McpProtocolResourceLink() = default;

McpProtocolResourceLink::~McpProtocolResourceLink() = default;

bool McpProtocolResourceLink::operator==(const McpProtocolResourceLink &other) const = default;

QByteArray McpProtocolResourceLink::type()
{
    return QByteArrayLiteral("resource_link");
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceLink &t)
{
    d.space() << "title:" << t.title();
    d.space() << "description:" << t.description();
    d.space() << "meta:" << t.meta();
    d.space() << "annotations:" << t.annotations();
    d.space() << "icons:" << t.icons();
    d.space() << "mimeType:" << t.mimeType();
    d.space() << "name:" << t.name();
    d.space() << "size:" << t.size();
    d.space() << "uri:" << t.uri();
    return d;
}

McpProtocolResourceLink McpProtocolResourceLink::fromJson(const QJsonObject &obj)
{
    McpProtocolResourceLink prompt;
    if (obj.value("type"_L1).toString().toLatin1() != McpProtocolResourceLink::type()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'type' must be 'resource_link', got: " << obj.value("type"_L1).toString();
        return {};
    }
    if (obj.contains("description"_L1)) {
        prompt.setDescription(obj.value("description"_L1).toString());
    }
    if (obj.contains("title"_L1)) {
        prompt.setTitle(obj.value("title"_L1).toString());
    }

    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
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

QJsonObject McpProtocolResourceLink::toJson(const McpProtocolResourceLink &boolean)
{
    QJsonObject obj;
    obj["name"_L1] = boolean.name();
    obj["type"_L1] = QString::fromLatin1(boolean.type());
    obj["uri"_L1] = boolean.uri();
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    if (boolean.annotations().has_value()) {
        obj["annotations"_L1] = McpProtocolAnnotations::toJson(*boolean.annotations());
    }
    if (boolean.description().has_value()) {
        obj["description"_L1] = *boolean.description();
    }
    if (boolean.icons().has_value()) {
        QJsonArray arr_icons;
        const auto icons = *boolean.icons();
        for (const auto &v : icons) {
            arr_icons.append(McpProtocolIcon::toJson(v));
        }
        obj["icons"_L1] = arr_icons;
    }
    if (boolean.mimeType().has_value()) {
        obj["mimeType"_L1] = *boolean.mimeType();
    }
    if (boolean.size().has_value()) {
        obj["size"_L1] = *boolean.size();
    }
    if (boolean.title().has_value()) {
        obj["title"_L1] = *boolean.title();
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolResourceLink::meta() const
{
    return mMeta;
}

void McpProtocolResourceLink::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolAnnotations> McpProtocolResourceLink::annotations() const
{
    return mAnnotations;
}

void McpProtocolResourceLink::setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations)
{
    mAnnotations = std::move(newAnnotations);
}

std::optional<QString> McpProtocolResourceLink::description() const
{
    return mDescription;
}

void McpProtocolResourceLink::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<QList<McpProtocolIcon>> McpProtocolResourceLink::icons() const
{
    return mIcons;
}

void McpProtocolResourceLink::setIcons(std::optional<QList<McpProtocolIcon>> newIcons)
{
    mIcons = std::move(newIcons);
}

std::optional<QString> McpProtocolResourceLink::mimeType() const
{
    return mMimeType;
}

void McpProtocolResourceLink::setMimeType(std::optional<QString> newMimeType)
{
    mMimeType = std::move(newMimeType);
}

QString McpProtocolResourceLink::name() const
{
    return mName;
}

void McpProtocolResourceLink::setName(const QString &newName)
{
    mName = newName;
}

std::optional<int> McpProtocolResourceLink::size() const
{
    return mSize;
}

void McpProtocolResourceLink::setSize(std::optional<int> newSize)
{
    mSize = newSize;
}

std::optional<QString> McpProtocolResourceLink::title() const
{
    return mTitle;
}

void McpProtocolResourceLink::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}

QString McpProtocolResourceLink::uri() const
{
    return mUri;
}

void McpProtocolResourceLink::setUri(const QString &newUri)
{
    mUri = newUri;
}
