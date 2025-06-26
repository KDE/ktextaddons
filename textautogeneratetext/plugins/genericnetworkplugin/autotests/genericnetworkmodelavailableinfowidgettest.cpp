/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericnetworkmodelavailableinfowidgettest.h"
#include "modelsmanager/genericnetworkmodelavailableinfowidget.h"
#include <QTest>
QTEST_MAIN(GenericNetworkModelAvailableInfoWidgetTest)

GenericNetworkModelAvailableInfoWidgetTest::GenericNetworkModelAvailableInfoWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void GenericNetworkModelAvailableInfoWidgetTest::shouldHaveDefaultValues()
{
    GenericNetworkModelAvailableInfoWidget w;
    // TODO
}

#include "moc_genericnetworkmodelavailableinfowidgettest.cpp"
