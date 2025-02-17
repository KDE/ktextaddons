/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emojisortfilterproxymodel.h"
#include "emojimodel.h"
#include "emoticonunicodeutils.h"

using namespace TextEmoticonsCore;

class EmojiSortFilterProxyModel::EmojiProxyModelPrivate
{
public:
    EmojiProxyModelPrivate(EmojiSortFilterProxyModel *qq)
        : q(qq)
    {
    }
    void clearSearch()
    {
        q->setSearchIdentifier(QString());
    }
    QString mCategory;
    QStringList mRecentEmoticons;
    QString mSearchIdentifier;
    EmojiSortFilterProxyModel *const q;
};

EmojiSortFilterProxyModel::EmojiSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , d(new EmojiSortFilterProxyModel::EmojiProxyModelPrivate(this))
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(EmojiModel::Identifier);
    sort(0);
}

EmojiSortFilterProxyModel::~EmojiSortFilterProxyModel() = default;

bool EmojiSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (d->mCategory.isEmpty()) {
        return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
        return false;
    }
    if (!d->mSearchIdentifier.isEmpty()) {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const QString identifier = sourceIndex.data(EmojiModel::Identifier).toString();
        if (identifier.contains(d->mSearchIdentifier)) {
            return true;
        }
        return false;
    }
    if (d->mCategory == TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier()) {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const QString identifier = sourceIndex.data(EmojiModel::Identifier).toString();
        if (d->mRecentEmoticons.contains(identifier)) {
            return true;
        }
    } else {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const auto category = sourceIndex.data(EmojiModel::Category).toString();
        if (d->mCategory == category) {
            return true;
        }
    }
    return false;
}

QString EmojiSortFilterProxyModel::searchIdentifier() const
{
    return d->mSearchIdentifier;
}

void EmojiSortFilterProxyModel::setSearchIdentifier(const QString &newSearchIdentifier)
{
    if (d->mSearchIdentifier != newSearchIdentifier) {
        d->mSearchIdentifier = newSearchIdentifier;
        invalidateFilter();
    }
}

QStringList EmojiSortFilterProxyModel::recentEmoticons() const
{
    return d->mRecentEmoticons;
}

void EmojiSortFilterProxyModel::setRecentEmoticons(const QStringList &newRecentEmoticons)
{
    if (d->mRecentEmoticons != newRecentEmoticons) {
        d->mRecentEmoticons = newRecentEmoticons;
        if (TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier() == d->mCategory) {
            invalidate();
        }
        Q_EMIT recentEmoticonsChanged();
    }
}

QString EmojiSortFilterProxyModel::category() const
{
    return d->mCategory;
}

void EmojiSortFilterProxyModel::setCategory(const QString &newCategorie)
{
    if (d->mCategory != newCategorie) {
        d->mCategory = newCategorie;
        if (!d->mSearchIdentifier.isEmpty()) {
            d->clearSearch();
        } else {
            invalidateFilter();
        }
        if ((TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier() == d->mCategory)
            || (TextEmoticonsCore::EmoticonUnicodeUtils::customIdentifier() == d->mCategory)) {
            // Make sure that we reorder recent/custom category
            invalidate();
        }
        Q_EMIT categoryChanged();
    }
}

bool EmojiSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier() == d->mCategory) {
        const QString leftIdentifier = sourceModel()->data(left, EmojiModel::Identifier).toString();
        const QString rightIdentifier = sourceModel()->data(right, EmojiModel::Identifier).toString();
        const int positionIdentifierLeft = d->mRecentEmoticons.indexOf(leftIdentifier);
        const int positionIdentifierRight = d->mRecentEmoticons.indexOf(rightIdentifier);
        //        qDebug() << " leftIdentifier " << leftIdentifier << " rightIdentifier " << rightIdentifier << " positionIdentifierLeft " <<
        //        positionIdentifierLeft
        //                 << " positionIdentifierRight " << positionIdentifierRight;
        //        qDebug() << "mRecentEmoticons  " << mRecentEmoticons;
        return positionIdentifierLeft < positionIdentifierRight;
    } else {
        const int leftOrder = sourceModel()->data(left, EmojiModel::Order).toInt();
        const int rightOrder = sourceModel()->data(right, EmojiModel::Order).toInt();

        return leftOrder < rightOrder;
    }
}

#include "moc_emojisortfilterproxymodel.cpp"
