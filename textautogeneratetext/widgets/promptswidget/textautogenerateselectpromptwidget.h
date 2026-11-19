/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_private_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGeneratePrompt;
class TextAutoGenerateTextPromptModel;
class TextAutoGenerateSelectPromptListWidget;
class TextAutoGenerateSearchPromptWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSelectPromptWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectPromptWidget(TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateSelectPromptWidget() override;

    [[nodiscard]] QList<TextAutoGeneratePrompt> prompts() const;

    // Load prompts from manager (changes are discarded)
    void load();
    // Apply changes to manager (it's not saved on disk)
    void save();

Q_SIGNALS:
    void settingsChanged();

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditPrompt(const TextAutoGenerateText::TextAutoGeneratePrompt &prompt);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAddPrompt(const TextAutoGenerateText::TextAutoGeneratePrompt &prompt);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemovePrompt(const QByteArray &identifier);
    TextAutoGenerateSelectPromptListWidget *const mListWidget;
    TextAutoGenerateTextPromptModel *const mPromptModel;
    TextAutoGenerateManager *const mManager;
    TextAutoGenerateSearchPromptWidget *const mSearchPromptWidget;
};
}
