/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserver.h"
#include "common/mcpprotocolutils.h"
#include <QDebug>
using namespace TextAutoGenerateTextMcpProtocolCore;
using namespace Qt::Literals::StringLiterals;
McpServer::McpServer() = default;

McpServer::~McpServer() = default;

void McpServer::createUniqueIdentifier()
{
    mIdentifier = McpProtocolUtils::generateUUid();
}

QUrl McpServer::serverUrl() const
{
    return mServerUrl;
}

void McpServer::setServerUrl(const QUrl &newServerUrl)
{
    mServerUrl = newServerUrl;
}

bool McpServer::enabled() const
{
    return mEnabled;
}

void McpServer::setEnabled(bool newEnabled)
{
    mEnabled = newEnabled;
}

QString McpServer::name() const
{
    return mName;
}

void McpServer::setName(const QString &newName)
{
    mName = newName;
}

QByteArray McpServer::identifier() const
{
    return mIdentifier;
}

void McpServer::setIdentifier(const QByteArray &newIdentifier)
{
    mIdentifier = newIdentifier;
}

void McpServer::load(const KConfigGroup &config)
{
    mEnabled = config.readEntry("Enabled", true);
    mName = config.readEntry("Name", QString());
    mIdentifier = config.readEntry("Id", QByteArray());
    mServerUrl = config.readEntry("ServerUrl", QUrl());
    // TODO add server type
}

void McpServer::save(KConfigGroup &config) const
{
    config.writeEntry(u"ServerUrl"_s, mServerUrl);
    config.writeEntry(u"Id"_s, mIdentifier);
    config.writeEntry(u"Name"_s, mName);
    config.writeEntry(u"Enabled"_s, mEnabled);
    // TODO add server type
}

bool McpServer::isValid() const
{
    return !mIdentifier.isEmpty() && !mName.isEmpty() && !mServerUrl.isEmpty() && mServerType != ServerType::Unknown;
}

McpServer::ServerType McpServer::serverType() const
{
    return mServerType;
}

void McpServer::setServerType(ServerType newServerType)
{
    mServerType = newServerType;
}

QString McpServer::command() const
{
    return mCommand;
}

void McpServer::setCommand(const QString &newCommand)
{
    mCommand = newCommand;
}

QStringList McpServer::arguments() const
{
    return mArguments;
}

void McpServer::setArguments(const QStringList &newArguments)
{
    mArguments = newArguments;
}

QMap<QString, QString> McpServer::environments() const
{
    return mEnvironments;
}

void McpServer::setEnvironments(const QMap<QString, QString> &newEnvironments)
{
    mEnvironments = newEnvironments;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpServer &t)
{
    d.space() << "url:" << t.serverUrl();
    d.space() << "enabled:" << t.enabled();
    d.space() << "name:" << t.name();
    d.space() << "identifier:" << t.identifier();
    d.space() << "serverType:" << t.serverType();
    d.space() << "command:" << t.command();
    d.space() << "environments:" << t.environments();
    return d;
}

#include "moc_mcpserver.cpp"
