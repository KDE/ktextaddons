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

void TextAutoGenerateAgentPrompSkillManager::load()
{
    // TODO
}

void TextAutoGenerateAgentPrompSkillManager::save()
{
    // TODO
}

QList<TextAutoGeneratePrompt> TextAutoGenerateAgentPrompSkillManager::prompts() const
{
    return mPrompts;
}

void TextAutoGenerateAgentPrompSkillManager::setPrompts(const QList<TextAutoGeneratePrompt> &newPrompts)
{
    if (mPrompts != newPrompts) {
        mPrompts = newPrompts;
        Q_EMIT promptsChanged();
    }
}

QList<TextAutoGenerateSkill> TextAutoGenerateAgentPrompSkillManager::skills() const
{
    return mSkills;
}

void TextAutoGenerateAgentPrompSkillManager::setSkills(const QList<TextAutoGenerateSkill> &newSkills)
{
    if (mSkills != newSkills) {
        mSkills = newSkills;
        Q_EMIT skillsChanged();
    }
}

QList<TextAutoGenerateAgent> TextAutoGenerateAgentPrompSkillManager::agents() const
{
    return mAgents;
}

void TextAutoGenerateAgentPrompSkillManager::setAgents(const QList<TextAutoGenerateAgent> &newAgents)
{
    if (mAgents != newAgents) {
        mAgents = newAgents;
        Q_EMIT agentsChanged();
    }
}

#include "moc_textautogenerateagentprompskillmanager.cpp"
