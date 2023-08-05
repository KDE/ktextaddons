/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorproxymodel.h"
#include "translatormodel.h"

TranslatorProxyModel::TranslatorProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

TranslatorProxyModel::~TranslatorProxyModel() = default;

bool TranslatorProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (!mSearchString.isEmpty()) {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const QString source = sourceIndex.data(TranslatorModel::Source).toString();
        const QString target = sourceIndex.data(TranslatorModel::Target).toString();
        qDebug() << " source " << source << " target " << target;
        if (source.contains(mSearchString, Qt::CaseInsensitive) || target.contains(mSearchString, Qt::CaseInsensitive)) {
            return true;
        }
        return false;
    }
    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

QString TranslatorProxyModel::searchString() const
{
    return mSearchString;
}

void TranslatorProxyModel::setSearchString(const QString &newSearchString)
{
    if (mSearchString != newSearchString) {
        mSearchString = newSearchString;
        invalidateFilter();
    }
}

#include "moc_translatorproxymodel.cpp"
