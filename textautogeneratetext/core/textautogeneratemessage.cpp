/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessage.h"

using namespace TextAutogenerateText;
TextAutoGenerateMessage::TextAutoGenerateMessage() = default;

TextAutoGenerateMessage::~TextAutoGenerateMessage() = default;

QDebug operator<<(QDebug d, const TextAutogenerateText::TextAutoGenerateMessage &t)
{
    d.space() << "content:" << t.content();
    d.space() << "sender:" << t.sender();
    d.space() << "dateTime:" << t.dateTime();
    d.space() << "in progress:" << t.inProgress();
    return d;
}

QString TextAutoGenerateMessage::content() const
{
    return mContent;
}

void TextAutoGenerateMessage::setContent(const QString &newContent)
{
    mContent = newContent;
}

TextAutoGenerateMessage::Sender TextAutoGenerateMessage::sender() const
{
    return mSender;
}

void TextAutoGenerateMessage::setSender(TextAutoGenerateMessage::Sender newSender)
{
    mSender = newSender;
}

qint64 TextAutoGenerateMessage::dateTime() const
{
    return mDateTime;
}

void TextAutoGenerateMessage::setDateTime(qint64 newDateTime)
{
    mDateTime = newDateTime;
}

bool TextAutoGenerateMessage::isValid() const
{
    return mSender != TextAutoGenerateMessage::Sender::Unknown;
}

bool TextAutoGenerateMessage::inProgress() const
{
    return mInProgress;
}

void TextAutoGenerateMessage::setInProgress(bool newInProgress)
{
    mInProgress = newInProgress;
}

bool TextAutoGenerateMessage::operator==(const TextAutoGenerateMessage &other) const
{
    return other.inProgress() == mInProgress && other.sender() == mSender && other.dateTime() == mDateTime && other.content() == mContent;
}

#include "moc_textautogeneratemessage.cpp"
