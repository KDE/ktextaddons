/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextselectdevicewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "speechtotext/widgets/speechtotextselectdevicewidget.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QStandardPaths>
#include <QTest>

QTEST_MAIN(SpeechToTextSelectDeviceWidgetTest)
SpeechToTextSelectDeviceWidgetTest::SpeechToTextSelectDeviceWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void SpeechToTextSelectDeviceWidgetTest::shouldHaveDefaultValues()
{
    TextSpeechToText::SpeechToTextSelectDeviceWidget w;

    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto label = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    auto mDeviceComboBox = w.findChild<QComboBox *>(u"mDeviceComboBox"_s);
    QVERIFY(mDeviceComboBox);
}

#include "moc_speechtotextselectdevicewidgettest.cpp"
