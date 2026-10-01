/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "bergamotenginelanguagewidgettest.h"

#include "bergamotenginelanguagewidget.h"
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(BergamotEngineLanguageWidgetTest)
BergamotEngineLanguageWidgetTest::BergamotEngineLanguageWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
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
