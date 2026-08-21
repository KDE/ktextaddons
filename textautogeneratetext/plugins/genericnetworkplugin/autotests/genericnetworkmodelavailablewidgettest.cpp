/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailablewidgettest.h"
#include "modelsmanager/genericnetworkmodelavailablewidget.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(GenericNetworkModelAvailableWidgetTest)

GenericNetworkModelAvailableWidgetTest::GenericNetworkModelAvailableWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void GenericNetworkModelAvailableWidgetTest::shouldHaveDefaultValues()
{
    GenericNetworkModelAvailableWidget w(nullptr);
    // TODO
}

#include "moc_genericnetworkmodelavailablewidgettest.cpp"
