/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextutils.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>

using namespace Qt::Literals::StringLiterals;

namespace
{
[[nodiscard]] QString readSetting(const QString &key)
{
    const KConfigGroup group(KSharedConfig::openConfig(), WhisperSpeechToTextUtils::groupName());
    return group.readEntry(key, QString());
}

void writeSetting(const QString &key, const QString &value)
{
    KConfigGroup group(KSharedConfig::openConfig(), WhisperSpeechToTextUtils::groupName());
    // An empty value is "whatever the script defaults to", which is not something
    // to freeze in the configuration file.
    if (value.isEmpty()) {
        group.deleteEntry(key);
    } else {
        group.writeEntry(key, value);
    }
    group.sync();
}
}

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

QString WhisperSpeechToTextUtils::groupName()
{
    return u"WhisperSpeechToText"_s;
}

QString WhisperSpeechToTextUtils::modelKey()
{
    return u"Model"_s;
}

QString WhisperSpeechToTextUtils::languageKey()
{
    return u"Language"_s;
}

QString WhisperSpeechToTextUtils::computeTypeKey()
{
    return u"ComputeType"_s;
}

QString WhisperSpeechToTextUtils::deviceKey()
{
    return u"Device"_s;
}

QString WhisperSpeechToTextUtils::loadModel()
{
    return readSetting(WhisperSpeechToTextUtils::modelKey());
}

void WhisperSpeechToTextUtils::saveModel(const QString &model)
{
    writeSetting(WhisperSpeechToTextUtils::modelKey(), model);
}

QString WhisperSpeechToTextUtils::loadLanguage()
{
    return readSetting(WhisperSpeechToTextUtils::languageKey());
}

void WhisperSpeechToTextUtils::saveLanguage(const QString &language)
{
    writeSetting(WhisperSpeechToTextUtils::languageKey(), language);
}

QString WhisperSpeechToTextUtils::loadComputeType()
{
    return readSetting(WhisperSpeechToTextUtils::computeTypeKey());
}

void WhisperSpeechToTextUtils::saveComputeType(const QString &computeType)
{
    writeSetting(WhisperSpeechToTextUtils::computeTypeKey(), computeType);
}

QString WhisperSpeechToTextUtils::loadDevice()
{
    return readSetting(WhisperSpeechToTextUtils::deviceKey());
}

void WhisperSpeechToTextUtils::saveDevice(const QString &device)
{
    writeSetting(WhisperSpeechToTextUtils::deviceKey(), device);
}
