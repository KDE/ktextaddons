/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechat.h"
#include "textautogeneratemessagesmodel.h"

#include <QJsonDocument>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateChat::TextAutoGenerateChat()
    : mMessageModel(new TextAutoGenerateMessagesModel())
{
}

TextAutoGenerateChat::TextAutoGenerateChat(const TextAutoGenerateChat &other)
    : mMessageModel(other.mMessageModel)
    , mIdentifier(other.mIdentifier)
    , mTitle(other.mTitle)
    , mFavorite(other.mFavorite)
    , mArchived(other.mArchived)
{
}

TextAutoGenerateChat &TextAutoGenerateChat::operator=(const TextAutoGenerateChat &other)
{
    if (this != &other) {
        mMessageModel = other.mMessageModel;
        mIdentifier = other.mIdentifier;
        mTitle = other.mTitle;
        mFavorite = other.mFavorite;
        mArchived = other.mArchived;
    }
    return *this;
}

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
    if (mMessageModel) {
        mMessageModel->setChatId(mIdentifier);
    }
}

bool TextAutoGenerateChat::operator==(const TextAutoGenerateChat &other) const
{
    return other.identifier() == mIdentifier && other.archived() == mArchived && other.favorite() == mFavorite && other.title() == mTitle;
}

QString TextAutoGenerateChat::title() const
{
    if (mMessageModel) {
        if (mTitle.isEmpty() && !mMessageModel->messages().isEmpty()) {
            return mMessageModel->messages().constFirst().htmlGenerated();
        }
    }
    return mTitle;
}

void TextAutoGenerateChat::setTitle(const QString &newTitle)
{
    mTitle = newTitle;
}

qint64 TextAutoGenerateChat::dateTime() const
{
    if (mMessageModel) {
        if (!mMessageModel->messages().isEmpty()) {
            return mMessageModel->messages().constLast().dateTime();
        }
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
    chat.setIdentifier(o["identifier"_L1].toString().toLatin1());
    return chat;
}

TextAutoGenerateMessagesModel *TextAutoGenerateChat::messageModel() const
{
    return mMessageModel.data();
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateChat &t)
{
    d.space() << "title:" << t.title();
    d.space() << "favorite:" << t.favorite();
    d.space() << "archived:" << t.archived();
    d.space() << "identifier:" << t.identifier();
    return d;
}

#include "moc_textautogeneratechat.cpp"
