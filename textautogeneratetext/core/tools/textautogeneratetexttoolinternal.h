/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QList>
class QDebug;
namespace TextAutoGenerateText
{
class TextAutoGenerateTextToolInternalProperty;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolInternal
{
public:
    TextAutoGenerateTextToolInternal();
    ~TextAutoGenerateTextToolInternal();

    [[nodiscard]] QList<TextAutoGenerateTextToolInternalProperty> properties() const;
    void setProperties(const QList<TextAutoGenerateTextToolInternalProperty> &newProperties);

    [[nodiscard]] QStringList required() const;
    void setRequired(const QStringList &newRequired);

private:
    QList<TextAutoGenerateTextToolInternalProperty> mProperties;
    QStringList mRequired;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolInternal &t);
