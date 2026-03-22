/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresourcetemplate.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolResourceTemplate::McpProtocolResourceTemplate() = default;

McpProtocolResourceTemplate::~McpProtocolResourceTemplate() = default;

bool McpProtocolResourceTemplate::operator==(const McpProtocolResourceTemplate &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResourceTemplate &t)
{
    return d;
}

McpProtocolResourceTemplate McpProtocolResourceTemplate::fromJson(const QJsonObject &obj)
{
    McpProtocolResourceTemplate prompt;
    // TODO
    return prompt;
}

QJsonObject McpProtocolResourceTemplate::toJson(const McpProtocolResourceTemplate &boolean)
{
    QJsonObject obj;
    obj["name"_L1] = boolean.name();
    obj["uriTemplate"_L1] = boolean.uriTemplate();
    if (boolean.meta().has_value()) {
        obj.insert("_meta"_L1, McpProtocolMeta::toJson(*boolean.meta()));
    }
    if (boolean.annotations().has_value()) {
        obj.insert("annotations"_L1, McpProtocolAnnotations::toJson(*boolean.annotations()));
    }
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
    if (boolean.mimeType().has_value())
        obj.insert("mimeType"_L1, *boolean.mimeType());
    if (boolean.title().has_value()) {
        obj.insert("title"_L1, *boolean.title());
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolResourceTemplate::meta() const
{
    return mMeta;
}

void McpProtocolResourceTemplate::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<McpProtocolAnnotations> McpProtocolResourceTemplate::annotations() const
{
    return mAnnotations;
}

void McpProtocolResourceTemplate::setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations)
{
    mAnnotations = std::move(newAnnotations);
}

std::optional<QString> McpProtocolResourceTemplate::description() const
{
    return mDescription;
}

void McpProtocolResourceTemplate::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<QList<McpProtocolIcon>> McpProtocolResourceTemplate::icons() const
{
    return mIcons;
}

void McpProtocolResourceTemplate::setIcons(std::optional<QList<McpProtocolIcon>> newIcons)
{
    mIcons = std::move(newIcons);
}

std::optional<QString> McpProtocolResourceTemplate::mimeType() const
{
    return mMimeType;
}

void McpProtocolResourceTemplate::setMimeType(std::optional<QString> newMimeType)
{
    mMimeType = std::move(newMimeType);
}

QString McpProtocolResourceTemplate::name() const
{
    return mName;
}

void McpProtocolResourceTemplate::setName(const QString &newName)
{
    mName = newName;
}

std::optional<QString> McpProtocolResourceTemplate::title() const
{
    return mTitle;
}

void McpProtocolResourceTemplate::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}

QString McpProtocolResourceTemplate::uriTemplate() const
{
    return mUriTemplate;
}

void McpProtocolResourceTemplate::setUriTemplate(const QString &newUriTemplate)
{
    mUriTemplate = newUriTemplate;
}
