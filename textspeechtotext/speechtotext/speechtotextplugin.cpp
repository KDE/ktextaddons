/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "speechtotextplugin.h"
using namespace TextSpeechToText;

class TextSpeechToText::SpeechToTextPluginPrivate
{
public:
    QString mResult;
};

SpeechToTextPlugin::SpeechToTextPlugin(QObject *parent)
    : QObject{parent}
    , d(new TextSpeechToText::SpeechToTextPluginPrivate())
{
}

SpeechToTextPlugin::~SpeechToTextPlugin() = default;

QString SpeechToTextPlugin::result() const
{
    return d->mResult;
}

#include "moc_speechtotextplugin.cpp"
