/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateblockcodemanager.h"
#include <QDebug>

using namespace TextAutoGenerateText;
TextAutoGenerateBlockCodeManager *TextAutoGenerateBlockCodeManager::self()
{
    static TextAutoGenerateBlockCodeManager s_self;
    return &s_self;
}

void TextAutoGenerateBlockCodeManager::insert(const QString &identifier, const QString &blockCode)
{
    // qDebug() << " identifier" << identifier << " blockCode " << blockCode;
    mCacheBlockCode.insert(identifier, blockCode);
}

QString TextAutoGenerateBlockCodeManager::blockCode(const QString &identifier) const
{
    return mCacheBlockCode.value(identifier);
}
