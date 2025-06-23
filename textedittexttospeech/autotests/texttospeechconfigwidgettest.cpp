/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechconfigwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "texttospeechconfiginterface.h"
#include "texttospeechconfigwidget.h"
#include "texttospeechlanguagecombobox.h"
#include "texttospeechsliderwidget.h"
#include "texttospeechvoicecombobox.h"

#include <QComboBox>
#include <QPushButton>
#include <QSignalSpy>
#include <QTest>

QTEST_MAIN(TextToSpeechConfigWidgetTest)

TextToSpeechConfigWidgetTest::TextToSpeechConfigWidgetTest(QObject *parent)
    : QObject(parent)
{
}

TextToSpeechConfigWidgetTest::~TextToSpeechConfigWidgetTest() = default;

void TextToSpeechConfigWidgetTest::addInterface(TextEditTextToSpeech::TextToSpeechConfigWidget *widget)
{
    auto interface = new TextEditTextToSpeech::TextToSpeechConfigInterface(this);
    widget->setTextToSpeechConfigInterface(interface);
}

void TextToSpeechConfigWidgetTest::shouldHaveDefaultValue()
{
    TextEditTextToSpeech::TextToSpeechConfigWidget textToSpeechConfigWidget;
    addInterface(&textToSpeechConfigWidget);
    auto volume = textToSpeechConfigWidget.findChild<TextEditTextToSpeech::TextToSpeechSliderWidget *>(u"volume"_s);
    QVERIFY(volume);

    auto rate = textToSpeechConfigWidget.findChild<TextEditTextToSpeech::TextToSpeechSliderWidget *>(u"rate"_s);
    QVERIFY(rate);

    auto pitch = textToSpeechConfigWidget.findChild<TextEditTextToSpeech::TextToSpeechSliderWidget *>(u"pitch"_s);
    QVERIFY(pitch);

    auto language = textToSpeechConfigWidget.findChild<TextEditTextToSpeech::TextToSpeechLanguageComboBox *>(u"language"_s);
    QVERIFY(language);
    // FIXME
    // QVERIFY(language->count()>0);

    auto availableEngine = textToSpeechConfigWidget.findChild<QComboBox *>(u"engine"_s);
    QVERIFY(availableEngine);

    auto voice = textToSpeechConfigWidget.findChild<TextEditTextToSpeech::TextToSpeechVoiceComboBox *>(u"voice"_s);
    QVERIFY(voice);

    auto mTestButton = textToSpeechConfigWidget.findChild<QPushButton *>(u"mTestButton"_s);
    QVERIFY(mTestButton);
}

void TextToSpeechConfigWidgetTest::shouldEmitConfigChangedWhenChangeConfigValue()
{
    TextEditTextToSpeech::TextToSpeechConfigWidget textToSpeechConfigWidget;
    addInterface(&textToSpeechConfigWidget);
    QSignalSpy spy(&textToSpeechConfigWidget, &TextEditTextToSpeech::TextToSpeechConfigWidget::configChanged);
    auto volume = textToSpeechConfigWidget.findChild<TextEditTextToSpeech::TextToSpeechSliderWidget *>(u"volume"_s);
    volume->setValue(5);
    // It updates slider too! => 2 emit signal.
    QCOMPARE(spy.count(), 2);

    spy.clear();
    auto rate = textToSpeechConfigWidget.findChild<TextEditTextToSpeech::TextToSpeechSliderWidget *>(u"rate"_s);
    rate->setValue(5);
    QCOMPARE(spy.count(), 2);

    spy.clear();
    auto pitch = textToSpeechConfigWidget.findChild<TextEditTextToSpeech::TextToSpeechSliderWidget *>(u"pitch"_s);
    pitch->setValue(5);
    QCOMPARE(spy.count(), 2);

    auto language = textToSpeechConfigWidget.findChild<QComboBox *>(u"language"_s);
    language->blockSignals(true);
    QStringList lst;
    lst << u"foo"_s;
    lst << u"foo"_s;
    lst << u"foo"_s;
    lst << u"foo"_s;
    language->addItems(lst);
    language->blockSignals(false);
    language->setCurrentIndex(3);
    QCOMPARE(spy.count(), 3);
}

#include "moc_texttospeechconfigwidgettest.cpp"
