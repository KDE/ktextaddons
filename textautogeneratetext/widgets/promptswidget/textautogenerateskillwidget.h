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
class TextAutoGenerateSkill;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSkillWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSkillWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateSkillWidget() override;

    void setSkill(const TextAutoGenerateText::TextAutoGenerateSkill &skill);
    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateSkill skill() const;

private:
    QLineEdit *const mName;
    QLineEdit *const mDescription;
    QPlainTextEdit *const mInstructions;
};
}
