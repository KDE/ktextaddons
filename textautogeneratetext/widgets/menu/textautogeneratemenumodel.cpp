/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

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
    if (!index.isValid()) {
        return Qt::ItemIsDropEnabled; // allow dropping between items
    }
    return Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled | QAbstractListModel::flags(index);
}

Qt::DropActions TextAutoGenerateMenuModel::supportedDropActions() const
{
    return Qt::MoveAction;
}

Qt::DropActions TextAutoGenerateMenuModel::supportedDragActions() const
{
    return Qt::MoveAction;
}

QStringList TextAutoGenerateMenuModel::mimeTypes() const
{
    return {QString::fromLatin1("application/x-autogenerate-menu")};
}

bool TextAutoGenerateMenuModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    if (!beginMoveRows(sourceParent, sourceRow, sourceRow + count - 1, destinationParent, destinationChild)) {
        return false; // invalid move, e.g. no-op (move row 2 to row 2 or to row 3)
    }

    for (int i = 0; i < count; ++i) {
        mTextInfos.move(sourceRow + i, destinationChild + (sourceRow > destinationChild ? 0 : -1));
    }
    for (int i = 0; i < mTextInfos.count(); ++i) {
        mTextInfos[i].setOrder(i);
    }
    endMoveRows();
    return true;
}

#include "moc_textautogeneratemenumodel.cpp"
