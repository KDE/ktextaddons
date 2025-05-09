/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechat.h"

using namespace TextAutoGenerateText;
TextAutoGenerateChat::TextAutoGenerateChat() = default;

TextAutoGenerateChat::~TextAutoGenerateChat() = default;

bool TextAutoGenerateChat::favorite() const
{
    return mFavorite;
}

void TextAutoGenerateChat::setFavorite(bool newFavorite)
{
    mFavorite = newFavorite;
}

bool TextAutoGenerateChat::archived() const
{
    return mArchived;
}

void TextAutoGenerateChat::setArchived(bool newArchived)
{
    mArchived = newArchived;
}

QByteArray TextAutoGenerateChat::identifier() const
{
    return mIdentifier;
}

void TextAutoGenerateChat::setIdentifier(const QByteArray &newIdentifier)
{
    mIdentifier = newIdentifier;
}

bool TextAutoGenerateChat::operator==(const TextAutoGenerateChat &other) const
{
    return other.identifier() == mIdentifier && other.archived() == mArchived && other.favorite() == mFavorite && other.title() == mTitle;
}

QList<TextAutoGenerateMessage> TextAutoGenerateChat::messages() const
{
    return mMessages;
}

void TextAutoGenerateChat::setMessages(const QList<TextAutoGenerateText::TextAutoGenerateMessage> &newMessages)
{
    mMessages = newMessages;
}

QString TextAutoGenerateChat::title() const
{
    if (mTitle.isEmpty() && !mMessages.isEmpty()) {
        return mMessages.constFirst().htmlGenerated();
    }
    return mTitle;
}

void TextAutoGenerateChat::setTitle(const QString &newTitle)
{
    mTitle = newTitle;
}

qint64 TextAutoGenerateChat::dateTime() const
{
    if (!mMessages.isEmpty()) {
        return mMessages.constFirst().dateTime();
    }
    return -1;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateChat &t)
{
    d.space() << "title:" << t.title();
    d.space() << "favorite:" << t.favorite();
    d.space() << "archived:" << t.archived();
    d.space() << "identifier:" << t.identifier();
    d.space() << "messages:" << t.messages();
    return d;
}

#include "moc_textautogeneratechat.cpp"
