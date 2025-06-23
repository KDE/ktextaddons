/*
   SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechsliderwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "texttospeechsliderwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QTest>
QTEST_MAIN(TextToSpeechSliderWidgetTest)
TextToSpeechSliderWidgetTest::TextToSpeechSliderWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextToSpeechSliderWidgetTest::shouldHaveDefaultValues()
{
    TextEditTextToSpeech::TextToSpeechSliderWidget w({});
    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mLabel = w.findChild<QLabel *>(u"mLabel"_s);
    QVERIFY(mLabel);

    auto mSlider = w.findChild<QSlider *>(u"mSlider"_s);
    QVERIFY(mSlider);
    QCOMPARE(mSlider->orientation(), Qt::Horizontal);
}

#include "moc_texttospeechsliderwidgettest.cpp"
