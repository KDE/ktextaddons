/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailableinfostest.h"
#include "modelsmanager/genericnetworkmodelavailableinfos.h"
#include <QTest>
QTEST_GUILESS_MAIN(GenericNetworkModelAvailableInfosTest)

GenericNetworkModelAvailableInfosTest::GenericNetworkModelAvailableInfosTest(QObject *parent)
    : QObject{parent}
{
}

void GenericNetworkModelAvailableInfosTest::shouldHaveDefaultValues()
{
    GenericNetworkModelAvailableInfos infos;
    QVERIFY(infos.infos().isEmpty());
}

#include "moc_genericnetworkmodelavailableinfostest.cpp"
