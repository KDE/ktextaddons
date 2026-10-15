/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateTextSkillModelTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextSkillModelTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextSkillModelTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldSetSkills();
    void shouldAddSkill();
    void shouldRemoveSkill();
    void shouldUpdateSkill();
};
