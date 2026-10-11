/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

namespace TextAutoGenerateTextMcpProtocolCore
{
class McpServerManager;
}

namespace TextAutoGenerateText
{
namespace TextAutoGenerateMcpToolsUtils
{
[[nodiscard]] bool isServerAlwaysAllowed(TextAutoGenerateTextMcpProtocolCore::McpServerManager *serverManager, const QByteArray &serverIdentifier);
void setServerAlwaysAllowed(TextAutoGenerateTextMcpProtocolCore::McpServerManager *serverManager, const QByteArray &serverIdentifier, bool allowed);
}
}
