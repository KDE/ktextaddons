/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateagentprompskillmanager.h"
#include "core/textautogeneratetextutils.h"
#include <KConfigGroup>
#include <KSharedConfig>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateAgentPrompSkillManager::TextAutoGenerateAgentPrompSkillManager(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateAgentPrompSkillManager::~TextAutoGenerateAgentPrompSkillManager() = default;

void TextAutoGenerateAgentPrompSkillManager::load()
{
    loadPrompts();
    loadSkills();
}

void TextAutoGenerateAgentPrompSkillManager::loadPrompts()
{
    const auto config = KSharedConfig::openConfig(TextAutoGenerateTextUtils::promptConfigFileName());
    const QStringList promptList = TextAutoGenerateTextUtils::promptsList(config);
    QList<TextAutoGeneratePrompt> lst;
    lst.reserve(promptList.count());
    for (const QString &prompt : promptList) {
        TextAutoGeneratePrompt p;
        p.load(config->group(prompt));
        if (p.isValid()) {
            lst.append(std::move(p));
        }
    }
    setPrompts(lst);
}

void TextAutoGenerateAgentPrompSkillManager::loadSkills()
{
    const auto config = KSharedConfig::openConfig(TextAutoGenerateTextUtils::skillConfigFileName());
    const QStringList skillList = TextAutoGenerateTextUtils::skillsList(config);
    QList<TextAutoGenerateSkill> lst;
    lst.reserve(skillList.count());
    for (const QString &skill : skillList) {
        TextAutoGenerateSkill p;
        p.load(config->group(skill));
        if (p.isValid()) {
            lst.append(std::move(p));
        }
    }
    setSkills(lst);
}

void TextAutoGenerateAgentPrompSkillManager::loadAgents()
{
    const auto config = KSharedConfig::openConfig(TextAutoGenerateTextUtils::agentConfigFileName());
    const QStringList agentList = TextAutoGenerateTextUtils::agentsList(config);
    QList<TextAutoGenerateAgent> lst;
    lst.reserve(agentList.count());
    for (const QString &agent : agentList) {
        TextAutoGenerateAgent p;
        p.load(config->group(agent));
        if (p.isValid()) {
            lst.append(std::move(p));
        }
    }
    setAgents(lst);
}

void TextAutoGenerateAgentPrompSkillManager::save()
{
    saveAgents();
    saveSkills();
    savePrompts();
}

void TextAutoGenerateAgentPrompSkillManager::saveAgents()
{
    auto config = KSharedConfig::openConfig(TextAutoGenerateTextUtils::agentConfigFileName());

    const auto instanceList = TextAutoGenerateTextUtils::agentsList(config);
    for (const auto &group : instanceList) {
        config->deleteGroup(group);
    }

    for (int i = 0; i < mAgents.count(); ++i) {
        KConfigGroup group = config->group(u"Agent #%1"_s.arg(i));
        mAgents[i].save(group);
    }
    config->sync();
}

void TextAutoGenerateAgentPrompSkillManager::saveSkills()
{
    auto config = KSharedConfig::openConfig(TextAutoGenerateTextUtils::instanceConfigFileName());

    const auto instanceList = TextAutoGenerateTextUtils::instancesList(config);
    for (const auto &group : instanceList) {
        config->deleteGroup(group);
    }

    for (int i = 0; i < mSkills.count(); ++i) {
        KConfigGroup group = config->group(u"Skill #%1"_s.arg(i));
        mSkills[i].save(group);
    }
    config->sync();
}

void TextAutoGenerateAgentPrompSkillManager::savePrompts()
{
    auto config = KSharedConfig::openConfig(TextAutoGenerateTextUtils::instanceConfigFileName());

    const auto instanceList = TextAutoGenerateTextUtils::instancesList(config);
    for (const auto &group : instanceList) {
        config->deleteGroup(group);
    }

    for (int i = 0; i < mPrompts.count(); ++i) {
        KConfigGroup group = config->group(u"Prompt #%1"_s.arg(i));
        mPrompts[i].save(group);
    }
    config->sync();
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
