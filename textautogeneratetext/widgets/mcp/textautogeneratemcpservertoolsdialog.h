/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_private_export.h"
#include <QDialog>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>

namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateMcpServerToolsWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateMcpServerToolsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMcpServerToolsDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateMcpServerToolsDialog() override;

    void setServer(const TextAutoGenerateTextMcpProtocolCore::McpServer &server);
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpServer server() const;

private:
    TextAutoGenerateMcpServerToolsWidget *const mTextAutoGenerateMcpServerToolsWidget;
};
}
