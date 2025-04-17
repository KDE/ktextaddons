/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QDebug>
namespace TextAutogenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateHistoryInfo
{
public:
    TextAutoGenerateHistoryInfo();
    ~TextAutoGenerateHistoryInfo();

    [[nodiscard]] QString subject() const;
    void setSubject(const QString &newTitle);

    [[nodiscard]] qint64 dateTime() const;
    void setDateTime(qint64 newDateTime);

    [[nodiscard]] QString model() const;
    void setModel(const QString &newModel);

    [[nodiscard]] QString engine() const;
    void setEngine(const QString &newEngine);

private:
    QString mEngine;
    QString mModel;
    QString mSubject;
    qint64 mDateTime = -1;
};
}
Q_DECLARE_TYPEINFO(TextAutogenerateText::TextAutoGenerateHistoryInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutogenerateText::TextAutoGenerateHistoryInfo &t);
