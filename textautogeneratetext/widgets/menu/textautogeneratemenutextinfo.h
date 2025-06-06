/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateMenuTextInfo
{
public:
    TextAutoGenerateMenuTextInfo();
    ~TextAutoGenerateMenuTextInfo();

    [[nodiscard]] bool enabled() const;
    void setEnabled(bool newEnabled);

    [[nodiscard]] QString requestText() const;
    void setRequestText(const QString &newRequestText);

    [[nodiscard]] bool operator==(const TextAutoGenerateMenuTextInfo &other) const;

private:
    QString mRequestText;
    bool mEnabled = true;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateMenuTextInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateMenuTextInfo &t);
