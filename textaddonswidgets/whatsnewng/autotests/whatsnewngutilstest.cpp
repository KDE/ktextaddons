/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "whatsnewngutilstest.h"
#include "whatsnewng/whatsnewngutils.h"
#include <QTest>

QTEST_GUILESS_MAIN(WhatsNewNgUtilsTest)

WhatsNewNgUtilsTest::WhatsNewNgUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void WhatsNewNgUtilsTest::shouldHaveDefaultValues()
{
    QCOMPARE(TextAddonsWidgets::WhatsNewNgUtils::allVersion(), -1);
}
#include "moc_whatsnewngutilstest.cpp"
