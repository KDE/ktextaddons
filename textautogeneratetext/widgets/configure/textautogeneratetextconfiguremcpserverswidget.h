/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpServerModel;
}
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class McpServerWidget;
}
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextConfigureMcpServersWidget
 * \brief Configure MCP servers which provide tools to LLM.
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextConfigureMcpServersWidget
 * Changes are applied with save().
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextConfigureMcpServersWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextConfigureMcpServersWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextConfigureMcpServersWidget() override;

    /*!
     * Apply changes and save servers
     */
    void save();
    /*!
     * Load current servers (changes are discarded)
     */
    void load();

Q_SIGNALS:
    /*!
     */
    void settingsChanged();

private:
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    // Servers are modified in a copy: changes are applied with save()
    TextAutoGenerateTextMcpProtocolCore::McpServerModel *const mMcpServerModel;
    TextAutoGenerateTextMcpProtocolWidgets::McpServerWidget *const mMcpServerWidget;
};
}
