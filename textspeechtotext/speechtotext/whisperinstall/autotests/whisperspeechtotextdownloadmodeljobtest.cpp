/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextdownloadmodeljobtest.h"

#include "whisperspeechtotextdownloadmodeljob.h"
#include "whisperspeechtotextutils.h"
#include <QPointer>
#include <QSignalSpy>
#include <QTest>

using namespace Qt::Literals::StringLiterals;

QTEST_GUILESS_MAIN(WhisperSpeechToTextDownloadModelJobTest)
WhisperSpeechToTextDownloadModelJobTest::WhisperSpeechToTextDownloadModelJobTest(QObject *parent)
    : QObject{parent}
{
}

void WhisperSpeechToTextDownloadModelJobTest::shouldHaveDefaultValues()
{
    WhisperSpeechToTextDownloadModelJob w;
    QVERIFY(w.model().isEmpty());
    QVERIFY(!w.wasCached());
    // No model to download: the job has no reason to run.
    QVERIFY(!w.canStart());

    const WhisperSpeechToTextDownloadModelJob::DownloadEvent event;
    QVERIFY(!event.isValid());
    QVERIFY(event.type.isEmpty());
    QCOMPARE(event.received, 0);
    QCOMPARE(event.total, 0);
    // A percent of its own is what only a progress event has.
    QCOMPARE(event.percent, -1);
}

void WhisperSpeechToTextDownloadModelJobTest::shouldAssignModel()
{
    WhisperSpeechToTextDownloadModelJob w;
    w.setModel(u"small"_s);
    QCOMPARE(w.model(), u"small"_s);
    // The download needs huggingface_hub, which is in the virtualenv.
    const bool installed = !WhisperSpeechToTextUtils::pythonScriptPath().isEmpty() && !WhisperSpeechToTextUtils::venvPython().isEmpty();
    QCOMPARE(w.canStart(), installed);

    w.setModel({});
    QVERIFY(!w.canStart());
}

void WhisperSpeechToTextDownloadModelJobTest::shouldParseEvents_data()
{
    QTest::addColumn<QByteArray>("line");
    QTest::addColumn<QString>("type");
    QTest::addColumn<qint64>("received");
    QTest::addColumn<qint64>("total");
    QTest::addColumn<int>("percent");
    QTest::addColumn<QString>("path");
    QTest::addColumn<QString>("message");

    QTest::newRow("start") << R"({"type":"start","model":"small","repo":"Systran/faster-whisper-small"})"_ba << u"start"_s << qint64(0) << qint64(0) << -1
                           << QString() << QString();
    QTest::newRow("progress") << R"({"type":"progress","model":"small","received":2665349,"total":78203619,"percent":3})"_ba << u"progress"_s << qint64(2665349)
                              << qint64(78203619) << 3 << QString() << QString();
    // The bytes of a big model do not fit in an int.
    QTest::newRow("progress-large") << R"({"type":"progress","model":"large-v3","received":3000000000,"total":3240000000,"percent":92})"_ba << u"progress"_s
                                    << qint64(3000000000) << qint64(3240000000) << 92 << QString() << QString();
    QTest::newRow("cached") << R"({"type":"cached","model":"tiny","path":"/home/foo/.cache/huggingface"})"_ba << u"cached"_s << qint64(0) << qint64(0) << -1
                            << u"/home/foo/.cache/huggingface"_s << QString();
    QTest::newRow("finished") << R"({"type":"finished","model":"tiny","path":"/home/foo/.cache/huggingface"})"_ba << u"finished"_s << qint64(0) << qint64(0)
                              << -1 << u"/home/foo/.cache/huggingface"_s << QString();
    QTest::newRow("error") << R"({"type":"error","model":"small","message":"OSError: no space left"})"_ba << u"error"_s << qint64(0) << qint64(0) << -1
                           << QString() << u"OSError: no space left"_s;
}

void WhisperSpeechToTextDownloadModelJobTest::shouldParseEvents()
{
    QFETCH(QByteArray, line);
    QFETCH(QString, type);
    QFETCH(qint64, received);
    QFETCH(qint64, total);
    QFETCH(int, percent);
    QFETCH(QString, path);
    QFETCH(QString, message);

    const WhisperSpeechToTextDownloadModelJob::DownloadEvent event = WhisperSpeechToTextDownloadModelJob::parseEvent(line);
    QVERIFY(event.isValid());
    QCOMPARE(event.type, type);
    QCOMPARE(event.received, received);
    QCOMPARE(event.total, total);
    QCOMPARE(event.percent, percent);
    QCOMPARE(event.path, path);
    QCOMPARE(event.message, message);
}

void WhisperSpeechToTextDownloadModelJobTest::shouldNotParseInvalidLine()
{
    QVERIFY(!WhisperSpeechToTextDownloadModelJob::parseEvent(QByteArray()).isValid());
    QVERIFY(!WhisperSpeechToTextDownloadModelJob::parseEvent("not json at all").isValid());
    // A line cut in two by a read is not an event yet.
    QVERIFY(!WhisperSpeechToTextDownloadModelJob::parseEvent(R"({"type":"progre)").isValid());
}

void WhisperSpeechToTextDownloadModelJobTest::shouldNotStartWithoutModel()
{
    QPointer<WhisperSpeechToTextDownloadModelJob> job = new WhisperSpeechToTextDownloadModelJob;
    QSignalSpy failedSpy(job, &WhisperSpeechToTextDownloadModelJob::downloadModelFailed);
    QSignalSpy doneSpy(job, &WhisperSpeechToTextDownloadModelJob::downloadModelDone);
    QVERIFY(!job->canStart());
    job->start();
    QCOMPARE(failedSpy.count(), 1);
    QCOMPARE(doneSpy.count(), 0);
    // The job deletes itself as it can't start.
    QVERIFY(QTest::qWaitFor([&job]() {
        return job.isNull();
    }));
}

#include "moc_whisperspeechtotextdownloadmodeljobtest.cpp"
