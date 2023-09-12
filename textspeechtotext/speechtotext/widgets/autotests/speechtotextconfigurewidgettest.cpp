/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextconfigurewidgettest.h"
#include "speechtotext/widgets/speechtotextcombobox.h"
#include "speechtotext/widgets/speechtotextconfigurewidget.h"
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

    auto mSpeechToTextComboBox = w.findChild<TextSpeechToText::SpeechToTextComboBox *>(QStringLiteral("mSpeechToTextComboBox"));
    QVERIFY(mSpeechToTextComboBox);
}

#include "moc_speechtotextconfigurewidgettest.cpp"
