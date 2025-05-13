/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchmessage.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchMessage::TextAutoGenerateSearchMessage() = default;

TextAutoGenerateSearchMessage::~TextAutoGenerateSearchMessage() = default;

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateSearchMessage &t)
{
    d.space() << "chatId:" << t.chatId();
    d.space() << "messageId:" << t.messageId();
    d.space() << "previewText:" << t.previewText();
    d.space() << "dateTime:" << t.dateTime();
    return d;
}

bool TextAutoGenerateSearchMessage::operator==(const TextAutoGenerateSearchMessage &other) const
{
    return other.chatId() == mChatId && other.dateTime() == mDateTime && other.messageId() == mMessageId && other.previewText() == mPreviewText;
}

QByteArray TextAutoGenerateSearchMessage::chatId() const
{
    return mChatId;
}

void TextAutoGenerateSearchMessage::setChatId(const QByteArray &newChatId)
{
    mChatId = newChatId;
}

QByteArray TextAutoGenerateSearchMessage::messageId() const
{
    return mMessageId;
}

void TextAutoGenerateSearchMessage::setMessageId(const QByteArray &newMessageId)
{
    mMessageId = newMessageId;
}

QString TextAutoGenerateSearchMessage::previewText() const
{
    return mPreviewText;
}

void TextAutoGenerateSearchMessage::setPreviewText(const QString &newPreviewText)
{
    mPreviewText = newPreviewText;
}

qint64 TextAutoGenerateSearchMessage::dateTime() const
{
    return mDateTime;
}

void TextAutoGenerateSearchMessage::setDateTime(qint64 newDateTime)
{
    mDateTime = newDateTime;
}
