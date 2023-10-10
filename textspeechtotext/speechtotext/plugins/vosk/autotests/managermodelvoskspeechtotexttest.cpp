/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "managermodelvoskspeechtotexttest.h"
#include "managermodelvoskspeechtotext.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(ManagerModelVoskSpeechToTextTest)
ManagerModelVoskSpeechToTextTest::ManagerModelVoskSpeechToTextTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void ManagerModelVoskSpeechToTextTest::shouldHaveDefaultValues()
{
    ManagerModelVoskSpeechToText w;
    QVERIFY(w.speechToTextInfos().isEmpty());
    QVERIFY(w.needDownloadModelList());
}

#include "moc_managermodelvoskspeechtotexttest.cpp"
