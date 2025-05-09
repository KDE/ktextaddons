/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "customemojiiconmanagertest.h"
#include "customemojiiconmanager.h"
#include <QTest>
QTEST_GUILESS_MAIN(CustomEmojiIconManagerTest)
CustomEmojiIconManagerTest::CustomEmojiIconManagerTest(QObject *parent)
    : QObject{parent}
{
}

void CustomEmojiIconManagerTest::shouldHaveDefaultValues()
{
    TextEmoticonsCore::CustomEmojiIconManager w;
    // TODO
}

#include "moc_customemojiiconmanagertest.cpp"
