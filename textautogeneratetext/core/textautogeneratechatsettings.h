/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>
#include <QMap>
#include <QString>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateChatSettings
{
public:
    struct TEXTAUTOGENERATETEXT_EXPORT PendingTypedInfo {
        QString text;
        int scrollbarPosition = -1;
        [[nodiscard]] bool isValid() const;
    };
    TextAutoGenerateChatSettings();
    ~TextAutoGenerateChatSettings();

    void remove(const QByteArray &roomId);

    void add(const QByteArray &chatId, const PendingTypedInfo &info);

    [[nodiscard]] PendingTypedInfo value(const QByteArray &chatId);

    [[nodiscard]] bool isEmpty() const;

private:
    QMap<QByteArray /*ChatId*/, PendingTypedInfo> mPendingTypedTexts;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateChatSettings::PendingTypedInfo &t);
