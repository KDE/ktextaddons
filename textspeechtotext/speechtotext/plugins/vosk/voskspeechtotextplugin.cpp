/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextplugin.h"
#include "speechtotext_vosk_debug.h"
#include "voskengineutils.h"
#include "voskspeechtotextdevice.h"
#include <QIODevice>

using namespace Qt::Literals::StringLiterals;

VoskSpeechToTextPlugin::VoskSpeechToTextPlugin(QObject *parent)
    : TextSpeechToText::SpeechToTextPlugin{parent}
    , mDevice(new VoskSpeechToTextDevice(this))
{
    connect(mDevice, &VoskSpeechToTextDevice::result, this, &VoskSpeechToTextPlugin::speechToTextDone);
}

VoskSpeechToTextPlugin::~VoskSpeechToTextPlugin() = default;

void VoskSpeechToTextPlugin::speechToText()
{
    if (!mDevice->available()) {
        qCWarning(SPEECHTOTEXT_VOSK_LOG) << "Vosk is not available";
        return;
    }
    // TODO
}

int VoskSpeechToTextPlugin::sampleRate() const
{
    return 16000;
}

QIODevice *VoskSpeechToTextPlugin::audioDevice() const
{
    return mDevice;
}

bool VoskSpeechToTextPlugin::loadSettings()
{
    const QString activeLanguage = VoskEngineUtils::loadActiveLanguage();
    if (activeLanguage.isEmpty()) {
        qCWarning(SPEECHTOTEXT_VOSK_LOG) << "No active language defined. Impossible to initialize vosk plugin";
        return false;
    }
    // First setSampleRate
    VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo info;
    info.sampleRate = sampleRate();
    info.modelDir = VoskEngineUtils::storageLanguagePath() + u'/';
    info.formattedLang = activeLanguage;
    if (!mDevice->initialize(std::move(info))) {
        qCWarning(SPEECHTOTEXT_VOSK_LOG) << "Impossible to initialize vosk plugin";
        return false;
    }
    return true;
}

void VoskSpeechToTextPlugin::clear()
{
    mDevice->clear();
}

#include "moc_voskspeechtotextplugin.cpp"
