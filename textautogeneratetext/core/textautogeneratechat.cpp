/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechat.h"

#include <QJsonDocument>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
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

QByteArray TextAutoGenerateChat::serialize(const TextAutoGenerateChat &chat, bool toBinary)
{
    QJsonDocument d;
    QJsonObject o;
    if (!chat.mTitle.isEmpty()) {
        o["title"_L1] = chat.mTitle;
    }
    o["favorite"_L1] = chat.mFavorite;
    o["archived"_L1] = chat.mArchived;
    o["identifier"_L1] = QString::fromLatin1(chat.mIdentifier);

    if (toBinary) {
        return QCborValue::fromJsonValue(o).toCbor();
    }
    d.setObject(o);
    return d.toJson(QJsonDocument::Indented);
}

TextAutoGenerateChat TextAutoGenerateChat::deserialize(const QJsonObject &o)
{
    TextAutoGenerateChat chat;
    chat.setTitle(o["title"_L1].toString());
    chat.setFavorite(o["favorite"_L1].toBool(false));
    chat.setArchived(o["archived"_L1].toBool(false));
    chat.setIdentifier(o["archived"_L1].toString().toLatin1());
    return chat;
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
