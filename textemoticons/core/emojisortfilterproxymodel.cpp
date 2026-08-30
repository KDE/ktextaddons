/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "emojisortfilterproxymodel.h"
#include "emojimodel.h"
#include "emoticonunicodeutils.h"

#include <algorithm>
using namespace Qt::Literals::StringLiterals;
using namespace TextEmoticonsCore;

class EmojiSortFilterProxyModel::EmojiProxyModelPrivate
{
public:
    explicit EmojiProxyModelPrivate(EmojiSortFilterProxyModel *qq)
        : q(qq)
    {
    }
    void clearSearch()
    {
        q->setSearchIdentifier(QString());
    }

    [[nodiscard]] QLatin1StringView emojiToneSuffix() const
    {
        switch (tone) {
        case EmojiModelManager::EmojiTone::All:
        case EmojiModelManager::EmojiTone::Original:
            return {};
        case EmojiModelManager::EmojiTone::Light:
            return "_tone1"_L1;
        case EmojiModelManager::EmojiTone::MediumLight:
            return "_tone2"_L1;
        case EmojiModelManager::EmojiTone::Medium:
            return "_tone3"_L1;
        case EmojiModelManager::EmojiTone::MediumDark:
            return "_tone4"_L1;
        case EmojiModelManager::EmojiTone::Dark:
            return "_tone5"_L1;
        }
        return {};
    }

    bool filterTone(const QModelIndex &sourceIndex) const
    {
        if (tone == EmojiModelManager::EmojiTone::Original) {
            return !sourceIndex.data(EmojiModel::Identifier).toString().contains("_tone"_L1);
        }
        const QLatin1StringView suffix = emojiToneSuffix();
        if (suffix.isEmpty()) {
            return true;
        }
        if (const bool diversityChildren = sourceIndex.data(EmojiModel::DiversityChildren).toBool(); diversityChildren) {
            return false;
        }
        const QString identifier = sourceIndex.data(EmojiModel::Identifier).toString();
        // Match the suffix at the end of the identifier: :handshake_tone1-3: is a
        // mixed tone emoji, it belongs to no single tone.
        // chopped() on a QStringView keeps this allocation-free; QString::chopped() would copy.
        return !identifier.contains("_tone"_L1) || (identifier.endsWith(u':') && QStringView(identifier).chopped(1).endsWith(suffix));
    }

    // Overload for callers that do not have the source index yet: when the tone filter accepts
    // everything there is no need to build one at all.
    bool filterTone(int source_row, const QModelIndex &source_parent) const
    {
        if (tone != EmojiModelManager::EmojiTone::Original && emojiToneSuffix().isEmpty()) {
            return true;
        }
        return filterTone(q->sourceModel()->index(source_row, 0, source_parent));
    }

    [[nodiscard]] bool matchesSearch(const QModelIndex &sourceIndex) const
    {
        if (sourceIndex.data(EmojiModel::Identifier).toString().contains(searchIdentifier, Qt::CaseInsensitive)) {
            return true;
        }
        // The identifier is the name used by the emoji set we ship; the names users
        // remember from elsewhere are aliases, so search those too.
        const QStringList aliases = sourceIndex.data(EmojiModel::Aliases).toStringList();
        return std::any_of(aliases.cbegin(), aliases.cend(), [this](const QString &alias) {
            return alias.contains(searchIdentifier, Qt::CaseInsensitive);
        });
    }

    QString category;
    QStringList recentEmoticons;
    QString searchIdentifier;
    EmojiModelManager::EmojiTone tone = EmojiModelManager::EmojiTone::All;
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
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    if (!d->searchIdentifier.isEmpty()) {
        return d->filterTone(sourceIndex) && d->matchesSearch(sourceIndex);
    }
    if (d->category == TextEmoticonsCore::EmoticonUnicodeUtils::recentIdentifier()) {
        if (const QString identifier = sourceIndex.data(EmojiModel::Identifier).toString(); d->recentEmoticons.contains(identifier)) {
            return true;
        }
    } else {
        if (const auto category = sourceIndex.data(EmojiModel::Category).toString(); d->filterTone(sourceIndex) && d->category == category) {
            return true;
        }
    }
    return false;
}

EmojiModelManager::EmojiTone EmojiSortFilterProxyModel::emojiTone() const
{
    return d->tone;
}

void EmojiSortFilterProxyModel::setEmojiTone(EmojiModelManager::EmojiTone tone)
{
    if (d->tone != tone) {
        beginFilterChange();
        d->tone = tone;
        endFilterChange(QSortFilterProxyModel::Direction::Rows);
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
        beginFilterChange();
        d->searchIdentifier = newSearchIdentifier;
        endFilterChange(QSortFilterProxyModel::Direction::Rows);
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
        if (!d->searchIdentifier.isEmpty()) {
            d->clearSearch();
        }
        beginFilterChange();
        d->category = newCategorie;
        endFilterChange(QSortFilterProxyModel::Direction::Rows);
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
    return QString::fromLatin1(d->emojiToneSuffix());
}

#include "moc_emojisortfilterproxymodel.cpp"
