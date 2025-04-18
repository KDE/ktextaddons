/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratemessage.h"
#include <KTextToHTML>
using namespace TextAutogenerateText;
TextAutoGenerateMessage::TextAutoGenerateMessage() = default;

TextAutoGenerateMessage::~TextAutoGenerateMessage() = default;

QDebug operator<<(QDebug d, const TextAutogenerateText::TextAutoGenerateMessage &t)
{
    d.space() << "content:" << t.content();
    d.space() << "htmlGenerated:" << t.htmlGenerated();
    d.space() << "sender:" << t.sender();
    d.space() << "dateTime:" << t.dateTime();
    d.space() << "in progress:" << t.inProgress();
    d.space() << "uuid:" << t.uuid();
    d.space() << "answerUuid:" << t.answerUuid();
    d.space() << "topic:" << t.topic();
    return d;
}

QString TextAutoGenerateMessage::content() const
{
    return mContent;
}

void TextAutoGenerateMessage::setContent(const QString &newContent)
{
    if (mContent != newContent) {
        mContent = newContent;
        const KTextToHTML::Options convertFlags = KTextToHTML::HighlightText | KTextToHTML::ConvertPhoneNumbers;
        mHtmlGenerated = KTextToHTML::convertToHtml(mContent, convertFlags);
    }
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
    return other.uuid() == mUuid && other.inProgress() == mInProgress && other.sender() == mSender && other.dateTime() == mDateTime
        && other.content() == mContent && other.answerUuid() == mAnswerUuid && other.topic() == mTopic;
}

QByteArray TextAutoGenerateMessage::uuid() const
{
    return mUuid;
}

void TextAutoGenerateMessage::setUuid(const QByteArray &newUuid)
{
    mUuid = newUuid;
}

QString TextAutoGenerateMessage::htmlGenerated() const
{
    return mHtmlGenerated;
}

QByteArray TextAutoGenerateMessage::answerUuid() const
{
    return mAnswerUuid;
}

void TextAutoGenerateMessage::setAnswerUuid(const QByteArray &newAnswerUuid)
{
    mAnswerUuid = newAnswerUuid;
}

QString TextAutoGenerateMessage::topic() const
{
    return mTopic;
}

void TextAutoGenerateMessage::setTopic(const QString &newTopic)
{
    mTopic = newTopic;
}

#include "moc_textautogeneratemessage.cpp"
