/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineutilstest.h"
#include "bergamotengineutils.h"
#include <QTest>

QTEST_GUILESS_MAIN(BergamotEngineUtilsTest)
BergamotEngineUtilsTest::BergamotEngineUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void BergamotEngineUtilsTest::shouldDefaultBergamotRepository()
{
    QCOMPARE(BergamotEngineUtils::defaultBergamotRepository(), QStringLiteral("https://translatelocally.com/models.json"));
}
