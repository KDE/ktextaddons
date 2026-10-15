/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "core/prompts/textautogenerateagent.h"
#include "textautogeneratetext_private_export.h"
#include <QWidget>
class QLineEdit;
class QPlainTextEdit;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateAgentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAgentWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateAgentWidget() override;

    void setAgent(const TextAutoGenerateText::TextAutoGenerateAgent &agent);
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateAgent agent() const;

private:
    TextAutoGenerateText::TextAutoGenerateAgent mCurrentAgent;
    QLineEdit *const mName;
    QPlainTextEdit *const mDescription;
};
}
