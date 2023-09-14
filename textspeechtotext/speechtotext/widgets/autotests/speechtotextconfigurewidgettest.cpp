/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextconfigurewidgettest.h"
#include "speechtotext/widgets/speechtotextcomboboxwidget.h"
#include "speechtotext/widgets/speechtotextconfigurewidget.h"
#include "speechtotext/widgets/speechtotextselectdevicewidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(SpeechToTextConfigureWidgetTest)
SpeechToTextConfigureWidgetTest::SpeechToTextConfigureWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void SpeechToTextConfigureWidgetTest::shouldHaveDefaultValues()
{
    TextSpeechToText::SpeechToTextConfigureWidget w;

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mSpeechToTextComboBox = w.findChild<TextSpeechToText::SpeechToTextComboBoxWidget *>(QStringLiteral("mSpeechToTextComboBox"));
    QVERIFY(mSpeechToTextComboBox);

    auto mSpeechToTextDevice = w.findChild<TextSpeechToText::SpeechToTextSelectDeviceWidget *>(QStringLiteral("mSpeechToTextDevice"));
    QVERIFY(mSpeechToTextDevice);
}

#include "moc_speechtotextconfigurewidgettest.cpp"
