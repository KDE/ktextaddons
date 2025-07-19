/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechatsmodel.h"
using namespace Qt::Literals::StringLiterals;

#include "core/models/textautogeneratemessagesmodel.h"
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
    const auto &chatElement = mChats[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case Title:
        return title(chatElement);
    case Identifier:
        return chatElement.identifier();
    case Favorite:
        return chatElement.favorite();
    case Archived:
        return chatElement.archived();
    case InProgress:
        return chatElement.inProgress();
    case Section:
        return QVariant::fromValue(chatElement.section());
    case DateTime:
        return dateTime(chatElement);
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
    TextAutoGenerateChat &chatElement = mChats[id];
    switch (role) {
    case ChatRoles::Title: {
        chatElement.setTitle(value.toString());
        Q_EMIT dataChanged(idx, idx, {TextAutoGenerateChatsModel::ChatRoles::Title});
        return true;
    }
    case ChatRoles::Archived: {
        chatElement.setArchived(value.toBool());
        Q_EMIT dataChanged(idx, idx, {TextAutoGenerateChatsModel::ChatRoles::Archived});
        return true;
    }
    case ChatRoles::Favorite: {
        chatElement.setFavorite(value.toBool());
        Q_EMIT dataChanged(idx, idx, {TextAutoGenerateChatsModel::ChatRoles::Favorite});
        return true;
    }
    case ChatRoles::InProgress: {
        chatElement.setInProgress(value.toBool());
        Q_EMIT dataChanged(idx, idx, {TextAutoGenerateChatsModel::ChatRoles::InProgress});
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
    return u"ERROR"_s;
}

TextAutoGenerateMessagesModel *TextAutoGenerateChatsModel::messagesModel(const QByteArray &chatId) const
{
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        return (*it).messageModel();
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

void TextAutoGenerateChatsModel::removeDiscussion(const QByteArray &chatId)
{
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        const int i = std::distance(mChats.begin(), it);
        beginRemoveRows(QModelIndex(), i, i);
        mChats.removeAt(i);
        endRemoveRows();
    }
}

void TextAutoGenerateChatsModel::archiveDiscussion(const QByteArray &chatId, bool archive)
{
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        (*it).setArchived(archive);
        const int i = std::distance(mChats.begin(), it);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {Archived});
    }
}

bool TextAutoGenerateChatsModel::chatIsFavorited(const QByteArray &chatId) const
{
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        return (*it).favorite();
    }
    return false;
}

bool TextAutoGenerateChatsModel::chatIsArchived(const QByteArray &chatId) const
{
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        return (*it).archived();
    }
    return false;
}

void TextAutoGenerateChatsModel::setChatInProgress(const QByteArray &chatId, bool state)
{
    if (chatId.isEmpty()) {
        return;
    }
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        (*it).setInProgress(state);
        const int i = std::distance(mChats.begin(), it);
        auto emitChanged = [this](int rowNumber, const QList<int> &roles = QList<int>()) {
            const QModelIndex index = createIndex(rowNumber, 0);
            Q_EMIT dataChanged(index, index, roles);
        };
        emitChanged(i, {InProgress});
    }
}

QString TextAutoGenerateChatsModel::title(const QByteArray &chatId) const
{
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        return (*it).title();
    }
    return {};
}

bool TextAutoGenerateChatsModel::isEmpty() const
{
    return false;
}

bool TextAutoGenerateChatsModel::chatInProgress(const QByteArray &chatId) const
{
    auto chatUuid = [&](const TextAutoGenerateChat &chat) {
        return chat.identifier() == chatId;
    };
    auto it = std::find_if(mChats.begin(), mChats.end(), chatUuid);
    if (it != mChats.end()) {
        return (*it).inProgress();
    }
    return false;
}

QList<QByteArray> TextAutoGenerateChatsModel::chatsId() const
{
    QList<QByteArray> lst;
    for (const TextAutoGenerateChat &chat : mChats) {
        lst.append(chat.identifier());
    }
    return lst;
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
