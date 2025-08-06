/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QString>
namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateSettings class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateSettings
{
public:
    TextAutoGenerateSettings();
    ~TextAutoGenerateSettings();

    [[nodiscard]] QString systemPrompt() const;
    void setSystemPrompt(const QString &newSystemPrompt);
    void load();

private:
    void save();
    QString mSystemPrompt;
};

}
