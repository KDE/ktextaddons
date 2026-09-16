/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextcachedmodelsjobtest.h"
using namespace Qt::Literals::StringLiterals;

#include "whisperspeechtotextcachedmodelsjob.h"
#include "whisperspeechtotextmodelsjob.h"
#include "whisperspeechtotextutils.h"
#include <QSignalSpy>
#include <QTest>

QTEST_GUILESS_MAIN(WhisperSpeechToTextCachedModelsJobTest)
WhisperSpeechToTextCachedModelsJobTest::WhisperSpeechToTextCachedModelsJobTest(QObject *parent)
    : QObject{parent}
{
}

void WhisperSpeechToTextCachedModelsJobTest::shouldHaveDefaultValues()
{
    WhisperSpeechToTextCachedModelsJob w;
    // Looking at the cache needs huggingface_hub, which is in the virtualenv.
    const bool installed = !WhisperSpeechToTextUtils::pythonScriptPath().isEmpty() && !WhisperSpeechToTextUtils::venvPython().isEmpty();
    QCOMPARE(w.canStart(), installed);
}

void WhisperSpeechToTextCachedModelsJobTest::shouldOnlyKeepTheCachedModels()
{
    const QByteArray output = R"({"type":"cached","model":"tiny","repo":"Systran/faster-whisper-tiny","path":"/home/foo/.cache"})"
                              "\n"
                              R"({"type":"missing","model":"base","repo":"Systran/faster-whisper-base","sizeMib":145})"
                              "\n"
                              R"({"type":"cached","model":"medium","repo":"Systran/faster-whisper-medium","path":"/home/foo/.cache"})"
                              "\n";
    QCOMPARE(WhisperSpeechToTextCachedModelsJob::parseCachedModels(output), QStringList({u"tiny"_s, u"medium"_s}));

    // A model the script does not know is reported as an error, not as cached.
    const QByteArray unknown = R"({"type":"error","model":"nope","message":"unknown model: 'nope'"})"
                               "\n";
    QVERIFY(WhisperSpeechToTextCachedModelsJob::parseCachedModels(unknown).isEmpty());
}

void WhisperSpeechToTextCachedModelsJobTest::shouldNotParseInvalidOutput()
{
    QVERIFY(WhisperSpeechToTextCachedModelsJob::parseCachedModels(QByteArray()).isEmpty());
    QVERIFY(WhisperSpeechToTextCachedModelsJob::parseCachedModels("not json at all\n").isEmpty());
    // Nothing on disk yet is what a fresh install answers.
    QVERIFY(WhisperSpeechToTextCachedModelsJob::parseCachedModels(R"({"type":"missing","model":"tiny","sizeMib":75})"
                                                                  "\n")
                .isEmpty());
}

void WhisperSpeechToTextCachedModelsJobTest::shouldAskTheScript()
{
    if (WhisperSpeechToTextUtils::pythonScriptPath().isEmpty() || WhisperSpeechToTextUtils::venvPython().isEmpty()) {
        QSKIP("whisper is not installed here.");
    }
    auto job = new WhisperSpeechToTextCachedModelsJob;
    QSignalSpy loadedSpy(job, &WhisperSpeechToTextCachedModelsJob::cachedModelsLoaded);
    QSignalSpy failedSpy(job, &WhisperSpeechToTextCachedModelsJob::cachedModelsFailed);
    job->start();
    // Waiting for the answer only would wait for the timeout when it failed.
    QVERIFY(QTest::qWaitFor(
        [&loadedSpy, &failedSpy]() {
            return loadedSpy.count() > 0 || failedSpy.count() > 0;
        },
        30000));
    // An installed script older than this library is what a failure means here.
    QCOMPARE(failedSpy.count(), 0);

    // Whatever is cached here, it can only be models the script offers.
    const QStringList cached = loadedSpy.at(0).at(0).toStringList();
    QStringList known;
    const WhisperSpeechToTextModelsJob::ModelInfos models = WhisperSpeechToTextModelsJob::modelsSynchronously();
    for (const WhisperSpeechToTextModelsJob::ModelInfo &info : models) {
        known.append(info.identifier);
    }
    for (const QString &model : cached) {
        QVERIFY(known.contains(model));
    }
}

#include "moc_whisperspeechtotextcachedmodelsjobtest.cpp"
