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
    switch (level) {
    case McpProtocolUtils::LoggingLevel::Alert:
        return u"alert"_s;
    case McpProtocolUtils::LoggingLevel::Critical:
        return u"critical"_s;
    case McpProtocolUtils::LoggingLevel::Debug:
        return u"debug"_s;
    case McpProtocolUtils::LoggingLevel::Emergency:
        return u"emergency"_s;
    case McpProtocolUtils::LoggingLevel::Error:
        return u"error"_s;
    case McpProtocolUtils::LoggingLevel::Info:
        return u"info"_s;
    case McpProtocolUtils::LoggingLevel::Notice:
        return u"notice"_s;
    case McpProtocolUtils::LoggingLevel::Warning:
        return u"warning"_s;
    case McpProtocolUtils::LoggingLevel::Unknown:
        return {};
    }
    return {};
}

McpProtocol::McpProtocolUtils::LoggingLevel McpProtocol::McpProtocolUtils::convertLoggingLevelFromString(const QString &str)
{
    if (str == "alert"_L1) {
        return McpProtocolUtils::LoggingLevel::Alert;
    } else if (str == "critical"_L1) {
        return McpProtocolUtils::LoggingLevel::Critical;
    } else if (str == "debug"_L1) {
        return McpProtocolUtils::LoggingLevel::Debug;
    } else if (str == "emergency"_L1) {
        return McpProtocolUtils::LoggingLevel::Emergency;
    } else if (str == "error"_L1) {
        return McpProtocolUtils::LoggingLevel::Error;
    } else if (str == "info"_L1) {
        return McpProtocolUtils::LoggingLevel::Info;
    } else if (str == "notice"_L1) {
        return McpProtocolUtils::LoggingLevel::Notice;
    } else if (str == "warning"_L1) {
        return McpProtocolUtils::LoggingLevel::Warning;
    }
    return McpProtocolUtils::LoggingLevel::Unknown;
}
