/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deeplengineconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "../deeplengineconfigurewidget.h"
#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(DeeplEngineConfigureWidgetTest)
DeeplEngineConfigureWidgetTest::DeeplEngineConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void DeeplEngineConfigureWidgetTest::shouldHaveDefaultValues()
{
    DeeplEngineConfigureWidget w;
    QVERIFY(!w.useFreeLicenceKey());

    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mUseFreeLicense = w.findChild<QCheckBox *>(u"mUseFreeLicense"_s);
    QVERIFY(mUseFreeLicense);
    QVERIFY(!mUseFreeLicense->isChecked());

    auto mApiKey = w.findChild<QLineEdit *>(u"mApiKey"_s);
    QVERIFY(mApiKey);
    QVERIFY(mApiKey->isClearButtonEnabled());
}

#include "moc_deeplengineconfigurewidgettest.cpp"
