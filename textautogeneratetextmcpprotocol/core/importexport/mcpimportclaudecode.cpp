/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpimportclaudecode.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpImportClaudeCode::McpImportClaudeCode() = default;

McpImportClaudeCode::~McpImportClaudeCode() = default;

QString McpImportClaudeCode::path() const
{
    return mPath;
}

void McpImportClaudeCode::setPath(const QString &newPath)
{
    mPath = newPath;
}

bool McpImportClaudeCode::importServer()
{
    mMcpServers.clear();
    if (mPath.isEmpty()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "mPath is empty";
        return false;
    }
    // TODO
    return false;
}

QList<McpServer> McpImportClaudeCode::mcpServers() const
{
    return mMcpServers;
}
