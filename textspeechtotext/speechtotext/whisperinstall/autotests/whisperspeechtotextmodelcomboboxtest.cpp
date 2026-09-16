/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextmodelcomboboxtest.h"
using namespace Qt::Literals::StringLiterals;

#include "whisperspeechtotextmodelcombobox.h"
#include "whisperspeechtotextutils.h"
#include <QFont>
#include <QSignalSpy>
#include <QTest>

namespace
{
[[nodiscard]] WhisperSpeechToTextModelsJob::ModelInfos testModels()
{
    return WhisperSpeechToTextModelsJob::parseModels(R"({"models":[
        {"id":"tiny","name":"tiny","sizeMib":75,"multilingual":true,"default":false},
        {"id":"small","name":"small","sizeMib":490,"multilingual":true,"default":true},
        {"id":"distil-small.en","name":"distil-small.en","sizeMib":340,"multilingual":false,"default":false}]})");
}
}

QTEST_MAIN(WhisperSpeechToTextModelComboBoxTest)
WhisperSpeechToTextModelComboBoxTest::WhisperSpeechToTextModelComboBoxTest(QObject *parent)
    : QObject{parent}
{
}

void WhisperSpeechToTextModelComboBoxTest::shouldHaveDefaultValues()
{
    WhisperSpeechToTextModelComboBox w;
    // The models are asked for by fill(), not by the constructor.
    QCOMPARE(w.count(), 0);
    QVERIFY(w.currentModel().isEmpty());
}

void WhisperSpeechToTextModelComboBoxTest::shouldFillWithModels()
{
    WhisperSpeechToTextModelComboBox w;
    w.setModels(testModels());
    QCOMPARE(w.count(), 3);
    // The identifier is what the engine stores, not the text shown.
    QCOMPARE(w.itemData(0).toString(), u"tiny"_s);
    QCOMPARE(w.itemData(2).toString(), u"distil-small.en"_s);
    for (int i = 0; i < w.count(); ++i) {
        // The size is what tells the user what is about to be downloaded.
        QVERIFY(w.itemText(i).contains(w.itemData(i).toString()));
        QVERIFY(!w.itemData(i, Qt::ToolTipRole).toString().isEmpty());
    }

    // Filling again does not append the models a second time.
    w.setModels(testModels());
    QCOMPARE(w.count(), 3);
}

void WhisperSpeechToTextModelComboBoxTest::shouldNotEmitWhileFilling()
{
    WhisperSpeechToTextModelComboBox w;
    QSignalSpy spy(&w, &WhisperSpeechToTextModelComboBox::currentModelChanged);
    w.setModels(testModels());
    // Passing through the items on the way to the selected one is not a choice.
    QCOMPARE(spy.count(), 0);

    w.setCurrentModel(u"tiny"_s);
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy.at(0).at(0).toString(), u"tiny"_s);
    QCOMPARE(w.currentModel(), u"tiny"_s);
}

void WhisperSpeechToTextModelComboBoxTest::shouldSelectTheDefaultModelWhenNoneWasChosen()
{
    WhisperSpeechToTextModelComboBox w;
    w.setModels(testModels());
    // Nothing was chosen: the model the script transcribes with is the one shown.
    QCOMPARE(w.currentModel(), u"small"_s);

    // A model which is not offered anymore does not leave the box on something else.
    w.setCurrentModel(u"a-model-which-does-not-exist"_s);
    QCOMPARE(w.currentModel(), u"small"_s);

    w.setCurrentModel({});
    QCOMPARE(w.currentModel(), u"small"_s);
}

void WhisperSpeechToTextModelComboBoxTest::shouldKeepTheModelAskedForBeforeTheModelsAreThere()
{
    WhisperSpeechToTextModelComboBox w;
    // A dialog loads its settings without waiting for the script to answer.
    w.setCurrentModel(u"distil-small.en"_s);
    QCOMPARE(w.count(), 0);
    QVERIFY(w.currentModel().isEmpty());

    w.setModels(testModels());
    QCOMPARE(w.currentModel(), u"distil-small.en"_s);
}

void WhisperSpeechToTextModelComboBoxTest::shouldFillFromTheScript()
{
    if (WhisperSpeechToTextUtils::pythonScriptPath().isEmpty() || WhisperSpeechToTextUtils::pythonVersionPath().isEmpty()) {
        QSKIP("whisper_helper.py is not installed here.");
    }
    WhisperSpeechToTextModelComboBox w;
    QSignalSpy loadedSpy(&w, &WhisperSpeechToTextModelComboBox::modelsLoaded);
    QSignalSpy failedSpy(&w, &WhisperSpeechToTextModelComboBox::modelsFailed);
    w.fill();
    QVERIFY(loadedSpy.wait());
    QCOMPARE(failedSpy.count(), 0);
    QVERIFY(w.count() > 0);
    // The script marks one of them as its default, and that is the one selected.
    QVERIFY(!w.currentModel().isEmpty());
}

void WhisperSpeechToTextModelComboBoxTest::shouldMarkTheModelsWhichAreOnDisk()
{
    WhisperSpeechToTextModelComboBox w;
    w.setModels(testModels());
    // Nothing was looked at yet: no model can be said to be missing.
    QVERIFY(!w.cachedModelsKnown());
    QVERIFY(w.cachedModels().isEmpty());
    QVERIFY(!w.isModelDownloaded(u"tiny"_s));
    // Comparing with a text of its own would compare with a locale: the sizes
    // are written the way the user of the day writes them.
    const QString plainTinyText = w.itemText(0);
    const QString plainSmallText = w.itemText(1);

    QSignalSpy spy(&w, &WhisperSpeechToTextModelComboBox::currentModelChanged);
    w.setCachedModels({u"tiny"_s});
    QVERIFY(w.cachedModelsKnown());
    QVERIFY(w.isModelDownloaded(u"tiny"_s));
    QVERIFY(!w.isModelDownloaded(u"small"_s));
    // The text of the model which is there says so, the others are untouched.
    QVERIFY(w.itemText(0) != plainTinyText);
    QVERIFY(w.itemText(0).contains(u"tiny"_s));
    QCOMPARE(w.itemText(1), plainSmallText);
    // And it is written in bold, so the list can be read without reading it.
    QVERIFY(qvariant_cast<QFont>(w.itemData(0, Qt::FontRole)).bold());
    QVERIFY(!w.itemData(1, Qt::FontRole).isValid());
    // Only the texts changed: what is selected is still what was selected.
    QCOMPARE(w.currentModel(), u"small"_s);
    QCOMPARE(spy.count(), 0);

    // An empty list, once the cache was looked at, means nothing is on disk.
    w.setCachedModels({});
    QVERIFY(w.cachedModelsKnown());
    QVERIFY(!w.isModelDownloaded(u"tiny"_s));
    QCOMPARE(w.itemText(0), plainTinyText);
    QVERIFY(!w.itemData(0, Qt::FontRole).isValid());
}

#include "moc_whisperspeechtotextmodelcomboboxtest.cpp"
