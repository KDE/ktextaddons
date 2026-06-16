/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLineEdit;
class QPlainTextEdit;
namespace TextAutoGenerateText
{
class TextAutoGeneratePrompt;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGeneratePromptWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGeneratePromptWidget(QWidget *parent = nullptr);
    ~TextAutoGeneratePromptWidget() override;

    void setPrompt(const TextAutoGenerateText::TextAutoGeneratePrompt &prompt);
    [[nodiscard]] TextAutoGenerateText::TextAutoGeneratePrompt prompt() const;

private:
    QLineEdit *const mName;
    QPlainTextEdit *const mText;
};
}
