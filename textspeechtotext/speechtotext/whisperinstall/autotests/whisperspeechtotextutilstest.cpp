/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextutilstest.h"
using namespace Qt::Literals::StringLiterals;

#include "whisperspeechtotextutils.h"
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
#include <QTest>

QTEST_GUILESS_MAIN(WhisperSpeechToTextUtilsTest)
WhisperSpeechToTextUtilsTest::WhisperSpeechToTextUtilsTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void WhisperSpeechToTextUtilsTest::shouldDefinePythonVersion()
{
    QCOMPARE(WhisperSpeechToTextUtils::pythonVersion(), u"python3"_s);
}

void WhisperSpeechToTextUtilsTest::shouldDefinePythonScript()
{
    QCOMPARE(WhisperSpeechToTextUtils::pythonScript(), u"whisper_helper.py"_s);
}

void WhisperSpeechToTextUtilsTest::shouldResolvePythonVersionPath()
{
    const QString path = WhisperSpeechToTextUtils::pythonVersionPath();
    QCOMPARE(path, QStandardPaths::findExecutable(WhisperSpeechToTextUtils::pythonVersion()));
    if (path.isEmpty()) {
        // No python interpreter installed here, nothing more to verify.
        return;
    }
    const QFileInfo fileInfo(path);
    QVERIFY(fileInfo.isAbsolute());
    QVERIFY(fileInfo.isExecutable());
    QCOMPARE(fileInfo.baseName(), WhisperSpeechToTextUtils::pythonVersion());
}

void WhisperSpeechToTextUtilsTest::shouldResolvePythonScriptPath()
{
    const QString path = WhisperSpeechToTextUtils::pythonScriptPath();
    QCOMPARE(path, QStandardPaths::findExecutable(WhisperSpeechToTextUtils::pythonScript()));
    if (path.isEmpty()) {
        // The script is not installed in this environment.
        return;
    }
    const QFileInfo fileInfo(path);
    QVERIFY(fileInfo.isAbsolute());
    QVERIFY(fileInfo.isExecutable());
    QCOMPARE(fileInfo.fileName(), WhisperSpeechToTextUtils::pythonScript());
}

void WhisperSpeechToTextUtilsTest::shouldDefineRequiredModules()
{
    // The pip names of REQUIRED_MODULES in whisper_helper.py.
    QCOMPARE(WhisperSpeechToTextUtils::requiredModules(), QStringList({u"faster-whisper"_s, u"numpy"_s}));
}

void WhisperSpeechToTextUtilsTest::shouldDefineVenvPaths()
{
    const QString venvPath = WhisperSpeechToTextUtils::defaultVenvPath();
    QCOMPARE(venvPath, QDir::homePath() + u"/.venv/whisper"_s);
    QCOMPARE(WhisperSpeechToTextUtils::defaultVenvPython(), venvPath + u"/bin/python"_s);
    QCOMPARE(WhisperSpeechToTextUtils::defaultVenvPip(), venvPath + u"/bin/pip"_s);
    // The kokoro virtualenv must not be reused, the modules are not the same.
    QVERIFY(!venvPath.endsWith(u"/kokoro"_s));
}

void WhisperSpeechToTextUtilsTest::shouldOnlyReturnExistingVenvExecutables()
{
    // venvPython()/venvPip() answer an empty string as long as the virtualenv
    // has not been created, which is what tells the jobs to install it.
    const QString python = WhisperSpeechToTextUtils::venvPython();
    QCOMPARE(python.isEmpty(), !QFileInfo::exists(WhisperSpeechToTextUtils::defaultVenvPython()));
    if (!python.isEmpty()) {
        QCOMPARE(python, WhisperSpeechToTextUtils::defaultVenvPython());
    }

    const QString pip = WhisperSpeechToTextUtils::venvPip();
    QCOMPARE(pip.isEmpty(), !QFileInfo::exists(WhisperSpeechToTextUtils::defaultVenvPip()));
    if (!pip.isEmpty()) {
        QCOMPARE(pip, WhisperSpeechToTextUtils::defaultVenvPip());
    }
}

#include "moc_whisperspeechtotextutilstest.cpp"
