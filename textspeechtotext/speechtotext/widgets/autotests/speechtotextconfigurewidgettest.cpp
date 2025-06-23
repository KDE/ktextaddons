/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "speechtotext/widgets/speechtotextcomboboxwidget.h"
#include "speechtotext/widgets/speechtotextconfigurewidget.h"
#include "speechtotext/widgets/speechtotextselectdevicewidget.h"
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(SpeechToTextConfigureWidgetTest)
SpeechToTextConfigureWidgetTest::SpeechToTextConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void SpeechToTextConfigureWidgetTest::shouldHaveDefaultValues()
{
    TextSpeechToText::SpeechToTextConfigureWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mSpeechToTextComboBox = w.findChild<TextSpeechToText::SpeechToTextComboBoxWidget *>(u"mSpeechToTextComboBox"_s);
    QVERIFY(mSpeechToTextComboBox);

    auto mSpeechToTextDevice = w.findChild<TextSpeechToText::SpeechToTextSelectDeviceWidget *>(u"mSpeechToTextDevice"_s);
    QVERIFY(mSpeechToTextDevice);
}

#include "moc_speechtotextconfigurewidgettest.cpp"
