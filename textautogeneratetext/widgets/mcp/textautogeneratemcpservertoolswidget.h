/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
class QCheckBox;
class QLabel;
class QLineEdit;
class QListWidget;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
/*!
 * Select tools of a MCP server which can be used (white list).
 * Tools are listed when server is saved, otherwise only allowed tools are shown.
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateMcpServerToolsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMcpServerToolsWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateMcpServerToolsWidget() override;

    void setServer(const TextAutoGenerateTextMcpProtocolCore::McpServer &server);
    /*!
     * Server with selected allowed tools
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpServer server() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateTools();
    TEXTAUTOGENERATETEXT_NO_EXPORT void updateStatus();
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotSearchChanged(const QString &str);
    TEXTAUTOGENERATETEXT_NO_EXPORT void setAllChecked(bool checked);
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT bool canListTools() const;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    QCheckBox *const mFilterToolsCheckBox;
    QLineEdit *const mSearchLineEdit;
    QListWidget *const mToolsListWidget;
    QLabel *const mStatusLabel;
    TextAutoGenerateTextMcpProtocolCore::McpServer mServer;
    // Tools checked by user, kept when list of tools is updated
    QStringList mAllowedTools;
};
}
