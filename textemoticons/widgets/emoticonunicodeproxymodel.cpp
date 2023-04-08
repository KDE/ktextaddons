/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emoticonunicodeproxymodel.h"
#include "emoticonunicodemodel.h"
#include "emoticonutils.h"
using namespace TextEmoticonsWidgets;
EmoticonUnicodeProxyModel::EmoticonUnicodeProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(EmoticonUnicodeModel::Identifier);
}

EmoticonUnicodeProxyModel::~EmoticonUnicodeProxyModel() = default;

void EmoticonUnicodeProxyModel::clearSearch()
{
    setSearchIdentifier(QString());
}

bool EmoticonUnicodeProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mCategory.isEmpty()) {
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    }
    if (!mSearchIdentifier.isEmpty()) {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const QString identifier = sourceIndex.data(EmoticonUnicodeModel::Identifier).toString();
        if (identifier.contains(mSearchIdentifier)) {
            return true;
        }
        return false;
    }
    if (mCategory == TextEmoticonsWidgets::EmoticonUtils::recentIdentifier()) {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const QString identifier = sourceIndex.data(EmoticonUnicodeModel::Identifier).toString();
        if (mRecentEmoticons.contains(identifier)) {
            return true;
        }
    } else {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const auto category = sourceIndex.data(EmoticonUnicodeModel::Category).toString();
        if (mCategory == category) {
            return true;
        }
    }
    return false;
}

QString EmoticonUnicodeProxyModel::searchIdentifier() const
{
    return mSearchIdentifier;
}

void EmoticonUnicodeProxyModel::setSearchIdentifier(const QString &newSearchIdentifier)
{
    qDebug() << " void EmoticonUnicodeProxyModel::setSearchIdentifier(const QString &newSearchIdentifier)" << newSearchIdentifier;
    if (mSearchIdentifier != newSearchIdentifier) {
        mSearchIdentifier = newSearchIdentifier;
        invalidateFilter();
    }
}

QStringList EmoticonUnicodeProxyModel::recentEmoticons() const
{
    return mRecentEmoticons;
}

void EmoticonUnicodeProxyModel::setRecentEmoticons(const QStringList &newRecentEmoticons)
{
    if (mRecentEmoticons != newRecentEmoticons) {
        mRecentEmoticons = newRecentEmoticons;
        if (TextEmoticonsWidgets::EmoticonUtils::recentIdentifier() == mCategory) {
            invalidate();
        }
    }
}

QString EmoticonUnicodeProxyModel::category() const
{
    return mCategory;
}

void EmoticonUnicodeProxyModel::setCategory(const QString &newCategorie)
{
    if (mCategory != newCategorie) {
        mCategory = newCategorie;
        invalidateFilter();
    }
}
