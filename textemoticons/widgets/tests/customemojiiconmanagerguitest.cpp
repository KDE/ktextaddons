/*
    SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customemojiiconmanagerguitest.h"
#include <QDebug>
#include <QIcon>
CustomEmojiIconManagerGuiTest::CustomEmojiIconManagerGuiTest(QObject *parent)
    : TextEmoticonsCore::CustomEmojiIconManager(parent)
{
}

CustomEmojiIconManagerGuiTest::~CustomEmojiIconManagerGuiTest()
{
}

QIcon CustomEmojiIconManagerGuiTest::generateIcon(const QString &customIdentifier)
{
    if (customIdentifier == QLatin1String(":custom1:")) {
        return QIcon::fromTheme(QStringLiteral("view-refresh"));
    } else if (customIdentifier == QLatin1String(":custom2:")) {
        return QIcon::fromTheme(QStringLiteral("lock"));
    } else if (customIdentifier == QLatin1String(":gif1:")) {
        return {};
    }
    return {};
}

QString CustomEmojiIconManagerGuiTest::fileName(const QString &customIdentifier)
{
    if (customIdentifier == QLatin1String(":gif1:")) {
        return QStringLiteral(":/gif1");
    }
    return {};
}

#include "moc_customemojiiconmanagerguitest.cpp"
