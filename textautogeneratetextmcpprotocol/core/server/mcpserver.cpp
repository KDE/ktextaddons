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
    mIdentifier = McpProtocolCommonUtils::generateUUid();
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
    mTransportType = convertTransportTypeFromString(config.readEntry("TransportType", QString()));

    mSettings.load(config);
}

void McpServer::save(KConfigGroup &config) const
{
    config.writeEntry(u"Id"_s, mIdentifier);
    config.writeEntry(u"Name"_s, mName);
    config.writeEntry(u"Enabled"_s, mEnabled);
    config.writeEntry(u"TransportType"_s, convertTransportTypeToString(mTransportType));
    mSettings.save(config);
}

bool McpServer::isValid() const
{
    if (mTransportType == TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown) {
        return false;
    }
    if (mTransportType == TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio) {
        if (mSettings.command().isEmpty()) {
            return false;
        }
    } else {
        if (mSettings.serverUrl().isEmpty()) {
            return false;
        }
    }
    return !mIdentifier.isEmpty() && !mName.isEmpty();
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType McpServer::transportType() const
{
    return mTransportType;
}

void McpServer::setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType newServerType)
{
    mTransportType = newServerType;
}

QString McpServer::transportTypeI18n(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type)
{
    switch (type) {
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse:
        return i18n("Sse");
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio:
        return i18n("Standard IO");
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp:
        return i18n("Streamable HTTP");
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Type not defined. It's a bug";
        return {};
    }
    return {};
}

McpProtocolSettings McpServer::settings() const
{
    return mSettings;
}

void McpServer::setSettings(const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings &newSettings)
{
    mSettings = newSettings;
}

QString McpServer::convertTransportTypeToString(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType type)
{
    switch (type) {
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse:
        return u"sse"_s;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio:
        return u"stdio"_s;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp:
        return u"streamablehttp"_s;
    case TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Type not defined. It's a bug";
        return {};
    }
    return {};
}

TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType McpServer::convertTransportTypeFromString(const QString &str)
{
    if (str == "sse"_L1) {
        return TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Sse;
    } else if (str == "stdio"_L1) {
        return TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Stdio;
    } else if (str == "streamablehttp"_L1) {
        return TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp;
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Type not defined. It's a bug" << str;
        return TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::Unknown;
    }
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpServer &t)
{
    d.space() << "enabled:" << t.enabled();
    d.space() << "name:" << t.name();
    d.space() << "identifier:" << t.identifier();
    d.space() << "serverType:" << t.transportType();

    d.space() << "settings:" << t.settings();
    return d;
}

#include "moc_mcpserver.cpp"
