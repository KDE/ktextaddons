/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "core/prompts/textautogenerateprompt.h"
#include "textautogeneratetext_private_export.h"
#include <QComboBox>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGeneratePromptComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit TextAutoGeneratePromptComboBox(QWidget *parent = nullptr);
    ~TextAutoGeneratePromptComboBox() override;

    [[nodiscard]] TextAutoGeneratePrompt::Category category() const;
    void setCategory(TextAutoGeneratePrompt::Category type);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void fill();
};
}
