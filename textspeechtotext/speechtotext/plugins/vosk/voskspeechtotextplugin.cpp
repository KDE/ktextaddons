/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextplugin.h"
#include "speechtotext_vosk_debug.h"
#include "voskspeechtotextdevice.h"
#include <QDebug>
#include <QIODevice>

VoskSpeechToTextPlugin::VoskSpeechToTextPlugin(QObject *parent)
    : TextSpeechToText::SpeechToTextPlugin{parent}
    , mDevice(new VoskSpeechToTextDevice(this))
{
    connect(mDevice, &VoskSpeechToTextDevice::result, this, &VoskSpeechToTextPlugin::speechToTextDone);
}

VoskSpeechToTextPlugin::~VoskSpeechToTextPlugin() = default;

void VoskSpeechToTextPlugin::speechToText()
{
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
    // First setSampleRate
    VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo info;
    info.sampleRate = sampleRate();
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
