/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextmanager.h"
#include "speechtotextengineloader.h"
#include "speechtotextplugin.h"
using namespace TextSpeechToText;

class SpeechToTextManager::SpeechToTextPluginPrivate
{
public:
    TextSpeechToText::SpeechToTextPlugin *mSpeechToTextPlugin = nullptr;
};

SpeechToTextManager::SpeechToTextManager(QObject *parent)
    : QObject{parent}
    , d(new SpeechToTextManager::SpeechToTextPluginPrivate)
{
}

SpeechToTextManager::~SpeechToTextManager() = default;

void SpeechToTextManager::switchEngine(const QString &engineName)
{
    if (d->mSpeechToTextPlugin) {
        disconnect(d->mSpeechToTextPlugin);
        delete d->mSpeechToTextPlugin;
        d->mSpeechToTextPlugin = nullptr;
    }
    // TODO
}

#include "moc_speechtotextmanager.cpp"
