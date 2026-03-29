/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolimplementation.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolImplementation::McpProtocolImplementation() = default;

McpProtocolImplementation::~McpProtocolImplementation() = default;

bool McpProtocolImplementation::operator==(const McpProtocolImplementation &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolImplementation &t)
{
    d.space() << "version:" << t.version();
    d.space() << "name:" << t.name();
    d.space() << "title:" << t.title();
    d.space() << "description:" << t.description();
    d.space() << "icons:" << t.icons();
    d.space() << "websiteUrl:" << t.websiteUrl();
    return d;
}

McpProtocolImplementation McpProtocolImplementation::fromJson(const QJsonObject &obj)
{
    McpProtocolImplementation impl;
    if (obj.contains("description"_L1)) {
        impl.setDescription(obj.value("description"_L1).toString());
    }
    if (obj.contains("icons"_L1) && obj["icons"_L1].isArray()) {
        const QJsonArray arr = obj["icons"_L1].toArray();
        QList<McpProtocolIcon> icons;
        for (const QJsonValue &v : arr) {
            icons.append(McpProtocolIcon::fromJson(v.toObject()));
        }
        impl.setIcons(icons);
    }
    impl.setName(obj.value("name"_L1).toString());
    if (obj.contains("title"_L1)) {
        impl.setTitle(obj.value("title"_L1).toString());
    }
    impl.setVersion(obj.value("version"_L1).toString());
    if (obj.contains("websiteUrl"_L1)) {
        impl.setWebsiteUrl(obj.value("websiteUrl"_L1).toString());
    }
    return impl;
}

QJsonObject McpProtocolImplementation::toJson(const McpProtocolImplementation &impl)
{
    QJsonObject obj;
    obj["name"_L1] = impl.name();
    obj["version"_L1] = impl.version();
    if (impl.description().has_value()) {
        obj["description"_L1] = *impl.description();
    }
    if (impl.icons().has_value()) {
        QJsonArray arr_icons;
        const auto icons = *impl.icons();
        for (const auto &v : icons) {
            arr_icons.append(McpProtocolIcon::toJson(v));
        }
        obj["icons"_L1] = arr_icons;
    }
    if (impl.title().has_value()) {
        obj["title"_L1] = *impl.title();
    }
    if (impl.websiteUrl().has_value()) {
        obj["websiteUrl"_L1] = *impl.websiteUrl();
    }
    return obj;
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
    mName = newName;
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
