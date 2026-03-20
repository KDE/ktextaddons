/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresourcelink.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolResourceLink::McpProtocolResourceLink() = default;

McpProtocolResourceLink::~McpProtocolResourceLink() = default;

bool McpProtocolResourceLink::operator==(const McpProtocolResourceLink &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolResourceLink &t)
{
    d.space() << "title:" << t.title();
    d.space() << "description:" << t.description();
    return d;
}

McpProtocolResourceLink McpProtocolResourceLink::fromJson(const QJsonObject &obj)
{
    McpProtocolResourceLink prompt;
    if (obj.contains("description"_L1)) {
        prompt.setDescription(obj.value("description"_L1).toString());
    }
    if (obj.contains("title"_L1)) {
        prompt.setTitle(obj.value("title"_L1).toString());
    }
    return prompt;
}

QJsonObject McpProtocolResourceLink::toJson(const McpProtocolResourceLink &boolean)
{
    QJsonObject obj;
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolResourceLink::meta() const
{
    return mMeta;
}

void McpProtocolResourceLink::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = newMeta;
}

std::optional<McpProtocolAnnotations> McpProtocolResourceLink::annotations() const
{
    return mAnnotations;
}

void McpProtocolResourceLink::setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations)
{
    mAnnotations = newAnnotations;
}

std::optional<QString> McpProtocolResourceLink::description() const
{
    return mDescription;
}

void McpProtocolResourceLink::setDescription(std::optional<QString> newDescription)
{
    mDescription = newDescription;
}

std::optional<QList<McpProtocolIcon>> McpProtocolResourceLink::icons() const
{
    return mIcons;
}

void McpProtocolResourceLink::setIcons(std::optional<QList<McpProtocolIcon>> newIcons)
{
    mIcons = newIcons;
}

std::optional<QString> McpProtocolResourceLink::mimeType() const
{
    return mMimeType;
}

void McpProtocolResourceLink::setMimeType(std::optional<QString> newMimeType)
{
    mMimeType = newMimeType;
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
