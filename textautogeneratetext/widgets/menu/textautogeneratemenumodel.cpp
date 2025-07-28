/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "textautogeneratemenumodel.h"
#include "textautogeneratetextwidget_menu_debug.h"
using namespace TextAutoGenerateText;
TextAutoGenerateMenuModel::TextAutoGenerateMenuModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

TextAutoGenerateMenuModel::~TextAutoGenerateMenuModel() = default;

int TextAutoGenerateMenuModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0; // flat model
    }
    return mTextInfos.count();
}

QVariant TextAutoGenerateMenuModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mTextInfos.count()) {
        return {};
    }

    const auto &textInfo = mTextInfos[index.row()];
    switch (role) {
    case Qt::DisplayRole:
    case TextRole:
        return textInfo.requestText();
    case Qt::CheckStateRole:
    case EnabledRole:
        return textInfo.enabled() ? Qt::Checked : Qt::Unchecked;
    default:
        break;
    }
    return {};
}

bool TextAutoGenerateMenuModel::setData(const QModelIndex &idx, const QVariant &value, int role)
{
    if (!idx.isValid()) {
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_MENU_LOG) << "ERROR: invalid index";
        return false;
    }
    const int id = idx.row();
    TextAutoGenerateMenuTextInfo &info = mTextInfos[id];
    switch (role) {
    case AiTextRoles::TextRole: {
        info.setRequestText(value.toString());
        const QModelIndex newIndex = index(idx.row(), AiTextRoles::TextRole);
        Q_EMIT dataChanged(newIndex, newIndex);
        return true;
    }
    case Qt::CheckStateRole:
    case AiTextRoles::EnabledRole:
        info.setEnabled(value.toBool());
        Q_EMIT dataChanged(idx, idx, {AiTextRoles::EnabledRole});
        return true;
    default:
        break;
    }
    return QAbstractListModel::setData(idx, value, role);
}

QList<TextAutoGenerateMenuTextInfo> TextAutoGenerateMenuModel::textInfos() const
{
    return mTextInfos;
}

void TextAutoGenerateMenuModel::setTextInfos(const QList<TextAutoGenerateMenuTextInfo> &newAskItems)
{
    beginResetModel();
    mTextInfos = newAskItems;
    endResetModel();
}

void TextAutoGenerateMenuModel::addItem(const TextAutoGenerateMenuTextInfo &msg)
{
    beginInsertRows(QModelIndex(), mTextInfos.count(), mTextInfos.count());
    mTextInfos.append(msg);
    endInsertRows();
}

void TextAutoGenerateMenuModel::removeInfo(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    mTextInfos.removeAt(index);
    endRemoveRows();
}

Qt::ItemFlags TextAutoGenerateMenuModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsUserCheckable | QAbstractListModel::flags(index);
}

#include "moc_textautogeneratemenumodel.cpp"
