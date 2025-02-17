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
        : emojiModel(new TextEmoticonsCore::EmojiModel(q))
    {
        emojiModel->setUnicodeEmoticonList(TextEmoticonsCore::UnicodeEmoticonManager::self()->unicodeEmojiList());
    }
    void loadRecentUsed()
    {
        // Try reading the old key first
        KConfigGroup group(KSharedConfig::openConfig(), QStringLiteral("EmoticonRecentUsed"));
        if (group.hasKey("Recents")) {
            recentIdentifier = group.readEntry("Recents", QStringList());
            // Make sure to clean up the old key, so we don't read it again
            group.deleteEntry("Recents");
            group.sync();
        } else {
            // Read the new key from state config
            group = KConfigGroup(KSharedConfig::openStateConfig(), settingsGroupName);
            recentIdentifier = group.readEntry("LastUsedEmojis", QStringList());
        }
    }

    void writeRecentUsed()
    {
        KConfigGroup group(KSharedConfig::openStateConfig(), settingsGroupName);
        group.writeEntry("LastUsedEmojis", recentIdentifier);
        group.sync();
    }

    QString settingsGroupName = QStringLiteral("EmoticonRecentUsed");
    TextEmoticonsCore::EmojiModel *const emojiModel;
    QStringList recentIdentifier;
    QStringList excludeEmoticons;
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
    return d->emojiModel;
}

void EmojiModelManager::setRecentSettingsGroupName(const QString &key)
{
    d->settingsGroupName = key;
    d->loadRecentUsed();
}

const QStringList &EmojiModelManager::recentIdentifier() const
{
    return d->recentIdentifier;
}

void EmojiModelManager::setRecentIdentifier(const QStringList &newRecentIdentifier)
{
    d->recentIdentifier = newRecentIdentifier;
    d->writeRecentUsed();
    Q_EMIT usedIdentifierChanged(d->recentIdentifier);
}

void EmojiModelManager::addIdentifier(const QString &identifier)
{
    if (int i = d->recentIdentifier.indexOf(identifier)) {
        // Remove it for adding in top of list
        if (i != -1) {
            d->recentIdentifier.removeAt(i);
        }
    }
    d->recentIdentifier.prepend(identifier);
    d->writeRecentUsed();
    Q_EMIT usedIdentifierChanged(d->recentIdentifier);
}

CustomEmojiIconManager *EmojiModelManager::customEmojiIconManager() const
{
    return d->emojiModel->customEmojiIconManager();
}

void EmojiModelManager::setCustomEmojiIconManager(CustomEmojiIconManager *newCustomEmojiIconManager)
{
    d->emojiModel->setCustomEmojiIconManager(newCustomEmojiIconManager);
}

QStringList EmojiModelManager::excludeEmoticons() const
{
    return d->excludeEmoticons;
}

void EmojiModelManager::setExcludeEmoticons(const QStringList &emoticons)
{
    if (d->excludeEmoticons != emoticons) {
        d->excludeEmoticons = emoticons;
        d->emojiModel->setExcludeEmoticons(d->excludeEmoticons);
        Q_EMIT excludeEmoticonsChanged();
    }
}

#include "moc_emojimodelmanager.cpp"
