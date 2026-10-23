/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpregistryserverinfo.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace TextAutoGenerateTextMcpProtocolCore;
using namespace Qt::Literals::StringLiterals;
McpRegistryServerInfo::McpRegistryServerInfo() = default;

McpRegistryServerInfo::~McpRegistryServerInfo() = default;

McpRegistryServerInfo McpRegistryServerInfo::fromJson(const QJsonObject &obj)
{
    qDebug() << " obj " << obj;
    McpRegistryServerInfo info;
    info.mName = obj["name"_L1].toString();
    info.mTitle = obj["title"_L1].toString();
    info.mDescription = obj["description"_L1].toString();
    info.mVersion = obj["version"_L1].toString();
    info.mRepositoryUrl = obj["repository"_L1].toObject()["url"_L1].toString();
    info.mWebsiteUrl = obj["websiteUrl"_L1].toString();

    const QJsonArray packagesArray = obj["packages"_L1].toArray();
    for (const auto &value : packagesArray) {
        const QJsonObject packageObj = value.toObject();
        Package package;
        package.registryType = packageObj["registryType"_L1].toString();
        package.identifier = packageObj["identifier"_L1].toString();
        package.version = packageObj["version"_L1].toString();
        package.runtimeHint = packageObj["runtimeHint"_L1].toString();
        package.transportType = packageObj["transport"_L1].toObject()["type"_L1].toString();
        const QJsonArray envArray = packageObj["environmentVariables"_L1].toArray();
        for (const auto &envValue : envArray) {
            const QJsonObject envObj = envValue.toObject();
            EnvironmentVariable env;
            env.name = envObj["name"_L1].toString();
            env.description = envObj["description"_L1].toString();
            env.isRequired = envObj["isRequired"_L1].toBool();
            env.isSecret = envObj["isSecret"_L1].toBool();
            package.environmentVariables.append(std::move(env));
        }
        info.mPackages.append(std::move(package));
    }

    const QJsonArray remotesArray = obj["remotes"_L1].toArray();
    for (const auto &value : remotesArray) {
        const QJsonObject remoteObj = value.toObject();
        info.mRemotes.append({remoteObj["type"_L1].toString(), remoteObj["url"_L1].toString()});
    }
    return info;
}

QList<McpRegistryServerInfo> McpRegistryServerInfo::parseServerList(const QJsonObject &obj, QString &nextCursor)
{
    QList<McpRegistryServerInfo> list;
    const QJsonArray serversArray = obj["servers"_L1].toArray();
    list.reserve(serversArray.count());
    for (const auto &value : serversArray) {
        const McpRegistryServerInfo info = fromJson(value.toObject()["server"_L1].toObject());
        if (info.isValid()) {
            list.append(info);
        }
    }
    nextCursor = obj["metadata"_L1].toObject()["nextCursor"_L1].toString();
    return list;
}

bool McpRegistryServerInfo::isValid() const
{
    return !mName.isEmpty();
}

QString McpRegistryServerInfo::name() const
{
    return mName;
}

void McpRegistryServerInfo::setName(const QString &newName)
{
    mName = newName;
}

QString McpRegistryServerInfo::title() const
{
    return mTitle;
}

void McpRegistryServerInfo::setTitle(const QString &newTitle)
{
    mTitle = newTitle;
}

QString McpRegistryServerInfo::displayName() const
{
    return mTitle.isEmpty() ? mName : mTitle;
}

QString McpRegistryServerInfo::description() const
{
    return mDescription;
}

void McpRegistryServerInfo::setDescription(const QString &newDescription)
{
    mDescription = newDescription;
}

QString McpRegistryServerInfo::version() const
{
    return mVersion;
}

void McpRegistryServerInfo::setVersion(const QString &newVersion)
{
    mVersion = newVersion;
}

QString McpRegistryServerInfo::repositoryUrl() const
{
    return mRepositoryUrl;
}

void McpRegistryServerInfo::setRepositoryUrl(const QString &newRepositoryUrl)
{
    mRepositoryUrl = newRepositoryUrl;
}

QString McpRegistryServerInfo::websiteUrl() const
{
    return mWebsiteUrl;
}

void McpRegistryServerInfo::setWebsiteUrl(const QString &newWebsiteUrl)
{
    mWebsiteUrl = newWebsiteUrl;
}

QList<McpRegistryServerInfo::Package> McpRegistryServerInfo::packages() const
{
    return mPackages;
}

void McpRegistryServerInfo::setPackages(const QList<Package> &newPackages)
{
    mPackages = newPackages;
}

QList<McpRegistryServerInfo::Remote> McpRegistryServerInfo::remotes() const
{
    return mRemotes;
}

void McpRegistryServerInfo::setRemotes(const QList<Remote> &newRemotes)
{
    mRemotes = newRemotes;
}

QList<McpRegistryServerInfo::Icon> McpRegistryServerInfo::icons() const
{
    return mIcons;
}

void McpRegistryServerInfo::setIcons(const QList<Icon> &newIcons)
{
    mIcons = newIcons;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpRegistryServerInfo &t)
{
    d.space() << "name:" << t.name();
    d.space() << "title:" << t.title();
    d.space() << "description:" << t.description();
    d.space() << "version:" << t.version();
    d.space() << "repositoryUrl:" << t.repositoryUrl();
    d.space() << "websiteUrl:" << t.websiteUrl();
    d.space() << "packages:" << t.packages().count();
    d.space() << "remotes:" << t.remotes().count();
    return d;
}
