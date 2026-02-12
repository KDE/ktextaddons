/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonkeepaliveparameterswidgettest.h"
#include "ollamacommonkeepaliveparameterscombobox.h"
#include "ollamacommonkeepaliveparameterswidget.h"
#include <QGroupBox>
#include <QSpinBox>
#include <QTest>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(OllamaCommonKeepAliveParametersWidgetTest)

OllamaCommonKeepAliveParametersWidgetTest::OllamaCommonKeepAliveParametersWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaCommonKeepAliveParametersWidgetTest::shouldHaveDefaultValues()
{
    const OllamaCommonKeepAliveParametersWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto groupCustomizeGroupbox = w.findChild<QGroupBox *>(u"groupCustomizeGroupbox"_s);
    QVERIFY(groupCustomizeGroupbox);

    auto mOllamaCommonKeepAliveParametersComboBox = w.findChild<OllamaCommonKeepAliveParametersComboBox *>(u"mOllamaCommonKeepAliveParametersComboBox"_s);
    QVERIFY(mOllamaCommonKeepAliveParametersComboBox);

    auto mKeepAliveMinutes = w.findChild<QSpinBox *>(u"mKeepAliveMinutes"_s);
    QVERIFY(mKeepAliveMinutes);
}

#include "moc_ollamacommonkeepaliveparameterswidgettest.cpp"
