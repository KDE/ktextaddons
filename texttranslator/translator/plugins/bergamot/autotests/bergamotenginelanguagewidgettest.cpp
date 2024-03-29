/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "bergamotenginelanguagewidgettest.h"
#include "bergamotenginelanguagewidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(BergamotEngineLanguageWidgetTest)
BergamotEngineLanguageWidgetTest::BergamotEngineLanguageWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void BergamotEngineLanguageWidgetTest::shouldHaveDefaultValues()
{
    BergamotEngineLanguageWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    // TODO
}

#include "moc_bergamotenginelanguagewidgettest.cpp"
