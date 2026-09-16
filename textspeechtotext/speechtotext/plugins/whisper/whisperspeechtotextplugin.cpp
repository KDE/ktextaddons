/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "whisperspeechtotextplugin.h"
#include "speechtotext_whisper_debug.h"
#include "whisperspeechtotextdevice.h"
#include "whisperspeechtotextutils.h"

WhisperSpeechToTextPlugin::WhisperSpeechToTextPlugin(QObject *parent)
    : TextSpeechToText::SpeechToTextPlugin{parent}
    , mDevice(new WhisperSpeechToTextDevice(this))
{
    connect(mDevice, &WhisperSpeechToTextDevice::result, this, &WhisperSpeechToTextPlugin::speechToTextDone);
    // The engine has no way of showing an error yet: the log is where a broken
    // python side can be seen.
    connect(mDevice, &WhisperSpeechToTextDevice::errorOccurred, this, [](const QString &message) {
        qCWarning(SPEECHTOTEXT_WHISPER_LOG) << message;
    });
}

WhisperSpeechToTextPlugin::~WhisperSpeechToTextPlugin() = default;

void WhisperSpeechToTextPlugin::speechToText()
{
    if (!mDevice->available()) {
        qCWarning(SPEECHTOTEXT_WHISPER_LOG) << "Whisper is not available";
        return;
    }
    // Drop what a previous run left before the audio starts flowing in.
    mDevice->clear();
}

void WhisperSpeechToTextPlugin::stop()
{
    mDevice->finish();
}

int WhisperSpeechToTextPlugin::sampleRate() const
{
    // SAMPLE_RATE of whisper_helper.py: whisper is trained on 16 kHz.
    return 16000;
}

QIODevice *WhisperSpeechToTextPlugin::audioDevice() const
{
    return mDevice;
}

bool WhisperSpeechToTextPlugin::loadSettings()
{
    WhisperSpeechToTextDevice::WhisperSpeechToTextDeviceInfo info;
    // Everything empty is legitimate: the script then transcribes with its own
    // defaults, which is what an engine nobody configured has to do.
    info.model = WhisperSpeechToTextUtils::loadModel();
    info.language = WhisperSpeechToTextUtils::loadLanguage();
    info.computeType = WhisperSpeechToTextUtils::loadComputeType();
    info.device = WhisperSpeechToTextUtils::loadDevice();
    setDefaultLanguage(info.language);
    if (!mDevice->initialize(std::move(info))) {
        qCWarning(SPEECHTOTEXT_WHISPER_LOG) << "Impossible to initialize whisper plugin. Install it from the engine settings.";
        return false;
    }
    return true;
}

void WhisperSpeechToTextPlugin::clear()
{
    // The dictation is what holds the audio: starting a new one is the way to
    // drop what the previous one had buffered in the script.
    mDevice->clear();
}

#include "moc_whisperspeechtotextplugin.cpp"
