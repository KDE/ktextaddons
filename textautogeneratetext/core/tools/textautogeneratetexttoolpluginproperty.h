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

    [[nodiscard]] KLazyLocalizedString description() const;
    void setDescription(const KLazyLocalizedString &newDescription);

    [[nodiscard]] KLazyLocalizedString name() const;
    void setName(const KLazyLocalizedString &newName);

    [[nodiscard]] QByteArray generateProperty() const;

private:
    KLazyLocalizedString mDescription;
    KLazyLocalizedString mName;
};
}
