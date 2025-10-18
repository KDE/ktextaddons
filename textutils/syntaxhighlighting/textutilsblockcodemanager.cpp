/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textutilsblockcodemanager.h"
#include <QDebug>

using namespace TextUtils;
TextUtilsBlockCodeManager *TextUtilsBlockCodeManager::self()
{
    static TextUtilsBlockCodeManager s_self;
    return &s_self;
}

void TextUtilsBlockCodeManager::insert(const QString &identifier, const QString &blockCode)
{
    // qDebug() << " identifier" << identifier << " blockCode " << blockCode;
    mCacheBlockCode.insert(identifier, blockCode);
    // qDebug() << " mCacheBlockCode " << mCacheBlockCode.size();
}

QString TextUtilsBlockCodeManager::blockCode(const QString &identifier) const
{
    return mCacheBlockCode.value(identifier);
}

void TextUtilsBlockCodeManager::clear()
{
    mCacheBlockCode.clear();
}
