/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechat.h"
#include "core/models/textautogeneratemessagesmodel.h"

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
    , mDateTime(other.mDateTime)
    , mFavorite(other.mFavorite)
    , mArchived(other.mArchived)
    , mInitialized(other.mInitialized)
    , mInProgress(other.mInProgress)
{
}

TextAutoGenerateChat &TextAutoGenerateChat::operator=(const TextAutoGenerateChat &other)
{
    if (this != &other) {
        mMessageModel = other.mMessageModel;
        mIdentifier = other.mIdentifier;
        mDateTime = other.mDateTime;
        mTitle = other.mTitle;
        mFavorite = other.mFavorite;
        mArchived = other.mArchived;
        mInitialized = other.mInitialized;
        mInProgress = other.mInProgress;
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
    return other.identifier() == mIdentifier && other.archived() == mArchived && other.favorite() == mFavorite && other.title() == mTitle
        && other.initialized() == mInitialized && other.dateTime() == mDateTime;
}

QString TextAutoGenerateChat::title() const
{
    if (mMessageModel) {
        if (mTitle.isEmpty() && !mMessageModel->messages().isEmpty()) {
            return mMessageModel->messages().constFirst().content();
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
    return mDateTime;
}

void TextAutoGenerateChat::setDateTime(qint64 dt)
{
    mDateTime = dt;
}

QByteArray TextAutoGenerateChat::serialize(const TextAutoGenerateChat &chat, bool toBinary)
{
    QJsonDocument d;
    QJsonObject o;
    o["title"_L1] = chat.title();
    o["favorite"_L1] = chat.mFavorite;
    o["archived"_L1] = chat.mArchived;
    o["identifier"_L1] = QString::fromLatin1(chat.mIdentifier);
    o["datetime"_L1] = chat.dateTime();

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
    chat.setDateTime(o["datetime"_L1].toInteger());
    return chat;
}

TextAutoGenerateMessagesModel *TextAutoGenerateChat::messageModel() const
{
    return mMessageModel.data();
}

bool TextAutoGenerateChat::initialized() const
{
    return mInitialized;
}

void TextAutoGenerateChat::setInitialized(bool newInitialized)
{
    mInitialized = newInitialized;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateChat &t)
{
    d.space() << "title:" << t.title();
    d.space() << "favorite:" << t.favorite();
    d.space() << "archived:" << t.archived();
    d.space() << "identifier:" << t.identifier();
    d.space() << "initialized:" << t.initialized();
    d.space() << "dateTime:" << t.dateTime();
    d.space() << "inProgress:" << t.inProgress();
    return d;
}

TextAutoGenerateChat::SectionHistory TextAutoGenerateChat::section() const
{
    if (favorite()) {
        return TextAutoGenerateChat::SectionHistory::Favorite;
    }
    if (!messageModel()) {
        return TextAutoGenerateChat::SectionHistory::Unknown;
    }
    if (messageModel()->messages().isEmpty()) {
        return mDateTime != -1 ? sectionMessage(mDateTime) : TextAutoGenerateChat::SectionHistory::Today;
    }
    return sectionMessage(messageModel()->messages().constLast().dateTime());
}

TextAutoGenerateChat::SectionHistory TextAutoGenerateChat::sectionMessage(qint64 dt) const
{
    if (dt == -1) {
        return TextAutoGenerateChat::SectionHistory::Unknown;
    }
    const QDate d = QDateTime::fromSecsSinceEpoch(dt).date();
    if (d == QDate::currentDate()) {
        return TextAutoGenerateChat::SectionHistory::Today;
    } else if (d < QDate::currentDate().addDays(7)) {
        return TextAutoGenerateChat::SectionHistory::LessThanSevenDays;
    } else if (d < QDate::currentDate().addDays(30)) {
        return TextAutoGenerateChat::SectionHistory::LessThanThirtyDays;
    } else {
        return TextAutoGenerateChat::SectionHistory::Later;
    }
    return TextAutoGenerateChat::SectionHistory::Unknown;
}

bool TextAutoGenerateChat::inProgress() const
{
    return mInProgress;
}

void TextAutoGenerateChat::setInProgress(bool newInProgress)
{
    mInProgress = newInProgress;
}

#include "moc_textautogeneratechat.cpp"
