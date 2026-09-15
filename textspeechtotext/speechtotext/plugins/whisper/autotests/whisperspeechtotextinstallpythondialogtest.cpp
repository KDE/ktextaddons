/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextinstallpythondialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "whisperspeechtotextinstallpythondialog.h"
#include "whisperspeechtotextinstallpythonwidget.h"
#include "whisperspeechtotextutils.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

QTEST_MAIN(WhisperSpeechToTextInstallPythonDialogTest)
WhisperSpeechToTextInstallPythonDialogTest::WhisperSpeechToTextInstallPythonDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void WhisperSpeechToTextInstallPythonDialogTest::shouldHaveDefaultValues()
{
    WhisperSpeechToTextInstallPythonDialog d;
    QVERIFY(!d.windowTitle().isEmpty());

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto widget = d.findChild<WhisperSpeechToTextInstallPythonWidget *>(u"mWhisperInstallPythonWidget"_s);
    QVERIFY(widget);

    auto box = d.findChild<QDialogButtonBox *>(u"box"_s);
    QVERIFY(box);

    auto closeButton = d.findChild<QPushButton *>(u"mCloseButton"_s);
    QVERIFY(closeButton);
    // Nothing is running yet, the dialog can be closed.
    QVERIFY(closeButton->isEnabled());
    QCOMPARE(box->buttonRole(closeButton), QDialogButtonBox::RejectRole);
}

void WhisperSpeechToTextInstallPythonDialogTest::shouldForwardModulesToWidget()
{
    WhisperSpeechToTextInstallPythonDialog d;
    auto widget = d.findChild<WhisperSpeechToTextInstallPythonWidget *>(u"mWhisperInstallPythonWidget"_s);
    QVERIFY(widget);
    QVERIFY(widget->modules().isEmpty());

    const QStringList modules = WhisperSpeechToTextUtils::requiredModules();
    d.setModules(modules);
    QCOMPARE(widget->modules(), modules);
}

void WhisperSpeechToTextInstallPythonDialogTest::shouldDisableCloseButtonWhileInstalling()
{
    WhisperSpeechToTextInstallPythonDialog d;
    auto widget = d.findChild<WhisperSpeechToTextInstallPythonWidget *>(u"mWhisperInstallPythonWidget"_s);
    QVERIFY(widget);
    auto closeButton = d.findChild<QPushButton *>(u"mCloseButton"_s);
    QVERIFY(closeButton);

    // Closing the dialog would kill pip in the middle of the installation.
    Q_EMIT widget->installInProgress(true);
    QVERIFY(!closeButton->isEnabled());
    Q_EMIT widget->installInProgress(false);
    QVERIFY(closeButton->isEnabled());

    // With nothing to install no process is started, so the button never gets disabled.
    d.startInstall();
    QVERIFY(closeButton->isEnabled());
}

#include "moc_whisperspeechtotextinstallpythondialogtest.cpp"
