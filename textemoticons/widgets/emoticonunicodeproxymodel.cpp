/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emoticonunicodeproxymodel.h"
#include "emoticonunicodemodel.h"
using namespace TextEmoticonsWidgets;
EmoticonUnicodeProxyModel::EmoticonUnicodeProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(EmoticonUnicodeModel::Identifier);
}

EmoticonUnicodeProxyModel::~EmoticonUnicodeProxyModel() = default;

bool EmoticonUnicodeProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mCategory.isEmpty()) {
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    }
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    const auto category = sourceIndex.data(EmoticonUnicodeModel::Category).toString();
    if (mCategory == category) {
        return true;
    }
    return false;
}

QString EmoticonUnicodeProxyModel::category() const
{
    return mCategory;
}

void EmoticonUnicodeProxyModel::setCategory(const QString &newCategorie)
{
    mCategory = newCategorie;
}
