/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>

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
    QString mPath;
    TextAutoGenerateTextMcpProtocolCore::McpServer mServer;
};
}
