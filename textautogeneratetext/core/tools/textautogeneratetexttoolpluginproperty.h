/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <KLazyLocalizedString>
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
    [[nodiscard]] KLazyLocalizedString description() const;
    void setDescription(const KLazyLocalizedString &newDescription);

    [[nodiscard]] KLazyLocalizedString name() const;
    void setName(const KLazyLocalizedString &newName);

private:
    KLazyLocalizedString mDescription;
    KLazyLocalizedString mName;
};
}
