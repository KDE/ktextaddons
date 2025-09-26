/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emojimodelmanager.h"
using namespace Qt::Literals::StringLiterals;

#include "unicodeemoticonmanager.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <TextEmoticonsCore/EmojiModel>
using namespace TextEmoticonsCore;

class EmojiModelManager::EmojiModelManagerPrivate
{
public:
    explicit EmojiModelManagerPrivate(QObject *parent)
        : emojiModel(new TextEmoticonsCore::EmojiModel(parent))
    {
        emojiModel->setUnicodeEmoticonList(TextEmoticonsCore::UnicodeEmoticonManager::self()->unicodeEmojiList());
    }
    void loadSettings()
    {
        // Try reading the old key first
        KConfigGroup group(KSharedConfig::openConfig(), u"EmoticonRecentUsed"_s);
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
        tone = static_cast<EmojiModelManager::EmojiTone>(group.readEntry("Tone", static_cast<int>(EmojiModelManager::EmojiTone::Original)));
    }

    void writeSettings()
    {
        KConfigGroup group(KSharedConfig::openStateConfig(), settingsGroupName);
        group.writeEntry("LastUsedEmojis", recentIdentifier);
        group.writeEntry("Tone", static_cast<int>(tone));
        group.sync();
    }

    QString settingsGroupName = u"EmoticonRecentUsed"_s;
    TextEmoticonsCore::EmojiModel *const emojiModel;
    QStringList recentIdentifier;
    QStringList excludeEmoticons;
    EmojiModelManager::EmojiTone tone = EmojiModelManager::EmojiTone::All;
};

EmojiModelManager::EmojiModelManager(QObject *parent)
    : QObject(parent)
    , d(new EmojiModelManagerPrivate(this))
{
    d->loadSettings();
}

EmojiModelManager::~EmojiModelManager()
{
    d->writeSettings();
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
    d->loadSettings();
}

const QStringList &EmojiModelManager::recentIdentifier() const
{
    return d->recentIdentifier;
}

void EmojiModelManager::setRecentIdentifier(const QStringList &newRecentIdentifier)
{
    d->recentIdentifier = newRecentIdentifier;
    d->writeSettings();
    Q_EMIT usedIdentifierChanged(d->recentIdentifier);
}

void EmojiModelManager::addIdentifier(const QString &identifier)
{
    if (const int i = d->recentIdentifier.indexOf(identifier); i != -1) {
        // Remove it for adding in top of list
        d->recentIdentifier.removeAt(i);
    }
    d->recentIdentifier.prepend(identifier);
    d->writeSettings();
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

EmojiModelManager::EmojiTone EmojiModelManager::emojiTone() const
{
    return d->tone;
}

void EmojiModelManager::setEmojiTone(EmojiModelManager::EmojiTone tone)
{
    if (d->tone != tone) {
        d->tone = tone;
        d->writeSettings();
        Q_EMIT emojiToneChanged();
    }
}

#include "moc_emojimodelmanager.cpp"
