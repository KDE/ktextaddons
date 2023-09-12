/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextselectdevicewidgettest.h"
#include "speechtotext/widgets/speechtotextselectdevicewidget.h"
#include <QTest>

QTEST_MAIN(SpeechToTextSelectDeviceWidgetTest)
SpeechToTextSelectDeviceWidgetTest::SpeechToTextSelectDeviceWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void SpeechToTextSelectDeviceWidgetTest::shouldHaveDefaultValues()
{
    TextSpeechToText::SpeechToTextSelectDeviceWidget w;
    // TODO
}
