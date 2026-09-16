/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextmodelsjobtest.h"
using namespace Qt::Literals::StringLiterals;

#include "whisperspeechtotextmodelsjob.h"
#include "whisperspeechtotextutils.h"
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>

QTEST_GUILESS_MAIN(WhisperSpeechToTextModelsJobTest)
WhisperSpeechToTextModelsJobTest::WhisperSpeechToTextModelsJobTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void WhisperSpeechToTextModelsJobTest::shouldHaveDefaultValues()
{
    WhisperSpeechToTextModelsJob w;
    // The script is the only thing the listing needs, python3 is everywhere.
    QCOMPARE(w.canStart(), !WhisperSpeechToTextUtils::pythonScriptPath().isEmpty() && !WhisperSpeechToTextUtils::pythonVersionPath().isEmpty());

    const WhisperSpeechToTextModelsJob::ModelInfo info;
    QVERIFY(info.identifier.isEmpty());
    QVERIFY(info.name.isEmpty());
    QCOMPARE(info.sizeMib, 0);
    QVERIFY(!info.multilingual);
    QVERIFY(!info.isDefault);
    QVERIFY(!info.isValid());
}

void WhisperSpeechToTextModelsJobTest::shouldParseModels()
{
    const QByteArray json = R"({"models":[
        {"id":"small","name":"small","sizeMib":490,"multilingual":true,"default":true},
        {"id":"distil-large-v3","sizeMib":1510,"multilingual":false,"default":false}]})";
    const WhisperSpeechToTextModelsJob::ModelInfos models = WhisperSpeechToTextModelsJob::parseModels(json);
    QCOMPARE(models.count(), 2);

    QCOMPARE(models.at(0).identifier, u"small"_s);
    QCOMPARE(models.at(0).name, u"small"_s);
    QCOMPARE(models.at(0).sizeMib, 490);
    QVERIFY(models.at(0).multilingual);
    QVERIFY(models.at(0).isDefault);
    QVERIFY(models.at(0).isValid());

    // Without a name of its own, the model is shown under its identifier.
    QCOMPARE(models.at(1).identifier, u"distil-large-v3"_s);
    QCOMPARE(models.at(1).name, u"distil-large-v3"_s);
    QCOMPARE(models.at(1).sizeMib, 1510);
    QVERIFY(!models.at(1).multilingual);
    QVERIFY(!models.at(1).isDefault);
}

void WhisperSpeechToTextModelsJobTest::shouldIgnoreModelsWithoutIdentifier()
{
    const QByteArray json = R"({"models":[{"name":"nothing to load"},{"id":"tiny","sizeMib":75}]})";
    const WhisperSpeechToTextModelsJob::ModelInfos models = WhisperSpeechToTextModelsJob::parseModels(json);
    QCOMPARE(models.count(), 1);
    QCOMPARE(models.at(0).identifier, u"tiny"_s);
}

void WhisperSpeechToTextModelsJobTest::shouldNotParseInvalidJson()
{
    QVERIFY(WhisperSpeechToTextModelsJob::parseModels(QByteArray()).isEmpty());
    QVERIFY(WhisperSpeechToTextModelsJob::parseModels("not json at all").isEmpty());
    // The answer of another subcommand carries no model.
    QVERIFY(WhisperSpeechToTextModelsJob::parseModels(R"({"available":true,"missing":[]})").isEmpty());
}

void WhisperSpeechToTextModelsJobTest::shouldReportTheDefaultModel()
{
    QVERIFY(WhisperSpeechToTextModelsJob::defaultModel({}).isEmpty());

    const QByteArray json = R"({"models":[{"id":"tiny"},{"id":"small","default":true}]})";
    const WhisperSpeechToTextModelsJob::ModelInfos models = WhisperSpeechToTextModelsJob::parseModels(json);
    QCOMPARE(WhisperSpeechToTextModelsJob::defaultModel(models), u"small"_s);

    // Nothing is marked: the script did not say, so neither does the job.
    QVERIFY(WhisperSpeechToTextModelsJob::defaultModel(WhisperSpeechToTextModelsJob::parseModels(R"({"models":[{"id":"tiny"}]})")).isEmpty());
}

void WhisperSpeechToTextModelsJobTest::shouldListTheModelsOfTheScript()
{
    if (WhisperSpeechToTextUtils::pythonScriptPath().isEmpty() || WhisperSpeechToTextUtils::pythonVersionPath().isEmpty()) {
        QSKIP("whisper_helper.py is not installed here.");
    }
    // The listing needs neither the virtualenv nor faster-whisper: the table is
    // built in the script, which is what makes it usable before the install.
    auto job = new WhisperSpeechToTextModelsJob;
    QSignalSpy loadedSpy(job, &WhisperSpeechToTextModelsJob::modelsLoaded);
    QSignalSpy failedSpy(job, &WhisperSpeechToTextModelsJob::modelsFailed);
    job->start();
    QVERIFY(loadedSpy.wait());
    QCOMPARE(failedSpy.count(), 0);

    const auto models = loadedSpy.at(0).at(0).value<WhisperSpeechToTextModelsJob::ModelInfos>();
    QVERIFY(!models.isEmpty());
    QVERIFY(models.constFirst().isValid());
    QVERIFY(!WhisperSpeechToTextModelsJob::defaultModel(models).isEmpty());
    QCOMPARE(models, WhisperSpeechToTextModelsJob::modelsSynchronously());
}

#include "moc_whisperspeechtotextmodelsjobtest.cpp"
