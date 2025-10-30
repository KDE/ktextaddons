/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QDebug>

#include <QByteArray>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToSpeechInfo
{
public:
    TextAutoGenerateTextToSpeechInfo();
    ~TextAutoGenerateTextToSpeechInfo();

    [[nodiscard]] QByteArray chatId() const;
    void setChatId(const QByteArray &newChatId);

    [[nodiscard]] QByteArray messageId() const;
    void setMessageId(const QByteArray &newMessageId);

    [[nodiscard]] bool operator==(const TextAutoGenerateTextToSpeechInfo &other) const;

private:
    QByteArray mChatId;
    QByteArray mMessageId;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextToSpeechInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToSpeechInfo &t);
