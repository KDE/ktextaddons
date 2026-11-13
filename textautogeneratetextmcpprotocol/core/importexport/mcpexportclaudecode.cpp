/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpexportclaudecode.h"
#include <QSaveFile>

using namespace TextAutoGenerateTextMcpProtocolCore;
McpExportClaudeCode::McpExportClaudeCode() = default;

McpExportClaudeCode::~McpExportClaudeCode() = default;

bool McpExportClaudeCode::isValid() const
{
    return mServer.isValid() && !mPath.isEmpty();
}

void McpExportClaudeCode::setServer(const McpServer &server)
{
    mServer = server;
}

void McpExportClaudeCode::setPath(const QString &path)
{
    mPath = path;
}

bool McpExportClaudeCode::exportServer() const
{
    // TODO
    return false;
}
