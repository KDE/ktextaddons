/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresource.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QJsonArray>
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

    return prompt;
}

QJsonObject McpProtocolResource::toJson(const McpProtocolResource &boolean)
{
    QJsonObject obj;
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
