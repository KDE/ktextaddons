/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QVariant>
namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateTextContext
{
public:
    TextAutogenerateTextContext();
    ~TextAutogenerateTextContext();

    [[nodiscard]] QVariant contextData() const;
    void setContextData(const QVariant &newContextData);

private:
    QVariant mContextData;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutogenerateText::TextAutogenerateTextContext &t);
