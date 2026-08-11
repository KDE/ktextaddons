/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QList>
#include <QObject>
#include <TextAutoGenerateText/TextAutoGenerateAgent>
#include <TextAutoGenerateText/TextAutoGeneratePrompt>
#include <TextAutoGenerateText/TextAutoGenerateSkill>

namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateAgentPrompSkillManager
 * \brief The TextAutoGenerateAgentPrompSkillManager class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateAgentPrompSkillManager
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAgentPrompSkillManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief TextAutoGenerateAgentPrompSkillManager
     * \param parent
     */
    explicit TextAutoGenerateAgentPrompSkillManager(QObject *parent = nullptr);
    /*!
     * \brief ~TextAutoGenerateAgentPrompSkillManager
     */
    ~TextAutoGenerateAgentPrompSkillManager() override;

    /*!
     * \brief prompts
     * \return
     */
    [[nodiscard]] QList<TextAutoGeneratePrompt> prompts() const;
    /*!
     * \brief setPrompts
     * \param newPrompts
     */
    void setPrompts(const QList<TextAutoGeneratePrompt> &newPrompts);

    /*!
     * \brief skills
     * \return
     */
    [[nodiscard]] QList<TextAutoGenerateSkill> skills() const;
    /*!
     * \brief setSkills
     * \param newSkills
     */
    void setSkills(const QList<TextAutoGenerateSkill> &newSkills);

    /*!
     * \brief agents
     * \return
     */
    [[nodiscard]] QList<TextAutoGenerateAgent> agents() const;
    /*!
     * \brief setAgents
     * \param newAgents
     */
    void setAgents(const QList<TextAutoGenerateAgent> &newAgents);

private:
    QList<TextAutoGeneratePrompt> mPrompts;
    QList<TextAutoGenerateSkill> mSkills;
    QList<TextAutoGenerateAgent> mAgents;
};
}
