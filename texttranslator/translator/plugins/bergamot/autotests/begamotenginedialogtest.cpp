/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "begamotenginedialogtest.h"
#include "begamotenginedialog.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(BegamotEngineDialogTest)
BegamotEngineDialogTest::BegamotEngineDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void BegamotEngineDialogTest::shouldHaveDefaultValues()
{
    BegamotEngineDialog w;
    // TODO
}

#include "moc_begamotenginedialogtest.cpp"
