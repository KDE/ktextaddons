/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <KLazyLocalizedString>
#include <QStringList>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolPluginProperty
{
public:
    TextAutoGenerateTextToolPluginProperty();
    ~TextAutoGenerateTextToolPluginProperty();

    [[nodiscard]] KLazyLocalizedString description() const;
    void setDescription(const KLazyLocalizedString &newDescription);

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] QStringList typeElements() const;
    void setTypeElements(const QStringList &newEnumElements);

private:
    QStringList mTypeElements;
    KLazyLocalizedString mDescription;
    QString mName;
};
}
