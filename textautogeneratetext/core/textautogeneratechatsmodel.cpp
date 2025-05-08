/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratechatsmodel.h"
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
        break;
    case Title:
        return {}; // TODO
    case Identifier:
        return chat.identifier();
    case Favorite:
        return chat.favorite();
    case Archived:
        return chat.archived();
    }
    return {};
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
        /*
        msg.setTi(value.toString());
        const QModelIndex newIndex = index(idx.row(), MessageRoles::TopicRole);
        Q_EMIT dataChanged(newIndex, newIndex);
        */
        return true;
    }
        // TODO
    case ChatRoles::Archived:
    case ChatRoles::Favorite:
        return false;
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

#include "moc_textautogeneratechatsmodel.cpp"
