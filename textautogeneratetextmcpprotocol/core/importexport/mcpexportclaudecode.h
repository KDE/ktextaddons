/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>

class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpExportClaudeCode
{
public:
    McpExportClaudeCode();
    ~McpExportClaudeCode();

    [[nodiscard]] bool isValid() const;

    void setServer(const McpServer &server);
    void setPath(const QString &path);

    [[nodiscard]] bool exportServer() const;

private:
    [[nodiscard]] QJsonObject exportSseSettings() const;
    [[nodiscard]] QJsonObject exportStdioSettings() const;
    [[nodiscard]] QJsonObject exportStreamableHttpSettings() const;
    [[nodiscard]] QJsonObject exportUrlSettings(const QString &type) const;

    QString mPath;
    TextAutoGenerateTextMcpProtocolCore::McpServer mServer;
};
}
