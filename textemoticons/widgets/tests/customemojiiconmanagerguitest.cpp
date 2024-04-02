/*
    SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customemojiiconmanagerguitest.h"
using namespace Qt::Literals::StringLiterals;

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
    if (customIdentifier == ":custom1:"_L1) {
        return QIcon::fromTheme(QStringLiteral("view-refresh"));
    } else if (customIdentifier == ":custom2:"_L1) {
        return QIcon::fromTheme(QStringLiteral("lock"));
    } else if (customIdentifier == ":gif1:"_L1) {
        return {};
    }
    return {};
}

QString CustomEmojiIconManagerGuiTest::fileName(const QString &customIdentifier)
{
    if (customIdentifier == ":gif1:"_L1) {
        return QStringLiteral(":/gif1");
    }
    return {};
}

#include "moc_customemojiiconmanagerguitest.cpp"
