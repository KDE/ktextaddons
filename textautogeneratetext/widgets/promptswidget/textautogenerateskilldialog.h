/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateSkillWidget;
class TextAutoGenerateSkill;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSkillDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSkillDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateSkillDialog() override;

    void setSkill(const TextAutoGenerateText::TextAutoGenerateSkill &prompt);
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateSkill skill() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TextAutoGenerateSkillWidget *const mSkillWidget;
};
}
