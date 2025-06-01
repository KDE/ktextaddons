/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"

#include <QString>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstance
{
public:
    TextAutoGenerateTextInstance();
    ~TextAutoGenerateTextInstance();

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

private:
    QString mName;
};
}
