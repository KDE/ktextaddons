/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customemojiiconmanager.h"

using namespace TextEmoticonsCore;
CustomEmojiIconManager::CustomEmojiIconManager(QObject *parent)
    : QObject(parent)
{
}

CustomEmojiIconManager::~CustomEmojiIconManager() = default;

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
