/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emojisortfilterproxymodel.h"
#include "emojimodel.h"
#include "emoticonunicodeutils.h"
using namespace Qt::Literals::StringLiterals;
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

    [[nodiscard]] QString emojiToneSuffix() const
    {
        switch (tone) {
        case EmojiSortFilterProxyModel::EmojiTone::All:
        case EmojiSortFilterProxyModel::EmojiTone::Original:
            return {};
        case EmojiSortFilterProxyModel::EmojiTone::Light:
            return "_tone1"_L1;
        case EmojiSortFilterProxyModel::EmojiTone::MediumLight:
            return "_tone2"_L1;
        case EmojiSortFilterProxyModel::EmojiTone::Medium:
            return "_tone3"_L1;
        case EmojiSortFilterProxyModel::EmojiTone::MediumDark:
            return "_tone4"_L1;
        case EmojiSortFilterProxyModel::EmojiTone::Dark:
            return "_tone5"_L1;
        }
        return {};
    }

    bool filterTone(int source_row, const QModelIndex &source_parent) const
    {
        const QString suffix = emojiToneSuffix();
        if (suffix.isEmpty()) {
            return true;
        } else {
            const QModelIndex sourceIndex = q->sourceModel()->index(source_row, 0, source_parent);
            const QString identifier = sourceIndex.data(EmojiModel::Identifier).toString();
            if (identifier.contains("_tone"_L1) && identifier.contains(suffix)) {
                return true;
            } else if (!identifier.contains("_tone"_L1)) {
                return true;
            }
            return false;
        }
    }

    QString category;
    QStringList recentEmoticons;
    QString searchIdentifier;
    EmojiSortFilterProxyModel::EmojiTone tone = EmojiSortFilterProxyModel::EmojiTone::All;
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
    if (d->category.isEmpty()) {
        return d->filterTone(source_row, source_parent) && QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
    }
    if (!d->searchIdentifier.isEmpty()) {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const QString identifier = sourceIndex.data(EmojiModel::Identifier).toString();
        if (d->filterTone(source_row, source_parent) && identifier.contains(d->searchIdentifier)) {
            return true;
        }
        return false;
    }
    if (d->category == TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier()) {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const QString identifier = sourceIndex.data(EmojiModel::Identifier).toString();
        if (d->recentEmoticons.contains(identifier)) {
            return true;
        }
    } else {
        const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
        const auto category = sourceIndex.data(EmojiModel::Category).toString();
        if (d->filterTone(source_row, source_parent) && d->category == category) {
            return true;
        }
    }
    return false;
}

EmojiSortFilterProxyModel::EmojiTone EmojiSortFilterProxyModel::emojiTone() const
{
    return d->tone;
}

void EmojiSortFilterProxyModel::setEmojiTone(EmojiSortFilterProxyModel::EmojiTone tone)
{
    if (d->tone != tone) {
        d->tone = tone;
        invalidateFilter();
        Q_EMIT emojiToneChanged();
    }
}

QString EmojiSortFilterProxyModel::searchIdentifier() const
{
    return d->searchIdentifier;
}

void EmojiSortFilterProxyModel::setSearchIdentifier(const QString &newSearchIdentifier)
{
    if (d->searchIdentifier != newSearchIdentifier) {
        d->searchIdentifier = newSearchIdentifier;
        invalidateFilter();
    }
}

QStringList EmojiSortFilterProxyModel::recentEmoticons() const
{
    return d->recentEmoticons;
}

void EmojiSortFilterProxyModel::setRecentEmoticons(const QStringList &newRecentEmoticons)
{
    if (d->recentEmoticons != newRecentEmoticons) {
        d->recentEmoticons = newRecentEmoticons;
        if (TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier() == d->category) {
            invalidate();
        }
        Q_EMIT recentEmoticonsChanged();
    }
}

QString EmojiSortFilterProxyModel::category() const
{
    return d->category;
}

void EmojiSortFilterProxyModel::setCategory(const QString &newCategorie)
{
    if (d->category != newCategorie) {
        d->category = newCategorie;
        if (!d->searchIdentifier.isEmpty()) {
            d->clearSearch();
        } else {
            invalidateFilter();
        }
        if ((TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier() == d->category)
            || (TextEmoticonsCore::EmoticonUnicodeUtils::customIdentifier() == d->category)) {
            // Make sure that we reorder recent/custom category
            invalidate();
        }
        Q_EMIT categoryChanged();
    }
}

bool EmojiSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    if (TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier() == d->category) {
        const QString leftIdentifier = sourceModel()->data(left, EmojiModel::Identifier).toString();
        const QString rightIdentifier = sourceModel()->data(right, EmojiModel::Identifier).toString();
        const int positionIdentifierLeft = d->recentEmoticons.indexOf(leftIdentifier);
        const int positionIdentifierRight = d->recentEmoticons.indexOf(rightIdentifier);
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

QString EmojiSortFilterProxyModel::emojiToneSuffix() const
{
    return d->emojiToneSuffix();
}
#include "moc_emojisortfilterproxymodel.cpp"
