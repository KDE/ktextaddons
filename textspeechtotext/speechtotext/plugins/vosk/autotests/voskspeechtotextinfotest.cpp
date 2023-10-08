/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextinfotest.h"
#include "voskspeechtotextinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(VoskSpeechToTextInfoTest)
VoskSpeechToTextInfoTest::VoskSpeechToTextInfoTest(QObject *parent)
    : QObject{parent}
{
}

void VoskSpeechToTextInfoTest::shouldHaveDefaultValues()
{
    VoskSpeechToTextInfo w;
}
