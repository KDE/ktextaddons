/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverutils.h"
#include "common/mcpprotocolcommonutils.h"
#include "common/mcpprotocolkeychainutils.h"
#include "common/mcpprotocolsettings.h"
#include <KConfigGroup>
#include <KSharedConfig>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

namespace
{
const char myLocalServerGroupName[] = "Local Server";
const char myHasAuthTokenKey[] = "HasAuthToken";
}

QByteArray McpProtocolServerUtils::generateAuthToken()
{
    return McpProtocolCommonUtils::generateAuthToken();
}

QByteArray McpProtocolServerUtils::authTokenIdentifier(const QString &configName)
{
    // Keep the historical identifier for the default server
    if (configName.isEmpty() || configName == McpProtocolCommonUtils::serverConfigFileName()) {
        return "mcp-server"_ba;
    }
    return "mcp-server-"_ba + configName.toUtf8();
}

void McpProtocolServerUtils::writeAuthToken(const QByteArray &token, const QString &configName)
{
    McpProtocolKeychainUtils::writeAuthToken(authTokenIdentifier(configName), token);
}

void McpProtocolServerUtils::readAuthToken(QObject *context, std::function<void(const QByteArray &)> callback, const QString &configName)
{
    McpProtocolKeychainUtils::readAuthToken(authTokenIdentifier(configName), context, std::move(callback));
}

void McpProtocolServerUtils::removeAuthToken(const QString &configName)
{
    McpProtocolKeychainUtils::removeAuthToken(authTokenIdentifier(configName));
}

QUrl McpProtocolServerUtils::defaultServerUrl()
{
    return QUrl(u"http://127.0.0.1:8765/mcp"_s);
}

void McpProtocolServerUtils::loadSettings(QObject *context, std::function<void(const McpProtocolSettings &)> callback)
{
    loadSettings(KSharedConfig::openConfig(McpProtocolCommonUtils::serverConfigFileName()), context, std::move(callback));
}

void McpProtocolServerUtils::loadSettings(const KSharedConfig::Ptr &config, QObject *context, std::function<void(const McpProtocolSettings &)> callback)
{
    const KConfigGroup group(config, QLatin1StringView(myLocalServerGroupName));
    McpProtocolSettings settings;
    settings.load(group);
    if (settings.serverUrl().isEmpty()) {
        settings.setServerUrl(defaultServerUrl());
    }
    if (!group.readEntry(myHasAuthTokenKey, false)) {
        callback(settings);
        return;
    }
    readAuthToken(
        context,
        [settings, callback = std::move(callback)](const QByteArray &token) mutable {
            settings.setAuthToken(token);
            callback(settings);
        },
        config->name());
}

void McpProtocolServerUtils::saveSettings(const KSharedConfig::Ptr &config, const McpProtocolSettings &settings)
{
    KConfigGroup group(config, QLatin1StringView(myLocalServerGroupName));
    const bool hadAuthToken = group.readEntry(myHasAuthTokenKey, false);
    group.deleteGroup();
    settings.save(group);
    const QByteArray token = settings.authToken();
    if (!token.isEmpty()) {
        group.writeEntry(myHasAuthTokenKey, true);
        writeAuthToken(token, config->name());
    } else if (hadAuthToken) {
        removeAuthToken(config->name());
    }
    config->sync();
}

void McpProtocolServerUtils::saveSettings(const McpProtocolSettings &settings)
{
    saveSettings(KSharedConfig::openConfig(McpProtocolCommonUtils::serverConfigFileName()), settings);
}
