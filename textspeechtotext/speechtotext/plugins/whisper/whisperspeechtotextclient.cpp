/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "whisperspeechtotextclient.h"

#include "whisperspeechtotextinstallpythondialog.h"
#include "whisperspeechtotextplugin.h"
#include <KLocalizedString>
#include <QPointer>

using namespace Qt::Literals::StringLiterals;
WhisperSpeechToTextClient::WhisperSpeechToTextClient(QObject *parent)
    : TextSpeechToText::SpeechToTextClient{parent}
{
}

WhisperSpeechToTextClient::~WhisperSpeechToTextClient() = default;

QString WhisperSpeechToTextClient::name() const
{
    return u"whisper"_s;
}

QString WhisperSpeechToTextClient::translatedName() const
{
    return i18n("Whisper");
}

TextSpeechToText::SpeechToTextClient::EngineType WhisperSpeechToTextClient::engineType() const
{
    return TextSpeechToText::SpeechToTextClient::Locale;
}

TextSpeechToText::SpeechToTextPlugin *WhisperSpeechToTextClient::createTextToSpeech()
{
    return new WhisperSpeechToTextPlugin;
}

bool WhisperSpeechToTextClient::hasConfigurationDialog() const
{
    return true;
}

bool WhisperSpeechToTextClient::showConfigureDialog(QWidget *parentWidget)
{
    QPointer<WhisperSpeechToTextInstallPythonDialog> dlg = new WhisperSpeechToTextInstallPythonDialog(parentWidget);
    dlg->exec();
    delete dlg;

    const bool settingsChanged = true; //(previousActiveLanguage != VoskEngineUtils::loadActiveLanguage());
    if (settingsChanged) {
        Q_EMIT configureChanged();
    }
    return settingsChanged;
}

#include "moc_whisperspeechtotextclient.cpp"
