/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailablewidgettest.h"
#include "modelsmanager/genericnetworkmodelavailablewidget.h"
#include <QTest>
QTEST_MAIN(GenericNetworkModelAvailableWidgetTest)

GenericNetworkModelAvailableWidgetTest::GenericNetworkModelAvailableWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void GenericNetworkModelAvailableWidgetTest::shouldHaveDefaultValues()
{
    GenericNetworkModelAvailableWidget w;
    // TODO
}

#include "moc_genericnetworkmodelavailablewidgettest.cpp"
