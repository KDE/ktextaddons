/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextcheckjobtest.h"
using namespace Qt::Literals::StringLiterals;

#include "whisperspeechtotextcheckjob.h"
#include "whisperspeechtotextutils.h"
#include <QPointer>
#include <QSignalSpy>
#include <QTest>

QTEST_GUILESS_MAIN(WhisperSpeechToTextCheckJobTest)
WhisperSpeechToTextCheckJobTest::WhisperSpeechToTextCheckJobTest(QObject *parent)
    : QObject{parent}
{
}

void WhisperSpeechToTextCheckJobTest::shouldHaveDefaultValues()
{
    WhisperSpeechToTextCheckJob w;
    // Nothing to run the check with as long as the helper script is not installed.
    QCOMPARE(w.canStart(), !WhisperSpeechToTextUtils::pythonScriptPath().isEmpty());

    const WhisperSpeechToTextCheckJob::CheckResult result;
    QVERIFY(result.isValid());
    QVERIFY(result.missing.isEmpty());
    QVERIFY(result.pythonExecutable.isEmpty());
    QCOMPARE(result.sampleRate, 0);
    QCOMPARE(result.channels, 0);
    QVERIFY(!result.needToReinstall);
    QVERIFY(result.errorString().isEmpty());
}

void WhisperSpeechToTextCheckJobTest::shouldParseCheckResult_data()
{
    QTest::addColumn<QByteArray>("json");
    QTest::addColumn<QStringList>("missing");
    QTest::addColumn<QString>("pythonExecutable");
    QTest::addColumn<int>("sampleRate");
    QTest::addColumn<int>("channels");
    QTest::addColumn<bool>("needToReinstall");

    QTest::newRow("empty") << QByteArray() << QStringList() << QString() << 0 << 0 << true;
    QTest::newRow("invalid-json") << QByteArray("not json at all") << QStringList() << QString() << 0 << 0 << true;
    QTest::newRow("empty-object") << QByteArray("{}") << QStringList() << QString() << 0 << 0 << true;
    // A json array is not what the script prints.
    QTest::newRow("array") << QByteArray("[]") << QStringList() << QString() << 0 << 0 << true;

    QTest::newRow("available") << QByteArray(
        R"({"available": true, "missing": [], "python": "/home/foo/.venv/whisper/bin/python", "sampleRate": 16000, "channels": 1})")
                               << QStringList() << u"/home/foo/.venv/whisper/bin/python"_s << 16000 << 1 << false;

    QTest::newRow("missing-one") << QByteArray(
        R"({"available": false, "missing": ["faster-whisper"], "python": "/usr/bin/python", "sampleRate": 16000, "channels": 1})")
                                 << QStringList{u"faster-whisper"_s} << u"/usr/bin/python"_s << 16000 << 1 << false;

    QTest::newRow("missing-all") << QByteArray(R"({"available": false, "missing": ["faster-whisper", "numpy"], "python": "/usr/bin/python"})")
                                 << QStringList{u"faster-whisper"_s, u"numpy"_s} << u"/usr/bin/python"_s << 0 << 0 << false;

    // Not usable but nothing named: only a reinstallation can fix it.
    QTest::newRow("unavailable-without-missing") << QByteArray(R"({"available": false, "missing": [], "python": "/usr/bin/python"})") << QStringList()
                                                 << u"/usr/bin/python"_s << 0 << 0 << true;

    // Defensive: the script must not be able to ask for the installation of "".
    QTest::newRow("empty-module-name") << QByteArray(R"({"available": false, "missing": ["", "numpy"]})") << QStringList{u"numpy"_s} << QString() << 0 << 0
                                       << false;
}

void WhisperSpeechToTextCheckJobTest::shouldParseCheckResult()
{
    QFETCH(QByteArray, json);
    QFETCH(QStringList, missing);
    QFETCH(QString, pythonExecutable);
    QFETCH(int, sampleRate);
    QFETCH(int, channels);
    QFETCH(bool, needToReinstall);

    const WhisperSpeechToTextCheckJob::CheckResult result = WhisperSpeechToTextCheckJob::parseCheckResult(json);
    QCOMPARE(result.missing, missing);
    QCOMPARE(result.pythonExecutable, pythonExecutable);
    QCOMPARE(result.sampleRate, sampleRate);
    QCOMPARE(result.channels, channels);
    QCOMPARE(result.needToReinstall, needToReinstall);
    QCOMPARE(result.isValid(), missing.isEmpty() && !needToReinstall);
}

void WhisperSpeechToTextCheckJobTest::shouldReportErrorString()
{
    WhisperSpeechToTextCheckJob::CheckResult result;
    QVERIFY(result.errorString().isEmpty());

    result.missing = QStringList{u"faster-whisper"_s, u"numpy"_s};
    const QString missingError = result.errorString();
    QVERIFY(!missingError.isEmpty());
    QVERIFY(missingError.contains(u"faster-whisper"_s));
    QVERIFY(missingError.contains(u"numpy"_s));

    // A broken installation is reported as such, whatever is missing.
    result.needToReinstall = true;
    QVERIFY(!result.errorString().isEmpty());
    QVERIFY(result.errorString() != missingError);
}

void WhisperSpeechToTextCheckJobTest::shouldAskToInstallPackagesWithoutVenv()
{
    if (!WhisperSpeechToTextUtils::venvPython().isEmpty()) {
        QSKIP("The whisper virtualenv exists here, the job would run the real script.");
    }
    QPointer<WhisperSpeechToTextCheckJob> job = new WhisperSpeechToTextCheckJob;
    QSignalSpy reinstallSpy(job, &WhisperSpeechToTextCheckJob::needToReinstall);
    QSignalSpy installSpy(job, &WhisperSpeechToTextCheckJob::needToInstallPackages);
    const bool canStart = job->canStart();
    job->start();
    if (canStart) {
        // The script is there but the modules live in a virtualenv which is not.
        QCOMPARE(installSpy.count(), 1);
        QCOMPARE(installSpy.constFirst().at(0).toStringList(), WhisperSpeechToTextUtils::requiredModules());
        QCOMPARE(reinstallSpy.count(), 0);
    } else {
        QCOMPARE(reinstallSpy.count(), 1);
        QCOMPARE(installSpy.count(), 0);
    }
    // The job deletes itself once it has reported the answer.
    QVERIFY(QTest::qWaitFor([&job]() {
        return job.isNull();
    }));
}

#include "moc_whisperspeechtotextcheckjobtest.cpp"
