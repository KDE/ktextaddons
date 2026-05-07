/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "plugincommonmodelinstalledinfossortproxymodeltest.h"
#include "plugincommonmodelinstalledinfossortproxymodel.h"
#include <QTest>
QTEST_MAIN(PluginCommonModelInstalledInfosSortProxyModelTest)

PluginCommonModelInstalledInfosSortProxyModelTest::PluginCommonModelInstalledInfosSortProxyModelTest(QObject *parent)
    : QObject{parent}
{
}

void PluginCommonModelInstalledInfosSortProxyModelTest::shouldHaveDefaultValues()
{
    const PluginCommonModelInstalledInfosSortProxyModel w;
    QCOMPARE(w.filterCaseSensitivity(), Qt::CaseInsensitive);
    QCOMPARE(w.sortCaseSensitivity(), Qt::CaseInsensitive);
}

#include "moc_plugincommonmodelinstalledinfossortproxymodeltest.cpp"
