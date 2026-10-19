/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverutils.h"
#include "common/mcpprotocolcommonutils.h"
#include "common/mcpprotocolkeychainutils.h"

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

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
