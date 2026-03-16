/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocol_export.h"
#include <QString>
namespace McpProtocol::McpProtocolUtils
{
enum class Role : uint8_t {
    Unknown,
    Assistant,
    User,
};

[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT QString convertRoleToString(McpProtocolUtils::Role role);

[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOL_EXPORT McpProtocolUtils::Role convertRoleFromString(const QString &str);
};
