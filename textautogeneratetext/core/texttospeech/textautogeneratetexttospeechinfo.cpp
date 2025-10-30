/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratetexttospeechinfo.h"

using namespace TextAutoGenerateText;

TextAutoGenerateTextToSpeechInfo::TextAutoGenerateTextToSpeechInfo() = default;

TextAutoGenerateTextToSpeechInfo::~TextAutoGenerateTextToSpeechInfo() = default;

QByteArray TextAutoGenerateTextToSpeechInfo::chatId() const
{
    return mChatId;
}

void TextAutoGenerateTextToSpeechInfo::setChatId(const QByteArray &newChatId)
{
    mChatId = newChatId;
}

QByteArray TextAutoGenerateTextToSpeechInfo::messageId() const
{
    return mMessageId;
}

void TextAutoGenerateTextToSpeechInfo::setMessageId(const QByteArray &newMessageId)
{
    mMessageId = newMessageId;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToSpeechInfo &t)
{
    d.space() << "chatId:" << t.chatId();
    d.space() << "messageId:" << t.messageId();
    return d;
}
