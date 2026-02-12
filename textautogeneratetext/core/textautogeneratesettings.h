/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QString>
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateSettings
 * \brief The TextAutoGenerateSettings class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateSettings
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateSettings
{
public:
    /*!
     * Constructs a new TextAutoGenerateSettings object.
     */
    TextAutoGenerateSettings();
    /*!
     * Destroys the TextAutoGenerateSettings object.
     */
    ~TextAutoGenerateSettings();

    /*!
     * Returns the system prompt.
     * \return The system prompt as a QString
     */
    [[nodiscard]] QString systemPrompt() const;
    /*!
     * Sets the system prompt.
     * \param newSystemPrompt The system prompt to set
     */
    void setSystemPrompt(const QString &newSystemPrompt);
    /*!
     * Loads the settings from storage.
     */
    void load();

    /*!
     * Returns the default system prompt.
     * \return The default prompt as a QString
     */
    [[nodiscard]] static QString defaultPrompt();

private:
    void save();
    QString mSystemPrompt;
};

}
