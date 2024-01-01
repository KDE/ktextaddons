/*
   SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customemojiiconmanager.h"

using namespace TextEmoticonsCore;
CustomEmojiIconManager::CustomEmojiIconManager(QObject *parent)
    : QObject(parent)
{
}

CustomEmojiIconManager::~CustomEmojiIconManager()
{
}

QIcon CustomEmojiIconManager::generateIcon(const QString &customIdentifier)
{
    Q_UNUSED(customIdentifier)
    return {};
}

QString CustomEmojiIconManager::fileName(const QString &customIdentifier)
{
    Q_UNUSED(customIdentifier)
    return {};
}

#include "moc_customemojiiconmanager.cpp"
