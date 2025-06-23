/*
   SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "texttospeechwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "texttospeechinterface.h"
#include "texttospeechsliderwidget.h"
#include "texttospeechwidget.h"
#include <QHBoxLayout>
#include <QSignalSpy>
#include <QTest>
#include <QToolButton>
#include <qtestmouse.h>

Q_DECLARE_METATYPE(TextEditTextToSpeech::TextToSpeechWidget::State)
QTEST_MAIN(TextToSpeechWidgetTest)
TextToSpeechWidgetTest::TextToSpeechWidgetTest(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<TextEditTextToSpeech::TextToSpeechWidget::State>();
    QIcon::setThemeName(u"breeze"_s);
}

void TextToSpeechWidgetTest::addInterface(TextEditTextToSpeech::TextToSpeechWidget *widget)
{
    auto interface = new TextEditTextToSpeech::TextToSpeechInterface(widget, this);
    widget->setTextToSpeechInterface(interface);
}

void TextToSpeechWidgetTest::shouldHaveDefaultValue()
{
    TextEditTextToSpeech::TextToSpeechWidget textToSpeechWidget;
    addInterface(&textToSpeechWidget);

    auto hbox = textToSpeechWidget.findChild<QHBoxLayout *>(u"hbox"_s);
    QVERIFY(hbox);
    QCOMPARE(hbox->contentsMargins(), QMargins{});

    QCOMPARE(textToSpeechWidget.state(), TextEditTextToSpeech::TextToSpeechWidget::Stop);

    auto closeButton = textToSpeechWidget.findChild<QToolButton *>(u"close-button"_s);
    QVERIFY(closeButton);

    auto stopButton = textToSpeechWidget.findChild<QToolButton *>(u"stopbutton"_s);
    QVERIFY(stopButton);
    QVERIFY(stopButton->isEnabled());
    QVERIFY(!stopButton->icon().isNull());

    auto playPauseButton = textToSpeechWidget.findChild<QToolButton *>(u"playpausebutton"_s);
    QVERIFY(playPauseButton);
    QVERIFY(!playPauseButton->isEnabled());
    QVERIFY(!playPauseButton->icon().isNull());

    auto volume = textToSpeechWidget.findChild<TextEditTextToSpeech::TextToSpeechSliderWidget *>(u"volumeslider"_s);
    QVERIFY(volume);

    auto configureButton = textToSpeechWidget.findChild<QToolButton *>(u"configurebutton"_s);
    QVERIFY(configureButton);
    QVERIFY(!configureButton->icon().isNull());
}

void TextToSpeechWidgetTest::shouldChangeButtonEnableStateWhenChangeState()
{
    TextEditTextToSpeech::TextToSpeechWidget textToSpeechWidget;
    addInterface(&textToSpeechWidget);
    textToSpeechWidget.setState(TextEditTextToSpeech::TextToSpeechWidget::Play);

    auto stopButton = textToSpeechWidget.findChild<QToolButton *>(u"stopbutton"_s);
    QVERIFY(stopButton->isEnabled());

    auto playPauseButton = textToSpeechWidget.findChild<QToolButton *>(u"playpausebutton"_s);
    QVERIFY(playPauseButton->isEnabled());

    textToSpeechWidget.setState(TextEditTextToSpeech::TextToSpeechWidget::Pause);
    QVERIFY(stopButton->isEnabled());
    QVERIFY(playPauseButton->isEnabled());

    textToSpeechWidget.setState(TextEditTextToSpeech::TextToSpeechWidget::Stop);
    QVERIFY(stopButton->isEnabled());
    QVERIFY(!playPauseButton->isEnabled());
}

void TextToSpeechWidgetTest::shouldChangeStateWhenClickOnPlayPause()
{
    TextEditTextToSpeech::TextToSpeechWidget textToSpeechWidget;
    addInterface(&textToSpeechWidget);

    textToSpeechWidget.setState(TextEditTextToSpeech::TextToSpeechWidget::Play);
    auto playPauseButton = textToSpeechWidget.findChild<QToolButton *>(u"playpausebutton"_s);
    QCOMPARE(textToSpeechWidget.state(), TextEditTextToSpeech::TextToSpeechWidget::Play);

    QTest::mouseClick(playPauseButton, Qt::LeftButton);
    QCOMPARE(textToSpeechWidget.state(), TextEditTextToSpeech::TextToSpeechWidget::Pause);

    QTest::mouseClick(playPauseButton, Qt::LeftButton);
    QCOMPARE(textToSpeechWidget.state(), TextEditTextToSpeech::TextToSpeechWidget::Play);
}

void TextToSpeechWidgetTest::shouldChangeStateWhenClickOnStop()
{
    TextEditTextToSpeech::TextToSpeechWidget textToSpeechWidget;
    addInterface(&textToSpeechWidget);
    textToSpeechWidget.setState(TextEditTextToSpeech::TextToSpeechWidget::Play);

    auto stopButton = textToSpeechWidget.findChild<QToolButton *>(u"stopbutton"_s);
    QTest::mouseClick(stopButton, Qt::LeftButton);
    QCOMPARE(textToSpeechWidget.state(), TextEditTextToSpeech::TextToSpeechWidget::Stop);
}

void TextToSpeechWidgetTest::shouldEmitStateChanged()
{
    TextEditTextToSpeech::TextToSpeechWidget textToSpeechWidget;
    addInterface(&textToSpeechWidget);
    QSignalSpy spy(&textToSpeechWidget, &TextEditTextToSpeech::TextToSpeechWidget::stateChanged);
    textToSpeechWidget.setState(TextEditTextToSpeech::TextToSpeechWidget::Play);
    QCOMPARE(spy.count(), 0);

    auto stopButton = textToSpeechWidget.findChild<QToolButton *>(u"stopbutton"_s);

    auto playPauseButton = textToSpeechWidget.findChild<QToolButton *>(u"playpausebutton"_s);

    QTest::mouseClick(playPauseButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).value<TextEditTextToSpeech::TextToSpeechWidget::State>(), TextEditTextToSpeech::TextToSpeechWidget::Pause);
    QTest::mouseClick(playPauseButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 2);
    QCOMPARE(spy.at(1).at(0).value<TextEditTextToSpeech::TextToSpeechWidget::State>(), TextEditTextToSpeech::TextToSpeechWidget::Play);
    QTest::mouseClick(playPauseButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 3);
    QCOMPARE(spy.at(2).at(0).value<TextEditTextToSpeech::TextToSpeechWidget::State>(), TextEditTextToSpeech::TextToSpeechWidget::Pause);
    QTest::mouseClick(stopButton, Qt::LeftButton);
    QCOMPARE(spy.count(), 4);
    QCOMPARE(spy.at(3).at(0).value<TextEditTextToSpeech::TextToSpeechWidget::State>(), TextEditTextToSpeech::TextToSpeechWidget::Stop);
}

#include "moc_texttospeechwidgettest.cpp"
