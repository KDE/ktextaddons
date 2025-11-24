/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QDialog>
#include <TextAutoGenerateText/TextAutoGenerateManager>
namespace TextAutoGenerateText
{
class TextAutoGenerateQuickAskWidget;
/**
 * @brief The TextAutoGenerateQuickAskDialog class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateQuickAskDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateQuickAskDialog(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateQuickAskDialog() override;

    void ask(const TextAutoGenerateText::TextAutoGenerateManager::AskMessageInfo &info);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TextAutoGenerateQuickAskWidget *const mTextAutoGenerateQuickAskWidget;
    TextAutoGenerateText::TextAutoGenerateManager *const mManager;
};
}
