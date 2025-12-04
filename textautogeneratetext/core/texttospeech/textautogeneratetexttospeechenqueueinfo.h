/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
class QDebug;

#include <QByteArray>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToSpeechEnqueueInfo
{
public:
    TextAutoGenerateTextToSpeechEnqueueInfo();
    ~TextAutoGenerateTextToSpeechEnqueueInfo();

    [[nodiscard]] QByteArray chatId() const;
    void setChatId(const QByteArray &newChatId);

    [[nodiscard]] QByteArray messageId() const;
    void setMessageId(const QByteArray &newMessageId);

    [[nodiscard]] bool operator==(const TextAutoGenerateTextToSpeechEnqueueInfo &other) const;
    [[nodiscard]] bool isValid() const;

private:
    QByteArray mChatId;
    QByteArray mMessageId;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateTextToSpeechEnqueueInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToSpeechEnqueueInfo &t);
