/*
    SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customemojiiconmanagerguitest.h"

#include <QIcon>
using namespace Qt::Literals::StringLiterals;
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
        return QIcon::fromTheme(u"view-refresh"_s);
    } else if (customIdentifier == ":custom2:"_L1) {
        return QIcon::fromTheme(u"lock"_s);
    } else if (customIdentifier == ":gif1:"_L1) {
        return {};
    }
    return {};
}

QString CustomEmojiIconManagerGuiTest::fileName(const QString &customIdentifier)
{
    if (customIdentifier == ":gif1:"_L1) {
        return u":/gif1"_s;
    }
    return {};
}

#include "moc_customemojiiconmanagerguitest.cpp"
