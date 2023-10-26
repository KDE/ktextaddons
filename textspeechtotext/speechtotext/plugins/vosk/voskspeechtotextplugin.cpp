/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskspeechtotextplugin.h"
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

void VoskSpeechToTextPlugin::loadSettings()
{
    // First setSampleRate
    VoskSpeechToTextDevice::VoskSpeechToTextDeviceInfo info;
    info.sampleRate = sampleRate();
    if (!mDevice->initialize(std::move(info))) {
        // TODO convert to debug category
        qWarning() << "Impossible to initialize vosk plugin";
    }
}

void VoskSpeechToTextPlugin::clear()
{
    mDevice->clear();
}

#include "moc_voskspeechtotextplugin.cpp"
