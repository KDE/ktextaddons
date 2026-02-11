/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonoverrideparameterswidgettest.h"
#include "ollamacommonoverrideparameterswidget.h"
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(OllamaCommonOverrideParametersWidgetTest)
using namespace Qt::Literals::StringLiterals;
OllamaCommonOverrideParametersWidgetTest::OllamaCommonOverrideParametersWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaCommonOverrideParametersWidgetTest::shouldHaveDefaultValues()
{
    const OllamaCommonOverrideParametersWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto groupCustomizeGroupbox = w.findChild<QGroupBox *>(u"groupCustomizeGroupbox"_s);
    QVERIFY(groupCustomizeGroupbox);

    auto mTemperature = w.findChild<QDoubleSpinBox *>(u"mTemperature"_s);
    QVERIFY(mTemperature);

    auto mSeed = w.findChild<QSpinBox *>(u"mSeed"_s);
    QVERIFY(mSeed);
}
#include "moc_ollamacommonoverrideparameterswidgettest.cpp"
