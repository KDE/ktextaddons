/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QList>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpImportClaudeCode
{
public:
    McpImportClaudeCode();
    ~McpImportClaudeCode();

    [[nodiscard]] QString path() const;
    void setPath(const QString &newPath);

    [[nodiscard]] bool importServer();

    [[nodiscard]] QList<McpServer> mcpServers() const;

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void importStreamableHttp(const QJsonObject &obj, McpServer &server) const;
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void importStdio(const QJsonObject &obj, McpServer &server) const;
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void importSse(const QJsonObject &obj, McpServer &server) const;
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT McpProtocolSettings importUrlSettings(const QJsonObject &obj) const;
    QString mPath;
    QList<McpServer> mMcpServers;
};
}
