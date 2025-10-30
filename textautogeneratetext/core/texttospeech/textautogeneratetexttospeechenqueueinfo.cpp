/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratetexttospeechenqueueinfo.h"

using namespace TextAutoGenerateText;

TextAutoGenerateTextToSpeechEnqueueInfo::TextAutoGenerateTextToSpeechEnqueueInfo() = default;

TextAutoGenerateTextToSpeechEnqueueInfo::~TextAutoGenerateTextToSpeechEnqueueInfo() = default;

QByteArray TextAutoGenerateTextToSpeechEnqueueInfo::chatId() const
{
    return mChatId;
}

void TextAutoGenerateTextToSpeechEnqueueInfo::setChatId(const QByteArray &newChatId)
{
    mChatId = newChatId;
}

QByteArray TextAutoGenerateTextToSpeechEnqueueInfo::messageId() const
{
    return mMessageId;
}

void TextAutoGenerateTextToSpeechEnqueueInfo::setMessageId(const QByteArray &newMessageId)
{
    mMessageId = newMessageId;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToSpeechEnqueueInfo &t)
{
    d.space() << "chatId:" << t.chatId();
    d.space() << "messageId:" << t.messageId();
    return d;
}

bool TextAutoGenerateTextToSpeechEnqueueInfo::operator==(const TextAutoGenerateTextToSpeechEnqueueInfo &other) const
{
    return mChatId == other.chatId() && mMessageId == other.messageId();
}

bool TextAutoGenerateTextToSpeechEnqueueInfo::isValid() const
{
    return !mChatId.isEmpty() && !mMessageId.isEmpty();
}
