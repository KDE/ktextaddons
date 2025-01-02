/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextconfiguredialogtest.h"
#include "speechtotext/widgets/speechtotextconfiguredialog.h"
#include "speechtotext/widgets/speechtotextconfigurewidget.h"

#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(SpeechToTextConfigureDialogTest)
SpeechToTextConfigureDialogTest::SpeechToTextConfigureDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void SpeechToTextConfigureDialogTest::shouldHaveDefaultValues()
{
    TextSpeechToText::SpeechToTextConfigureDialog d;
    // TODO
}

#include "moc_speechtotextconfiguredialogtest.cpp"
