/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

#include "textautogeneratetext_export.h"

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
};
}
