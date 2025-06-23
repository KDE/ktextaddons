/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailablelistviewtest.h"
#include "modelsmanager/genericnetworkmodelavailablelistview.h"
#include <QTest>
QTEST_MAIN(GenericNetworkModelAvailableListViewTest)

GenericNetworkModelAvailableListViewTest::GenericNetworkModelAvailableListViewTest(QObject *parent)
    : QObject{parent}
{
}

void GenericNetworkModelAvailableListViewTest::shouldHaveDefaultValues()
{
    GenericNetworkModelAvailableListView w;
    QCOMPARE(w.verticalScrollMode(), QAbstractItemView::ScrollPerPixel);
    QCOMPARE(w.horizontalScrollBarPolicy(), Qt::ScrollBarAlwaysOff);
    QVERIFY(w.wordWrap());
    QVERIFY(w.hasMouseTracking());
    QCOMPARE(w.focusPolicy(), Qt::NoFocus);
}

#include "moc_genericnetworkmodelavailablelistviewtest.cpp"
