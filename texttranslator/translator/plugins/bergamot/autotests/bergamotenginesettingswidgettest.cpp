/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotenginesettingswidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "bergamotenginesettingswidget.h"
#include <QComboBox>
#include <QGroupBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(BergamotEngineSettingsWidgetTest)
BergamotEngineSettingsWidgetTest::BergamotEngineSettingsWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void BergamotEngineSettingsWidgetTest::shouldHaveDefaultValues()
{
    BergamotEngineSettingsWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto resourceBox = w.findChild<QGroupBox *>(u"resourceBox"_s);
    QVERIFY(resourceBox);
    QVERIFY(!resourceBox->title().isEmpty());

    auto mNumberThreads = w.findChild<QComboBox *>(u"mNumberThreads"_s);
    QVERIFY(mNumberThreads);

    auto mMemoryByThreads = w.findChild<QComboBox *>(u"mMemoryByThreads"_s);
    QVERIFY(mMemoryByThreads);
}

#include "moc_bergamotenginesettingswidgettest.cpp"
