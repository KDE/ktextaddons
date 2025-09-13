/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QString>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolPluginProperty
{
public:
    TextAutoGenerateTextToolPluginProperty();
    ~TextAutoGenerateTextToolPluginProperty();

#if 0
    "location": {
      "type": "string",
      "description": "The location to get the weather for, e.g. San Francisco, CA"
    },
#endif
    [[nodiscard]] QString description() const;
    void setDescription(const QString &newDescription);

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

private:
    QString mDescription;
    QString mName;
};
}
