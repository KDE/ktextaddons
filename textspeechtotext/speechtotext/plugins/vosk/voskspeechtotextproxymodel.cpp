/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextproxymodel.h"
#include "voskspeechtotextmodel.h"

VoskSpeechToTextProxyModel::VoskSpeechToTextProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

VoskSpeechToTextProxyModel::~VoskSpeechToTextProxyModel() = default;

bool VoskSpeechToTextProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (!mSearchString.isEmpty()) {
        const QString source = sourceModel()->index(source_row, VoskSpeechToTextModel::LangText, source_parent).data().toString();
        if (source.contains(mSearchString, Qt::CaseInsensitive)) {
            return true;
        }
        return false;
    }
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

QString VoskSpeechToTextProxyModel::searchString() const
{
    return mSearchString;
}

void VoskSpeechToTextProxyModel::setSearchString(const QString &newSearchString)
{
    if (mSearchString != newSearchString) {
        mSearchString = newSearchString;
        invalidateFilter();
    }
}

bool VoskSpeechToTextProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (left.column() == VoskSpeechToTextModel::Size) {
        const QModelIndex leftOrder = left.sibling(left.row(), VoskSpeechToTextModel::SizeByte);
        const QModelIndex rightOrder = right.sibling(right.row(), VoskSpeechToTextModel::SizeByte);
        return leftOrder.data().toLongLong() < rightOrder.data().toLongLong();
    }
    return QSortFilterProxyModel::lessThan(left, right);
}

#include "moc_voskspeechtotextproxymodel.cpp"
