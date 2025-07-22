/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratenetworkpluginconfigurewidgettest.h"
#include "widgets/networkpluginconfigure/textautogeneratenetworkpluginconfigurewidget.h"
#include <KPasswordLineEdit>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTest>
QTEST_MAIN(TextAutoGenerateNetworkPluginConfigureWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateNetworkPluginConfigureWidgetTest::TextAutoGenerateNetworkPluginConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateNetworkPluginConfigureWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateNetworkPluginConfigureWidget w;
    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mApiKey = w.findChild<KPasswordLineEdit *>(u"mApiKey"_s);
    QVERIFY(mApiKey);

    auto mInstanceName = w.findChild<QLineEdit *>(u"mInstanceName"_s);
    QVERIFY(mInstanceName);
    auto mMaxToken = w.findChild<QSpinBox *>(u"mMaxToken"_s);
    QVERIFY(mMaxToken);
    auto mTemperature = w.findChild<QDoubleSpinBox *>(u"mTemperature"_s);
    QVERIFY(mTemperature);
    auto mSeed = w.findChild<QSpinBox *>(u"mSeed"_s);
    QVERIFY(mSeed);
    auto mWebSite = w.findChild<QLabel *>(u"mWebSite"_s);
    QVERIFY(mWebSite->openExternalLinks());
    QCOMPARE(mWebSite->textFormat(), Qt::RichText);
    QCOMPARE(mWebSite->textInteractionFlags(), Qt::TextBrowserInteraction);
    QVERIFY(mWebSite);
    auto mDescription = w.findChild<QLabel *>(u"mDescription"_s);
    QVERIFY(mDescription);
}

#include "moc_textautogeneratenetworkpluginconfigurewidgettest.cpp"
