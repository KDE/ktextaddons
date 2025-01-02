/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotenginewidgettest.h"
#include "bergamotenginewidget.h"
#include <QTabWidget>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(BergamotEngineWidgetTest)
BergamotEngineWidgetTest::BergamotEngineWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void BergamotEngineWidgetTest::shouldHaveDefaultValues()
{
    BergamotEngineWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mTabWidget = w.findChild<QTabWidget *>(QStringLiteral("mTabWidget"));
    QVERIFY(mTabWidget);

    // TODO
}

#include "moc_bergamotenginewidgettest.cpp"
