/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstallpythonwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "whisperspeechtotextinstallpythonwidget.h"
#include "whisperspeechtotextutils.h"
#include <QPlainTextEdit>
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
    WhisperSpeechToTextInstallPythonWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mPlainTextEdit = w.findChild<QPlainTextEdit *>(u"mPlainTextEdit"_s);
    QVERIFY(mPlainTextEdit);
    // The log of pip is shown, not edited.
    QVERIFY(mPlainTextEdit->isReadOnly());
    QVERIFY(mPlainTextEdit->toPlainText().isEmpty());

    QVERIFY(w.modules().isEmpty());
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
    QSignalSpy doneSpy(&w, &WhisperSpeechToTextInstallPythonWidget::installDone);
    QSignalSpy failedSpy(&w, &WhisperSpeechToTextInstallPythonWidget::installFailed);
    QSignalSpy progressSpy(&w, &WhisperSpeechToTextInstallPythonWidget::installInProgress);

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

#include "moc_whisperspeechtotextinstallpythonwidgettest.cpp"
