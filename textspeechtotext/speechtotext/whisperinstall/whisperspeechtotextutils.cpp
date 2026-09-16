/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextutils.h"
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

using namespace Qt::Literals::StringLiterals;

QString WhisperSpeechToTextUtils::pythonVersion()
{
    return u"python3"_s;
}

QString WhisperSpeechToTextUtils::pythonVersionPath()
{
    const QString path = QStandardPaths::findExecutable(WhisperSpeechToTextUtils::pythonVersion());
    return path;
}

QString WhisperSpeechToTextUtils::pythonScript()
{
    return u"whisper_helper.py"_s;
}

QString WhisperSpeechToTextUtils::pythonScriptPath()
{
    const QString path = QStandardPaths::findExecutable(WhisperSpeechToTextUtils::pythonScript());
    return path;
}

QStringList WhisperSpeechToTextUtils::requiredModules()
{
    return {u"faster-whisper"_s, u"numpy"_s};
}

QString WhisperSpeechToTextUtils::defaultVenvPath()
{
    const QString path = QDir::homePath() + u"/.venv/whisper"_s;
    return path;
}

QString WhisperSpeechToTextUtils::defaultVenvPython()
{
    const QString python = WhisperSpeechToTextUtils::defaultVenvPath() + u"/bin/python"_s;
    return python;
}

QString WhisperSpeechToTextUtils::defaultVenvPip()
{
    const QString pip = WhisperSpeechToTextUtils::defaultVenvPath() + u"/bin/pip"_s;
    return pip;
}

QString WhisperSpeechToTextUtils::venvPython()
{
    const QString python = WhisperSpeechToTextUtils::defaultVenvPython();
    return QFileInfo::exists(python) ? python : QString();
}

QString WhisperSpeechToTextUtils::venvPip()
{
    const QString pip = WhisperSpeechToTextUtils::defaultVenvPip();
    return QFileInfo::exists(pip) ? pip : QString();
}
