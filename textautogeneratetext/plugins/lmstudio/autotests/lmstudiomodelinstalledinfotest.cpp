/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lmstudiomodelinstalledinfotest.h"
#include "modelsmanager/lmstudiomodelinstalledinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(LMStudioModelInstalledInfoTest)

LMStudioModelInstalledInfoTest::LMStudioModelInstalledInfoTest(QObject *parent)
    : QObject{parent}
{
}

void LMStudioModelInstalledInfoTest::shouldHaveDefaultValues()
{
    LMStudioModelInstalledInfo w;
    // Values from parent class
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.model().isEmpty());
    QVERIFY(w.quantizationLevel().isEmpty());
    QVERIFY(w.parameterSize().isEmpty());
    QCOMPARE(w.categories().toInt(), 0);

    // Values from LMStudioModelInstalledInfo
    QVERIFY(w.publisher().isEmpty());
}

#include "moc_lmstudiomodelinstalledinfotest.cpp"
