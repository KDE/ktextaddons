/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "../libretranslateengineconfigurewidget.h"
#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(LibreTranslateEngineConfigureWidgetTest)
LibreTranslateEngineConfigureWidgetTest::LibreTranslateEngineConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void LibreTranslateEngineConfigureWidgetTest::shouldHaveDefaultValues()
{
    LibreTranslateEngineConfigureWidget w;
    QVERIFY(w.serverUrl().isEmpty());

    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mServerUrl = w.findChild<QLineEdit *>(u"mServerUrl"_s);
    QVERIFY(mServerUrl);
    QVERIFY(mServerUrl->isClearButtonEnabled());

    auto mApiKey = w.findChild<QLineEdit *>(u"mApiKey"_s);
    QVERIFY(mApiKey);
    QVERIFY(mApiKey->isClearButtonEnabled());

    QVERIFY(w.apiKey().isEmpty());
    QVERIFY(w.serverUrl().isEmpty());
    QVERIFY(!w.serverRequiredApiKey());

    auto mRequiredApiKey = w.findChild<QCheckBox *>(u"mRequiredApiKey"_s);
    QVERIFY(mRequiredApiKey);
    QVERIFY(!mRequiredApiKey->isChecked());
}

#include "moc_libretranslateengineconfigurewidgettest.cpp"
