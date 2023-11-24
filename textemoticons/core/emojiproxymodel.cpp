/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emojiproxymodel.h"
#include "emojimodel.h"
#include "emoticonunicodeutils.h"

using namespace TextEmoticonsCore;

class EmojiProxyModel::EmojiProxyModelPrivate
{
public:
    EmojiProxyModelPrivate(EmojiProxyModel *qq)
        : q(qq)
    {
    }
    void clearSearch()
    {
        q->setSearchIdentifier(QString());
    }
    bool emoticonAccepted(const QString &identifier) const
    {
        if (mExcludeEmoticons.contains(identifier)) {
            return false;
        }
        return true;
    }
    QString mCategory;
    QStringList mExcludeEmoticons;
    QStringList mRecentEmoticons;
    QString mSearchIdentifier;
    EmojiProxyModel *const q;
};

EmojiProxyModel::EmojiProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , d(new EmojiProxyModel::EmojiProxyModelPrivate(this))
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(EmojiModel::Identifier);
    sort(0);
}

EmojiProxyModel::~EmojiProxyModel() = default;

bool EmojiProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (d->mCategory.isEmpty()) {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const QString identifier = sourceIndex.data(EmojiModel::Identifier).toString();
        if (d->emoticonAccepted(identifier)) {
            return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
        }
        return false;
    }
    if (!d->mSearchIdentifier.isEmpty()) {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const QString identifier = sourceIndex.data(EmojiModel::Identifier).toString();
        if (d->emoticonAccepted(identifier) && identifier.contains(d->mSearchIdentifier)) {
            return true;
        }
        return false;
    }
    if (d->mCategory == TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier()) {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const QString identifier = sourceIndex.data(EmojiModel::Identifier).toString();
        if (d->emoticonAccepted(identifier) && d->mRecentEmoticons.contains(identifier)) {
            return true;
        }
    } else {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const auto category = sourceIndex.data(EmojiModel::Category).toString();
        const QString identifier = sourceIndex.data(EmojiModel::Identifier).toString();
        if (d->emoticonAccepted(identifier) && d->mCategory == category) {
            return true;
        }
    }
    return false;
}

QString EmojiProxyModel::searchIdentifier() const
{
    return d->mSearchIdentifier;
}

void EmojiProxyModel::setSearchIdentifier(const QString &newSearchIdentifier)
{
    if (d->mSearchIdentifier != newSearchIdentifier) {
        d->mSearchIdentifier = newSearchIdentifier;
        invalidateFilter();
    }
}

QStringList EmojiProxyModel::excludeEmoticons() const
{
    return d->mExcludeEmoticons;
}

void EmojiProxyModel::setExcludeEmoticons(const QStringList &emoticons)
{
    if (d->mExcludeEmoticons != emoticons) {
        d->mExcludeEmoticons = emoticons;
        invalidateFilter();
    }
}

QStringList EmojiProxyModel::recentEmoticons() const
{
    return d->mRecentEmoticons;
}

void EmojiProxyModel::setRecentEmoticons(const QStringList &newRecentEmoticons)
{
    if (d->mRecentEmoticons != newRecentEmoticons) {
        d->mRecentEmoticons = newRecentEmoticons;
        if (TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier() == d->mCategory) {
            invalidate();
        }
    }
}

QString EmojiProxyModel::category() const
{
    return d->mCategory;
}

void EmojiProxyModel::setCategory(const QString &newCategorie)
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
    }
}

bool EmojiProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
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

#include "moc_emojiproxymodel.cpp"
