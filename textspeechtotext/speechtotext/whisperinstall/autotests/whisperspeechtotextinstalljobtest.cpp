/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstalljobtest.h"
using namespace Qt::Literals::StringLiterals;

#include "whisperspeechtotextinstalljob.h"
#include "whisperspeechtotextutils.h"
#include <QPointer>
#include <QSignalSpy>
#include <QTest>

QTEST_GUILESS_MAIN(WhisperSpeechToTextInstallJobTest)
WhisperSpeechToTextInstallJobTest::WhisperSpeechToTextInstallJobTest(QObject *parent)
    : QObject{parent}
{
}

void WhisperSpeechToTextInstallJobTest::shouldHaveDefaultValues()
{
    WhisperSpeechToTextInstallJob w;
    QVERIFY(w.modules().isEmpty());
    // Nothing to install: the job has no reason to run.
    QVERIFY(!w.canStart());
}

void WhisperSpeechToTextInstallJobTest::shouldAssignModules()
{
    WhisperSpeechToTextInstallJob w;
    const QStringList modules = WhisperSpeechToTextUtils::requiredModules();
    w.setModules(modules);
    QCOMPARE(w.modules(), modules);

    // With modules to install, the pip of the virtualenv is still needed:
    // WhisperSpeechToTextInstallPythonEvenvJob is the one which creates it.
    QCOMPARE(w.canStart(), !WhisperSpeechToTextUtils::venvPip().isEmpty());

    w.setModules({});
    QVERIFY(w.modules().isEmpty());
    QVERIFY(!w.canStart());
}

void WhisperSpeechToTextInstallJobTest::shouldNotStartWithoutModules()
{
    QPointer<WhisperSpeechToTextInstallJob> job = new WhisperSpeechToTextInstallJob;
    QSignalSpy failedSpy(job, &WhisperSpeechToTextInstallJob::installFailed);
    QSignalSpy doneSpy(job, &WhisperSpeechToTextInstallJob::installDone);
    QVERIFY(!job->canStart());
    job->start();
    QCOMPARE(failedSpy.count(), 1);
    QCOMPARE(doneSpy.count(), 0);
    // The job deletes itself as it can't start.
    QVERIFY(QTest::qWaitFor([&job]() {
        return job.isNull();
    }));
}

#include "moc_whisperspeechtotextinstalljobtest.cpp"
