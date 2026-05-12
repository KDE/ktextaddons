/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpserver.h"
#include "common/mcpprotocolutils.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <KConfigGroup>
#include <KLocalizedString>

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
    mServerType = convertServerTypeFromString(config.readEntry("Type", QString()));

    mServerUrl = config.readEntry("ServerUrl", QUrl());
    mCommand = config.readEntry("Command", QString());
    mArguments = config.readEntry("Arguments", QString());
    // TODO mEnvironments
}

void McpServer::save(KConfigGroup &config) const
{
    config.writeEntry(u"Id"_s, mIdentifier);
    config.writeEntry(u"Name"_s, mName);
    config.writeEntry(u"Enabled"_s, mEnabled);
    config.writeEntry(u"Type"_s, convertServerTypeToString(mServerType));
    if (mServerType == ServerType::Stdio) {
        config.writeEntry(u"Command"_s, mCommand);
        config.writeEntry(u"Arguments"_s, mArguments);
    } else {
        config.writeEntry(u"ServerUrl"_s, mServerUrl);
    }
    // TODO mEnvironments
}

bool McpServer::isValid() const
{
    return !mIdentifier.isEmpty() && !mName.isEmpty() && mServerType != ServerType::Unknown;
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

QString McpServer::arguments() const
{
    return mArguments;
}

void McpServer::setArguments(const QString &newArguments)
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

QString McpServer::serverTypeI18n(ServerType type)
{
    switch (type) {
    case ServerType::Sse:
        return i18n("Sse");
    case ServerType::Stdio:
        return i18n("Standard IO");
    case ServerType::StreamableHttp:
        return i18n("Streamable HTTP");
    case ServerType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Type not defined. It's a bug";
        return {};
    }
    return {};
}

QString McpServer::convertServerTypeToString(ServerType type)
{
    switch (type) {
    case ServerType::Sse:
        return u"sse"_s;
    case ServerType::Stdio:
        return u"stdio"_s;
    case ServerType::StreamableHttp:
        return u"streamablehttp"_s;
    case ServerType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Type not defined. It's a bug";
        return {};
    }
    return {};
}

TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType McpServer::convertServerTypeFromString(const QString &str)
{
    if (str == "sse"_L1) {
        return TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Sse;
    } else if (str == "stdio"_L1) {
        return TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Stdio;
    } else if (str == "streamablehttp"_L1) {
        return TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::StreamableHttp;
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Type not defined. It's a bug" << str;
        return TextAutoGenerateTextMcpProtocolCore::McpServer::ServerType::Unknown;
    }
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
