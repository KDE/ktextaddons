/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "emoticonunicodemodelmanager.h"

#include "unicodeemoticonmanager.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <TextEmoticonsCore/EmojiModel>
using namespace TextEmoticonsCore;
namespace
{
static const char myEmoticonRecentUsedGroupName[] = "EmoticonRecentUsed";
}
EmoticonUnicodeModelManager::EmoticonUnicodeModelManager(QObject *parent)
    : QObject(parent)
    , mEmojiModel(new TextEmoticonsCore::EmojiModel(this))
{
    mEmojiModel->setUnicodeEmoticonList(TextEmoticonsCore::UnicodeEmoticonManager::self()->unicodeEmojiList());
    loadRecentUsed();
}

EmoticonUnicodeModelManager::~EmoticonUnicodeModelManager()
{
    writeRecentUsed();
}

EmoticonUnicodeModelManager *EmoticonUnicodeModelManager::self()
{
    static EmoticonUnicodeModelManager s_self;
    return &s_self;
}

TextEmoticonsCore::EmojiModel *EmoticonUnicodeModelManager::emojiModel() const
{
    return mEmojiModel;
}

const QStringList &EmoticonUnicodeModelManager::recentIdentifier() const
{
    return mRecentIdentifier;
}

void EmoticonUnicodeModelManager::setRecentIdentifier(const QStringList &newRecentIdentifier)
{
    mRecentIdentifier = newRecentIdentifier;
    writeRecentUsed();
    Q_EMIT usedIdentifierChanged(mRecentIdentifier);
}

void EmoticonUnicodeModelManager::addIdentifier(const QString &identifier)
{
    if (int i = mRecentIdentifier.indexOf(identifier)) {
        // Remove it for adding in top of list
        if (i != -1) {
            mRecentIdentifier.removeAt(i);
        }
    }
    mRecentIdentifier.prepend(identifier);
    writeRecentUsed();
    Q_EMIT usedIdentifierChanged(mRecentIdentifier);
}

CustomEmojiIconManager *EmoticonUnicodeModelManager::customEmojiIconManager() const
{
    return mEmojiModel->customEmojiIconManager();
}

void EmoticonUnicodeModelManager::setCustomEmojiIconManager(CustomEmojiIconManager *newCustomEmojiIconManager)
{
    mEmojiModel->setCustomEmojiIconManager(newCustomEmojiIconManager);
}

void EmoticonUnicodeModelManager::loadRecentUsed()
{
    KConfigGroup group(KSharedConfig::openConfig(), myEmoticonRecentUsedGroupName);
    mRecentIdentifier = group.readEntry("Recents", QStringList());
}

void EmoticonUnicodeModelManager::writeRecentUsed()
{
    KConfigGroup group(KSharedConfig::openConfig(), myEmoticonRecentUsedGroupName);
    group.writeEntry("Recents", mRecentIdentifier);
    group.sync();
}
