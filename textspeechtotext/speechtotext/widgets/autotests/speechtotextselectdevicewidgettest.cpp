/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextselectdevicewidgettest.h"
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

    auto mainLayout = w.findChild<QHBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto label = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    auto mDeviceComboBox = w.findChild<QComboBox *>(QStringLiteral("mDeviceComboBox"));
    QVERIFY(mDeviceComboBox);
}

#include "moc_speechtotextselectdevicewidgettest.cpp"
