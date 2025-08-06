/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>

#include "textautogeneratetext_export.h"
class QPlainTextEdit;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextConfigurePromptWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextConfigurePromptWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateTextConfigurePromptWidget() override;

    void setSystemPrompt(const QString &str);
    [[nodiscard]] QString systemPrompt() const;

private:
    QPlainTextEdit *const mSystemPrompt;
};

}
