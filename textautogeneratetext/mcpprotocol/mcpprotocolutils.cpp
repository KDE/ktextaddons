/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolutils.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
QString McpProtocol::McpProtocolUtils::convertRoleToString(McpProtocolUtils::Role role)
{
    switch (role) {
    case McpProtocolUtils::Role::Assistant:
        return u"assistant"_s;
    case McpProtocolUtils::Role::User:
        return u"user"_s;
    case McpProtocolUtils::Role::Unknown:
        return {};
    }
    return {};
}

McpProtocol::McpProtocolUtils::Role McpProtocol::McpProtocolUtils::convertRoleFromString(const QString &str)
{
    if (str == "assistant"_L1) {
        return McpProtocolUtils::Role::Assistant;
    } else if (str == "user"_L1) {
        return McpProtocolUtils::Role::User;
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Unknown role name " << str;
    return McpProtocolUtils::Role::Unknown;
}

QString McpProtocol::McpProtocolUtils::convertLoggingLevelToString(McpProtocolUtils::LoggingLevel level)
{
    // TODO
    switch (level) {
    case McpProtocolUtils::LoggingLevel::Alert:
    case McpProtocolUtils::LoggingLevel::Critical:
    case McpProtocolUtils::LoggingLevel::Debug:
    case McpProtocolUtils::LoggingLevel::Emergency:
    case McpProtocolUtils::LoggingLevel::Error:
    case McpProtocolUtils::LoggingLevel::Info:
    case McpProtocolUtils::LoggingLevel::Notice:
    case McpProtocolUtils::LoggingLevel::Warning:
        return u"assistant"_s;
    }
    return {};
}

McpProtocol::McpProtocolUtils::LoggingLevel McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(const QString &str)
{
    return {};
}
