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
        return QVariant::fromValue(section(chat));
    case DateTime:
        return dateTime(chat);
    }
    return {};
}

QString TextAutoGenerateChatsModel::title(const TextAutoGenerateChat &chat) const
{
    return chat.title();
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
        const QModelIndex newIndex = index(idx.row(), TextAutoGenerateChatsModel::ChatRoles::Title);
        Q_EMIT dataChanged(newIndex, newIndex);
        return true;
    }
    case ChatRoles::Archived: {
        chat.setArchived(value.toBool());
        const QModelIndex newIndex = index(idx.row(), TextAutoGenerateChatsModel::ChatRoles::Archived);
        Q_EMIT dataChanged(newIndex, newIndex);
        return true;
    }
    case ChatRoles::Favorite: {
        chat.setFavorite(value.toBool());
        const QModelIndex newIndex = index(idx.row(), TextAutoGenerateChatsModel::ChatRoles::Favorite);
        Q_EMIT dataChanged(newIndex, newIndex);
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

QString TextAutoGenerateChatsModel::sectionName(SectionHistory sectionId)
{
    switch (sectionId) {
    case TextAutoGenerateChatsModel::SectionHistory::Favorite:
        return i18n("Favorite");
    case TextAutoGenerateChatsModel::SectionHistory::Today:
        return i18n("Today");
    case TextAutoGenerateChatsModel::SectionHistory::LessThanSevenDays:
        return i18n("7 days previous");
    case TextAutoGenerateChatsModel::SectionHistory::LessThanThirtyDays:
        return i18n("30 days previous");
    case TextAutoGenerateChatsModel::SectionHistory::Later:
        return i18n("Later");
    case TextAutoGenerateChatsModel::SectionHistory::Unknown:
        return i18n("Unknown");
    case TextAutoGenerateChatsModel::SectionHistory::NSections:
        break;
    }
    return QStringLiteral("ERROR");
}

TextAutoGenerateChatsModel::SectionHistory TextAutoGenerateChatsModel::section(const TextAutoGenerateChat &chat) const
{
    if (!chat.messageModel() || chat.messageModel()->messages().isEmpty()) {
        return TextAutoGenerateChatsModel::SectionHistory::Unknown;
    }
    return section(chat.messageModel()->messages().constLast());
}

TextAutoGenerateChatsModel::SectionHistory TextAutoGenerateChatsModel::section(const TextAutoGenerateMessage &m) const
{
    if (m.dateTime() == -1) {
        return TextAutoGenerateChatsModel::SectionHistory::Unknown;
    }
    const QDate d = QDateTime::fromSecsSinceEpoch(m.dateTime()).date();
    if (d == QDate::currentDate()) {
        return TextAutoGenerateChatsModel::SectionHistory::Today;
    } else if (d < QDate::currentDate().addDays(7)) {
        return TextAutoGenerateChatsModel::SectionHistory::LessThanSevenDays;
    } else if (d < QDate::currentDate().addDays(30)) {
        return TextAutoGenerateChatsModel::SectionHistory::LessThanThirtyDays;
    } else {
        return TextAutoGenerateChatsModel::SectionHistory::Later;
    }
    return TextAutoGenerateChatsModel::SectionHistory::Unknown;
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

#include "moc_textautogeneratechatsmodel.cpp"
