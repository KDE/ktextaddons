/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstallpythonwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "whisperspeechtotextinstallpythonwidget.h"
#include "whisperspeechtotextmodelcombobox.h"
#include "whisperspeechtotextutils.h"
#include <QPlainTextEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QSignalSpy>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(WhisperSpeechToTextInstallPythonWidgetTest)
WhisperSpeechToTextInstallPythonWidgetTest::WhisperSpeechToTextInstallPythonWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void WhisperSpeechToTextInstallPythonWidgetTest::shouldHaveDefaultValues()
{
    const WhisperSpeechToTextInstallPythonWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mPlainTextEdit = w.findChild<QPlainTextEdit *>(u"mPlainTextEdit"_s);
    QVERIFY(mPlainTextEdit);
    // The log of pip is shown, not edited.
    QVERIFY(mPlainTextEdit->isReadOnly());
    QVERIFY(mPlainTextEdit->toPlainText().isEmpty());

    QVERIFY(w.modules().isEmpty());

    auto mDownloadProgressBar = w.findChild<QProgressBar *>(u"mDownloadProgressBar"_s);
    QVERIFY(mDownloadProgressBar);
    // Nothing is being downloaded: the bar would only be in the way.
    QVERIFY(mDownloadProgressBar->isHidden());

    auto mDownloadModelButton = w.findChild<QPushButton *>(u"mDownloadModelButton"_s);
    QVERIFY(mDownloadModelButton);
    // There is nothing to download as long as the models are not listed.
    QVERIFY(!mDownloadModelButton->isEnabled());

    QVERIFY(w.findChild<WhisperSpeechToTextModelComboBox *>(u"mModelComboBox"_s));
}

void WhisperSpeechToTextInstallPythonWidgetTest::shouldAssignModules()
{
    WhisperSpeechToTextInstallPythonWidget w;
    const QStringList modules = WhisperSpeechToTextUtils::requiredModules();
    w.setModules(modules);
    QCOMPARE(w.modules(), modules);
    w.setModules({});
    QVERIFY(w.modules().isEmpty());
}

void WhisperSpeechToTextInstallPythonWidgetTest::shouldNotInstallWithoutModules()
{
    WhisperSpeechToTextInstallPythonWidget w;
    const QSignalSpy doneSpy(&w, &WhisperSpeechToTextInstallPythonWidget::installDone);
    const QSignalSpy failedSpy(&w, &WhisperSpeechToTextInstallPythonWidget::installFailed);
    const QSignalSpy progressSpy(&w, &WhisperSpeechToTextInstallPythonWidget::installInProgress);

    w.startInstall();
    // Nothing to install is a success, and no process is started for it.
    QCOMPARE(doneSpy.count(), 1);
    QCOMPARE(failedSpy.count(), 0);
    // The end is still reported, otherwise what the caller disabled stays disabled.
    QCOMPARE(progressSpy.count(), 1);
    QCOMPARE(progressSpy.at(0).at(0).toBool(), false);

    auto mPlainTextEdit = w.findChild<QPlainTextEdit *>(u"mPlainTextEdit"_s);
    QVERIFY(mPlainTextEdit);
    QVERIFY(!mPlainTextEdit->toPlainText().isEmpty());
}

void WhisperSpeechToTextInstallPythonWidgetTest::shouldOfferToDownloadAModel()
{
    if (WhisperSpeechToTextUtils::pythonScriptPath().isEmpty() || WhisperSpeechToTextUtils::pythonVersionPath().isEmpty()) {
        QSKIP("whisper_helper.py is not installed here.");
    }
    WhisperSpeechToTextInstallPythonWidget w;
    auto mModelComboBox = w.findChild<WhisperSpeechToTextModelComboBox *>(u"mModelComboBox"_s);
    QVERIFY(mModelComboBox);
    QSignalSpy loadedSpy(mModelComboBox, &WhisperSpeechToTextModelComboBox::modelsLoaded);
    QVERIFY(loadedSpy.wait());

    // The models are listed without the virtualenv: choosing one is possible
    // before whisper is installed.
    QVERIFY(mModelComboBox->count() > 0);
    QVERIFY(!mModelComboBox->currentModel().isEmpty());
    auto mDownloadModelButton = w.findChild<QPushButton *>(u"mDownloadModelButton"_s);
    QVERIFY(mDownloadModelButton);
    QVERIFY(mDownloadModelButton->isEnabled());
    // Filling the box is not the user choosing a model, and nothing was downloaded.
    auto mPlainTextEdit = w.findChild<QPlainTextEdit *>(u"mPlainTextEdit"_s);
    QVERIFY(mPlainTextEdit);
    QVERIFY(mPlainTextEdit->toPlainText().isEmpty());
}

void WhisperSpeechToTextInstallPythonWidgetTest::shouldStoreTheModelWhichWasChosen()
{
    if (WhisperSpeechToTextUtils::pythonScriptPath().isEmpty() || WhisperSpeechToTextUtils::pythonVersionPath().isEmpty()) {
        QSKIP("whisper_helper.py is not installed here.");
    }
    WhisperSpeechToTextUtils::saveModel({});
    WhisperSpeechToTextInstallPythonWidget w;
    auto mModelComboBox = w.findChild<WhisperSpeechToTextModelComboBox *>(u"mModelComboBox"_s);
    QVERIFY(mModelComboBox);
    QSignalSpy loadedSpy(mModelComboBox, &WhisperSpeechToTextModelComboBox::modelsLoaded);
    QVERIFY(loadedSpy.wait());
    // Showing the dialog stores nothing: the model is still the one of the script.
    QVERIFY(WhisperSpeechToTextUtils::loadModel().isEmpty());

    QVERIFY(mModelComboBox->count() > 1);
    const QString other = mModelComboBox->itemData(mModelComboBox->currentIndex() == 0 ? 1 : 0).toString();
    mModelComboBox->setCurrentModel(other);
    // The dialog has no button to apply anything: choosing is storing.
    QCOMPARE(WhisperSpeechToTextUtils::loadModel(), other);

    WhisperSpeechToTextUtils::saveModel({});
}

#include "moc_whisperspeechtotextinstallpythonwidgettest.cpp"
