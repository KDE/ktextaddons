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

QIcon CustomEmojiIconManager::generateIcon([[maybe_unused]] const QString &customIdentifier)
{
    return {};
}

QString CustomEmojiIconManager::fileName([[maybe_unused]] const QString &customIdentifier)
{
    return {};
}

#include "moc_customemojiiconmanager.cpp"
