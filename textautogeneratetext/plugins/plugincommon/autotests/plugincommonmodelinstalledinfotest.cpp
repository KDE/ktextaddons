/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "plugincommonmodelinstalledinfotest.h"
#include <QTest>
QTEST_GUILESS_MAIN(PluginCommonModelInstalledInfoTest)

PluginCommonModelInstalledInfoTest::PluginCommonModelInstalledInfoTest(QObject *parent)
    : QObject{parent}
{
}

void PluginCommonModelInstalledInfoTest::shouldHaveDefaultValues()
{
    TestModelInstalledInfo w;
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.model().isEmpty());
    QVERIFY(w.quantizationLevel().isEmpty());
    QVERIFY(w.parameterSize().isEmpty());
    QCOMPARE(w.categories().toInt(), 0);
}

#include "moc_plugincommonmodelinstalledinfotest.cpp"
