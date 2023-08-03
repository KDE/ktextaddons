/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotutilstest.h"
#include "bergamotutils.h"
#include <QTest>

QTEST_GUILESS_MAIN(BergamotUtilsTest)
BergamotUtilsTest::BergamotUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void BergamotUtilsTest::shouldDefaultBergamotRepository()
{
    QCOMPARE(BergamotUtils::defaultBergamotRepository(), QStringLiteral("https://translatelocally.com/models.json"));
}
