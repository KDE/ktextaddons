/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratenetworkpluginconfigurewidgettest.h"
#include "widgets/networkpluginconfigure/textautogeneratenetworkpluginconfigurewidget.h"
#include <KPasswordLineEdit>
#include <QComboBox>
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
    auto mCustomModels = w.findChild<QLineEdit *>(u"mCustomModels"_s);
    QVERIFY(mCustomModels);
    QVERIFY(mCustomModels->text().isEmpty());
    QVERIFY(w.customModels().isEmpty());

    auto mThinkingLevel = w.findChild<QComboBox *>(u"mThinkingLevel"_s);
    QVERIFY(mThinkingLevel);
    QCOMPARE(mThinkingLevel->count(), 0);
    QVERIFY(mThinkingLevel->isHidden());
    QVERIFY(mainLayout->labelForField(mThinkingLevel)->isHidden());
    QVERIFY(w.thinkingLevel().isEmpty());
}

void TextAutoGenerateNetworkPluginConfigureWidgetTest::shouldSetThinkingLevels()
{
    TextAutoGenerateText::TextAutoGenerateNetworkPluginConfigureWidget w;
    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    auto mThinkingLevel = w.findChild<QComboBox *>(u"mThinkingLevel"_s);

    w.setThinkingLevels({{QString(), u"Default"_s}, {u"low"_s, u"Low"_s}, {u"high"_s, u"High"_s}});
    QCOMPARE(mThinkingLevel->count(), 3);
    QVERIFY(!mThinkingLevel->isHidden());
    QVERIFY(!mainLayout->labelForField(mThinkingLevel)->isHidden());
    QCOMPARE(mThinkingLevel->itemText(1), u"Low"_s);
    QVERIFY(w.thinkingLevel().isEmpty());

    w.setThinkingLevel(u"high"_s);
    QCOMPARE(w.thinkingLevel(), u"high"_s);
    QCOMPARE(mThinkingLevel->currentText(), u"High"_s);

    // Unknown level: fallback to the first entry
    w.setThinkingLevel(u"xhigh"_s);
    QCOMPARE(mThinkingLevel->currentIndex(), 0);
    QVERIFY(w.thinkingLevel().isEmpty());

    w.setThinkingLevels({});
    QCOMPARE(mThinkingLevel->count(), 0);
    QVERIFY(mThinkingLevel->isHidden());
    QVERIFY(mainLayout->labelForField(mThinkingLevel)->isHidden());
    QVERIFY(w.thinkingLevel().isEmpty());
}

void TextAutoGenerateNetworkPluginConfigureWidgetTest::shouldCleanCustomModels()
{
    TextAutoGenerateText::TextAutoGenerateNetworkPluginConfigureWidget w;
    w.setCustomModels({u"foo"_s, u"bar"_s});
    QCOMPARE(w.customModels(), QStringList({u"foo"_s, u"bar"_s}));

    auto mCustomModels = w.findChild<QLineEdit *>(u"mCustomModels"_s);
    mCustomModels->setText(u" foo ,, bar,foo , "_s);
    QCOMPARE(w.customModels(), QStringList({u"foo"_s, u"bar"_s}));
}

#include "moc_textautogeneratenetworkpluginconfigurewidgettest.cpp"
