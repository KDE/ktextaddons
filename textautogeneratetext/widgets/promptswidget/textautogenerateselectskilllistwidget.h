/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_private_export.h"
#include <QListView>
namespace TextAutoGenerateText
{
class TextAutoGenerateSkill;
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSelectSkillListWidget : public QListView
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSelectSkillListWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateSelectSkillListWidget() override;

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

Q_SIGNALS:
    void addSkill(const TextAutoGenerateText::TextAutoGenerateSkill &skill);
    void removeSkill(const QByteArray &identifier);
    void editSkill(const TextAutoGenerateText::TextAutoGenerateSkill &skill);

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotEditSkill(const QModelIndex &index);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotAddSkill();
};
}
