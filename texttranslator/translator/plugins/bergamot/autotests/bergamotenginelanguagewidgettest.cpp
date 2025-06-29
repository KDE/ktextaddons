/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "bergamotenginelanguagewidgettest.h"
using namespace Qt::Literals::StringLiterals;

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
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    // TODO
}

#include "moc_bergamotenginelanguagewidgettest.cpp"
