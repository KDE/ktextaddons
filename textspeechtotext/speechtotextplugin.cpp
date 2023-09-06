/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextplugin.h"
using namespace TextSpeechToText;

SpeechToTextPlugin::SpeechToTextPlugin(QObject *parent)
    : QObject{parent}
{
}

SpeechToTextPlugin::~SpeechToTextPlugin() = default;
