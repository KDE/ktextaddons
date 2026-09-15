/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextplugin.h"
#include "speechtotext_vosk_debug.h"
#include "voskengineutils.h"
#include "voskspeechtotextdevice.h"
#include <QFileInfo>
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
    // Drop what a previous run left in the recognizer before the audio starts flowing in.
    mDevice->clear();
}

void VoskSpeechToTextPlugin::stop()
{
    if (!mDevice->available()) {
        return;
    }
    mDevice->finish();
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
    const QString modelPath = VoskEngineUtils::activeLanguageModelPath();
    if (modelPath.isEmpty()) {
        qCWarning(SPEECHTOTEXT_VOSK_LOG) << "No language model to use. Download one and mark it as active in the vosk plugin settings.";
        return false;
    }
    if (!QFileInfo::exists(modelPath)) {
        qCWarning(SPEECHTOTEXT_VOSK_LOG) << "Language model directory does not exist:" << modelPath;
        return false;
    }

    VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo info;
    info.sampleRate = sampleRate();
    info.modelPath = modelPath;
    if (!mDevice->initialize(std::move(info))) {
        qCWarning(SPEECHTOTEXT_VOSK_LOG) << "Impossible to initialize vosk plugin";
        return false;
    }
    setDefaultLanguage(VoskEngineUtils::loadActiveLanguage());
    return true;
}

void VoskSpeechToTextPlugin::clear()
{
    mDevice->clear();
}

#include "moc_voskspeechtotextplugin.cpp"
