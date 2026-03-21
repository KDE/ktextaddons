/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocol_export.h"
#include <QString>
namespace McpProtocol
{
class McpProtocolTextResourceContents;
class McpProtocolBlobResourceContents;
}
namespace McpProtocol::McpProtocolUtils
{
using RequestId = std::variant<QString, int>;

using ProgressToken = std::variant<QString, int>;

using EmbeddedResourceResource = std::variant<McpProtocolTextResourceContents, McpProtocolBlobResourceContents>;

using Cursor = QString;

enum class Role : uint8_t {
    Unknown,
    Assistant,
    User,
};

enum class LoggingLevel : uint8_t {
    Alert,
    Critical,
    Debug,
    Emergency,
    Error,
    Info,
    Notice,
    Warning,
    Unknown,
};

enum class TaskStatus : uint8_t {
    Cancelled,
    Completed,
    Failed,
    InputRequired,
    Working,
    Unknown,
};

[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QString convertRoleToString(McpProtocolUtils::Role role);
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolUtils::Role convertRoleFromString(const QString &str);

[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QString convertLoggingLevelToString(McpProtocolUtils::LoggingLevel level);
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolUtils::LoggingLevel convertLoggingLevelFromString(const QString &str);

[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QString convertTaskStatusToString(McpProtocolUtils::TaskStatus level);
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolUtils::TaskStatus convertTaskStatusFromString(const QString &str);
};
