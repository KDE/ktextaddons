/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

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

#include "moc_voskspeechtotextproxymodel.cpp"
