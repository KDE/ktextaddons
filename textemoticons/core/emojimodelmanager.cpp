/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emojimodelmanager.h"

#include "unicodeemoticonmanager.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <TextEmoticonsCore/EmojiModel>
using namespace TextEmoticonsCore;

class EmojiModelManager::EmojiModelManagerPrivate
{
public:
    EmojiModelManagerPrivate(EmojiModelManager *q)
        : mEmojiModel(new TextEmoticonsCore::EmojiModel(q))
    {
        mEmojiModel->setUnicodeEmoticonList(TextEmoticonsCore::UnicodeEmoticonManager::self()->unicodeEmojiList());
    }
    void loadRecentUsed()
    {
        // Try reading the old key first
        KConfigGroup group(KSharedConfig::openConfig(), QStringLiteral("EmoticonRecentUsed"));
        if (group.hasKey("Recents")) {
            mRecentIdentifier = group.readEntry("Recents", QStringList());
            // Make sure to clean up the old key, so we don't read it again
            group.deleteEntry("Recents");
            group.sync();
        } else {
            // Read the new key from state config
            group = KConfigGroup(KSharedConfig::openStateConfig(), mSettingsGroupName);
            mRecentIdentifier = group.readEntry("LastUsedEmojis", QStringList());
        }
    }

    void writeRecentUsed()
    {
        KConfigGroup group(KSharedConfig::openStateConfig(), mSettingsGroupName);
        group.writeEntry("LastUsedEmojis", mRecentIdentifier);
        group.sync();
    }

    QString mSettingsGroupName = QStringLiteral("EmoticonRecentUsed");
    TextEmoticonsCore::EmojiModel *const mEmojiModel;
    QStringList mRecentIdentifier;
    QStringList mExcludeEmoticons;
};

EmojiModelManager::EmojiModelManager(QObject *parent)
    : QObject(parent)
    , d(new EmojiModelManagerPrivate(this))
{
    d->loadRecentUsed();
}

EmojiModelManager::~EmojiModelManager()
{
    d->writeRecentUsed();
}

EmojiModelManager *EmojiModelManager::self()
{
    static EmojiModelManager s_self;
    return &s_self;
}

TextEmoticonsCore::EmojiModel *EmojiModelManager::emojiModel() const
{
    return d->mEmojiModel;
}

void EmojiModelManager::setRecentSettingsGroupName(const QString &key)
{
    d->mSettingsGroupName = key;
    d->loadRecentUsed();
}

const QStringList &EmojiModelManager::recentIdentifier() const
{
    return d->mRecentIdentifier;
}

void EmojiModelManager::setRecentIdentifier(const QStringList &newRecentIdentifier)
{
    d->mRecentIdentifier = newRecentIdentifier;
    d->writeRecentUsed();
    Q_EMIT usedIdentifierChanged(d->mRecentIdentifier);
}

void EmojiModelManager::addIdentifier(const QString &identifier)
{
    if (int i = d->mRecentIdentifier.indexOf(identifier)) {
        // Remove it for adding in top of list
        if (i != -1) {
            d->mRecentIdentifier.removeAt(i);
        }
    }
    d->mRecentIdentifier.prepend(identifier);
    d->writeRecentUsed();
    Q_EMIT usedIdentifierChanged(d->mRecentIdentifier);
}

CustomEmojiIconManager *EmojiModelManager::customEmojiIconManager() const
{
    return d->mEmojiModel->customEmojiIconManager();
}

void EmojiModelManager::setCustomEmojiIconManager(CustomEmojiIconManager *newCustomEmojiIconManager)
{
    d->mEmojiModel->setCustomEmojiIconManager(newCustomEmojiIconManager);
}

QStringList EmojiModelManager::excludeEmoticons() const
{
    return d->mExcludeEmoticons;
}

void EmojiModelManager::setExcludeEmoticons(const QStringList &emoticons)
{
    if (d->mExcludeEmoticons != emoticons) {
        d->mExcludeEmoticons = emoticons;
        d->mEmojiModel->setExcludeEmoticons(d->mExcludeEmoticons);
        Q_EMIT excludeEmoticonsChanged();
    }
}

#include "moc_emojimodelmanager.cpp"
