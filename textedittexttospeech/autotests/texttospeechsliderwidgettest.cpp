/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechsliderwidgettest.h"

#include "texttospeechsliderwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSignalSpy>
#include <QSlider>
#include <QTest>
QTEST_MAIN(TextToSpeechSliderWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextToSpeechSliderWidgetTest::TextToSpeechSliderWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextToSpeechSliderWidgetTest::shouldHaveDefaultValues()
{
    const TextEditTextToSpeech::TextToSpeechSliderWidget w({});
    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mLabel = w.findChild<QLabel *>(u"mLabel"_s);
    QVERIFY(mLabel);

    auto mSlider = w.findChild<QSlider *>(u"mSlider"_s);
    QVERIFY(mSlider);
    QCOMPARE(mSlider->orientation(), Qt::Horizontal);
}

void TextToSpeechSliderWidgetTest::shouldUpdateLabelAndClampValue()
{
    TextEditTextToSpeech::TextToSpeechSliderWidget w(u"%1 %"_s);
    w.setRange(-100, 100);
    auto mLabel = w.findChild<QLabel *>(u"mLabel"_s);
    QVERIFY(mLabel);
    QSignalSpy spy(&w, &TextEditTextToSpeech::TextToSpeechSliderWidget::valueChanged);

    // Assigning the current value updates the label even though the slider stays silent.
    QCOMPARE(w.value(), 0);
    w.setValue(0);
    QCOMPARE(mLabel->text(), u"0 %"_s);
    QCOMPARE(spy.count(), 0);

    // A real change notifies exactly once.
    w.setValue(5);
    QCOMPARE(w.value(), 5);
    QCOMPARE(mLabel->text(), u"5 %"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.constFirst().at(0).toInt(), 5);

    // An out-of-range value is clamped, and the label shows the clamped value.
    spy.clear();
    w.setValue(500);
    QCOMPARE(w.value(), 100);
    QCOMPARE(mLabel->text(), u"100 %"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.constFirst().at(0).toInt(), 100);
}

#include "moc_texttospeechsliderwidgettest.cpp"
