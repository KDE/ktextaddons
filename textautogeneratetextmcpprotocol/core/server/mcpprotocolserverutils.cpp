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

QByteArray McpProtocolServerUtils::authTokenIdentifier()
{
    return "mcp-server"_ba;
}

void McpProtocolServerUtils::writeAuthToken(const QByteArray &token)
{
    McpProtocolKeychainUtils::writeAuthToken(authTokenIdentifier(), token);
}

void McpProtocolServerUtils::readAuthToken(QObject *context, std::function<void(const QByteArray &)> callback)
{
    McpProtocolKeychainUtils::readAuthToken(authTokenIdentifier(), context, std::move(callback));
}

void McpProtocolServerUtils::removeAuthToken()
{
    McpProtocolKeychainUtils::removeAuthToken(authTokenIdentifier());
}

QUrl McpProtocolServerUtils::defaultServerUrl()
{
    return QUrl(u"http://127.0.0.1:8765/mcp"_s);
}

void McpProtocolServerUtils::loadSettings(QObject *context, std::function<void(const McpProtocolSettings &)> callback)
{
    const auto config = KSharedConfig::openConfig(McpProtocolCommonUtils::serverConfigFileName());
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
    readAuthToken(context, [settings, callback = std::move(callback)](const QByteArray &token) mutable {
        settings.setAuthToken(token);
        callback(settings);
    });
}

void McpProtocolServerUtils::saveSettings(const McpProtocolSettings &settings)
{
    const auto config = KSharedConfig::openConfig(McpProtocolCommonUtils::serverConfigFileName());
    KConfigGroup group(config, QLatin1StringView(myLocalServerGroupName));
    const bool hadAuthToken = group.readEntry(myHasAuthTokenKey, false);
    group.deleteGroup();
    settings.save(group);
    const QByteArray token = settings.authToken();
    if (!token.isEmpty()) {
        group.writeEntry(myHasAuthTokenKey, true);
        writeAuthToken(token);
    } else if (hadAuthToken) {
        removeAuthToken();
    }
    config->sync();
}
