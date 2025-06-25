/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailableinfotest.h"
#include "modelsmanager/genericnetworkmodelavailableinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(GenericNetworkModelAvailableInfoTest)

GenericNetworkModelAvailableInfoTest::GenericNetworkModelAvailableInfoTest(QObject *parent)
    : QObject{parent}
{
}

void GenericNetworkModelAvailableInfoTest::shouldHaveDefaultValues()
{
    GenericNetworkModelAvailableInfo info;
    QVERIFY(info.description().isEmpty());
    QVERIFY(info.modelName().isEmpty());
    QVERIFY(!info.toolsSupported());
}

#include "moc_genericnetworkmodelavailableinfotest.cpp"
