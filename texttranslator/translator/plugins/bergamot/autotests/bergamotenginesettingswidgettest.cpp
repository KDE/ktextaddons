/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotenginesettingswidgettest.h"
#include "bergamotenginesettingswidget.h"
#include <QComboBox>
#include <QFormLayout>
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
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto resourceBox = w.findChild<QGroupBox *>(QStringLiteral("resourceBox"));
    QVERIFY(resourceBox);
    QVERIFY(!resourceBox->title().isEmpty());

    auto mNumberThreads = w.findChild<QComboBox *>(QStringLiteral("mNumberThreads"));
    QVERIFY(mNumberThreads);

    auto mMemoryByThreads = w.findChild<QComboBox *>(QStringLiteral("mMemoryByThreads"));
    QVERIFY(mMemoryByThreads);
}

#include "moc_bergamotenginesettingswidgettest.cpp"
