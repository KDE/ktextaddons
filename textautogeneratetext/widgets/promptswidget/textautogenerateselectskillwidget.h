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
class TextAutoGenerateSkill;
class TextAutoGenerateTextSkillModel;
class TextAutoGenerateSelectSkillListWidget;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSelectSkillWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectSkillWidget(TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateSelectSkillWidget() override;

    [[nodiscard]] QList<TextAutoGenerateSkill> skills() const;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditSkill(const TextAutoGenerateText::TextAutoGenerateSkill &skill);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAddSkill(const TextAutoGenerateText::TextAutoGenerateSkill &skill);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotRemoveSkill(const QByteArray &identifier);
    TextAutoGenerateSelectSkillListWidget *const mListWidget;
    TextAutoGenerateTextSkillModel *const mSkillModel;
};
}
