/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateagentprompskillmanager.h"

using namespace TextAutoGenerateText;
TextAutoGenerateAgentPrompSkillManager::TextAutoGenerateAgentPrompSkillManager(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateAgentPrompSkillManager::~TextAutoGenerateAgentPrompSkillManager() = default;

QList<TextAutoGeneratePrompt> TextAutoGenerateAgentPrompSkillManager::prompts() const
{
    return mPrompts;
}

void TextAutoGenerateAgentPrompSkillManager::setPrompts(const QList<TextAutoGeneratePrompt> &newPrompts)
{
    mPrompts = newPrompts;
}

QList<TextAutoGenerateSkill> TextAutoGenerateAgentPrompSkillManager::skills() const
{
    return mSkills;
}

void TextAutoGenerateAgentPrompSkillManager::setSkills(const QList<TextAutoGenerateSkill> &newSkills)
{
    mSkills = newSkills;
}

QList<TextAutoGenerateAgent> TextAutoGenerateAgentPrompSkillManager::agents() const
{
    return mAgents;
}

void TextAutoGenerateAgentPrompSkillManager::setAgents(const QList<TextAutoGenerateAgent> &newAgents)
{
    mAgents = newAgents;
}

#include "moc_textautogenerateagentprompskillmanager.cpp"
