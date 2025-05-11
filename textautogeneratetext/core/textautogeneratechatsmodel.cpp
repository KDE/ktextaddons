/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechatsmodel.h"
#include "core/textautogeneratemessagesmodel.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>
using namespace TextAutoGenerateText;
TextAutoGenerateChatsModel::TextAutoGenerateChatsModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateChatsModel::~TextAutoGenerateChatsModel() = default;

int TextAutoGenerateChatsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mChats.count();
}

QList<TextAutoGenerateChat> TextAutoGenerateChatsModel::chats() const
{
    return mChats;
}

void TextAutoGenerateChatsModel::setChats(const QList<TextAutoGenerateChat> &newChats)
{
    beginResetModel();
    mChats = newChats;
    endResetModel();
}

void TextAutoGenerateChatsModel::addChat(const TextAutoGenerateChat &chat)
{
    beginInsertRows(QModelIndex(), mChats.count(), mChats.count());
    mChats.append(chat);
    endInsertRows();
}

QVariant TextAutoGenerateChatsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mChats.count()) {
        return {};
    }
    const auto &chat = mChats[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case Title:
        return title(chat);
    case Identifier:
        return chat.identifier();
    case Favorite:
        return chat.favorite();
    case Archived:
        return chat.archived();
    case Section:
        return QVariant::fromValue(chat.section());
    case DateTime:
        return dateTime(chat);
    }
    return {};
}

QString TextAutoGenerateChatsModel::title(const TextAutoGenerateChat &chat) const
{
    const QString chatTitle = chat.title();
    return chatTitle.isEmpty() ? i18n("New Chat...") : chatTitle;
}

qint64 TextAutoGenerateChatsModel::dateTime(const TextAutoGenerateChat &chat) const
{
    return chat.dateTime();
}

bool TextAutoGenerateChatsModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (!idx.isValid()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "ERROR: invalid index";
        return false;
    }
    const int id = idx.row();
    TextAutoGenerateChat &chat = mChats[id];
    switch (role) {
    case ChatRoles::Title: {
        chat.setTitle(value.toString());
        Q_EMIT dataChanged(idx, idx, {TextAutoGenerateChatsModel::ChatRoles::Title});
        return true;
    }
    case ChatRoles::Archived: {
        chat.setArchived(value.toBool());
        Q_EMIT dataChanged(idx, idx, {TextAutoGenerateChatsModel::ChatRoles::Archived});
        return true;
    }
    case ChatRoles::Favorite: {
        chat.setFavorite(value.toBool());
        Q_EMIT dataChanged(idx, idx, {TextAutoGenerateChatsModel::ChatRoles::Favorite});
        return true;
    }
    case ChatRoles::Identifier:
    case ChatRoles::Section:
    case ChatRoles::DateTime:
        break;
    }
    return QAbstractListModel::setData(idx, value, role);
}

Qt::ItemFlags TextAutoGenerateChatsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

TextAutoGenerateChat TextAutoGenerateChatsModel::chat(const QByteArray &chatId) const
{
    if (chatId.isEmpty()) {
        return {};
    }
    auto matchesUuid = [&](const TextAutoGenerateChat &c) {
        return c.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), matchesUuid);
    if (it == mChats.end()) {
        return {};
    }
    return *it;
}

QString TextAutoGenerateChatsModel::sectionName(TextAutoGenerateChat::SectionHistory sectionId)
{
    switch (sectionId) {
    case TextAutoGenerateChat::SectionHistory::Favorite:
        return i18n("Favorite");
    case TextAutoGenerateChat::SectionHistory::Today:
        return i18n("Today");
    case TextAutoGenerateChat::SectionHistory::LessThanSevenDays:
        return i18n("7 days previous");
    case TextAutoGenerateChat::SectionHistory::LessThanThirtyDays:
        return i18n("30 days previous");
    case TextAutoGenerateChat::SectionHistory::Later:
        return i18n("Later");
    case TextAutoGenerateChat::SectionHistory::Unknown:
        return i18n("Unknown");
    case TextAutoGenerateChat::SectionHistory::NSections:
        break;
    }
    return QStringLiteral("ERROR");
}

TextAutoGenerateMessagesModel *TextAutoGenerateChatsModel::messagesModel(const QByteArray &chatId) const
{
    const int roomCount = mChats.count();
    for (int i = 0; i < roomCount; ++i) {
        const TextAutoGenerateChat &chat = mChats.at(i);
        if (chat.identifier() == chatId) {
            return chat.messageModel();
        }
    }
    return {};
}

bool TextAutoGenerateChatsModel::isInitialized(const QByteArray &chatId) const
{
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        return (*it).initialized();
    }
    return false;
}

void TextAutoGenerateChatsModel::setInitialized(const QByteArray &chatId, bool state)
{
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        (*it).setInitialized(state);
    }
}

void TextAutoGenerateChatsModel::messagesChanged(const QByteArray &chatId)
{
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        const int i = std::distance(mChats.begin(), it);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {Title | DateTime});
    }
}

void TextAutoGenerateChatsModel::changeFavorite(const QByteArray &chatId, bool favorite)
{
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        (*it).setFavorite(favorite);
        const int i = std::distance(mChats.begin(), it);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {Favorite});
    }
}

#include "moc_textautogeneratechatsmodel.cpp"
