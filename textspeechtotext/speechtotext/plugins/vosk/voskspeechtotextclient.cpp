/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "voskspeechtotextclient.h"
#include "voskenginedialog.h"
#include "voskspeechtotextplugin.h"
#include <KLocalizedString>
#include <QPointer>

VoskSpeechToTextClient::VoskSpeechToTextClient(QObject *parent)
    : TextSpeechToText::SpeechToTextClient{parent}
{
}

VoskSpeechToTextClient::~VoskSpeechToTextClient() = default;

QString VoskSpeechToTextClient::name() const
{
    return QStringLiteral("vosk");
}

QString VoskSpeechToTextClient::translatedName() const
{
    return i18n("Vosk");
}

TextSpeechToText::SpeechToTextClient::EngineType VoskSpeechToTextClient::engineType() const
{
    return TextSpeechToText::SpeechToTextClient::Locale;
}

TextSpeechToText::SpeechToTextPlugin *VoskSpeechToTextClient::createTextToSpeech()
{
    return new VoskSpeechToTextPlugin;
}

bool VoskSpeechToTextClient::hasConfigurationDialog() const
{
    return true;
}

bool VoskSpeechToTextClient::showConfigureDialog(QWidget *parentWidget)
{
    bool settingsChanged = false;
    QPointer<VoskEngineDialog> dlg = new VoskEngineDialog(parentWidget);
    if (dlg->exec()) {
        Q_EMIT configureChanged();
        settingsChanged = true;
    }
    delete dlg;
    return settingsChanged;
}

#include "moc_voskspeechtotextclient.cpp"
