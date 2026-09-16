/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstallpythonevenvjobtest.h"
#include "whisperspeechtotextinstallpythonevenvjob.h"
#include "whisperspeechtotextutils.h"
#include <QTest>

QTEST_GUILESS_MAIN(WhisperSpeechToTextInstallPythonEvenvJobTest)
WhisperSpeechToTextInstallPythonEvenvJobTest::WhisperSpeechToTextInstallPythonEvenvJobTest(QObject *parent)
    : QObject{parent}
{
}

void WhisperSpeechToTextInstallPythonEvenvJobTest::shouldHaveDefaultValues()
{
    WhisperSpeechToTextInstallPythonEvenvJob job;
    // The job needs an interpreter to create the virtualenv with, nothing else.
    QCOMPARE(job.canStart(), !WhisperSpeechToTextUtils::pythonVersionPath().isEmpty());
}

#include "moc_whisperspeechtotextinstallpythonevenvjobtest.cpp"
