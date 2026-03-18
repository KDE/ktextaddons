/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolimplementation.h"
#include <QDebug>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolImplementation::McpProtocolImplementation() = default;

McpProtocolImplementation::~McpProtocolImplementation() = default;

bool McpProtocolImplementation::operator==(const McpProtocolImplementation &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolImplementation &t)
{
    return d;
}

McpProtocolImplementation McpProtocolImplementation::fromJson(const QJsonObject &obj)
{
    McpProtocolImplementation text;
    return text;
}

QJsonObject McpProtocolImplementation::toJson(const McpProtocolImplementation &text)
{
    return {};
}

std::optional<QString> McpProtocolImplementation::description() const
{
    return mDescription;
}

void McpProtocolImplementation::setDescription(std::optional<QString> newDescription)
{
    mDescription = std::move(newDescription);
}

std::optional<QList<McpProtocolIcon>> McpProtocolImplementation::icons() const
{
    return mIcons;
}

void McpProtocolImplementation::setIcons(std::optional<QList<McpProtocolIcon>> newIcons)
{
    mIcons = std::move(newIcons);
}

QString McpProtocolImplementation::name() const
{
    return mName;
}

void McpProtocolImplementation::setName(const QString &newName)
{
    mName = std::move(newName);
}

std::optional<QString> McpProtocolImplementation::title() const
{
    return mTitle;
}

void McpProtocolImplementation::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}

QString McpProtocolImplementation::version() const
{
    return mVersion;
}

void McpProtocolImplementation::setVersion(const QString &newVersion)
{
    mVersion = newVersion;
}

std::optional<QString> McpProtocolImplementation::websiteUrl() const
{
    return mWebsiteUrl;
}

void McpProtocolImplementation::setWebsiteUrl(std::optional<QString> newWebsiteUrl)
{
    mWebsiteUrl = std::move(newWebsiteUrl);
}
