/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QJsonValue>
#include <QVariant>
namespace TextAutogenerateText
{
/**
 * @brief The TextAutogenerateTextContext class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextContext
{
public:
    TextAutoGenerateTextContext();
    ~TextAutoGenerateTextContext();

    [[nodiscard]] QVariant contextData() const;
    void setContextData(const QVariant &newContextData);

    [[nodiscard]] bool operator==(const TextAutoGenerateTextContext &other) const;

    [[nodiscard]] QJsonValue toJson() const;

private:
    QVariant mContextData;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutogenerateText::TextAutoGenerateTextContext &t);
