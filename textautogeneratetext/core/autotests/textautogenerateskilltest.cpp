/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateskilltest.h"
#include "core/prompts/textautogenerateskill.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateSkillTest)

TextAutoGenerateSkillTest::TextAutoGenerateSkillTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSkillTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateSkill skill;
    QVERIFY(skill.description().isEmpty());
    QVERIFY(skill.name().isEmpty());
    QVERIFY(skill.instructions().isEmpty());
}

#include "moc_textautogenerateskilltest.cpp"
