/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
class QTabWidget;
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateSelectPromptWidget;
class TextAutoGenerateSelectSkillWidget;
class TextAutoGenerateSelectAgentWidget;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextConfigurePromptsAgentsWidget
 * \brief Configure prompts, skills and agents.
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextConfigurePromptsAgentsWidget
 * Changes are applied with save().
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextConfigurePromptsAgentsWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     */
    explicit TextAutoGenerateTextConfigurePromptsAgentsWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    /*!
     */
    ~TextAutoGenerateTextConfigurePromptsAgentsWidget() override;

    /*!
     * Apply changes and save prompts, skills and agents
     */
    void save();
    /*!
     * Load current prompts, skills and agents (changes are discarded)
     */
    void load();

Q_SIGNALS:
    /*!
     */
    void settingsChanged();

private:
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
    QTabWidget *const mTabWidget;
    TextAutoGenerateSelectPromptWidget *const mSelectPromptWidget;
    TextAutoGenerateSelectSkillWidget *const mSelectSkillWidget;
    TextAutoGenerateSelectAgentWidget *const mSelectAgentWidget;
};
}
