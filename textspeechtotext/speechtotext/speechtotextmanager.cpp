/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextmanager.h"
#include "speechtotextclient.h"
#include "speechtotextengineloader.h"
#include "speechtotextplugin.h"

using namespace TextSpeechToText;

class SpeechToTextManager::SpeechToTextPluginPrivate
{
public:
    QString mEngineName;
    TextSpeechToText::SpeechToTextPlugin *mSpeechToTextPlugin = nullptr;
    TextSpeechToText::SpeechToTextClient *mSpeechToTextClient = nullptr;
};

SpeechToTextManager::SpeechToTextManager(QObject *parent)
    : QObject{parent}
    , d(new SpeechToTextManager::SpeechToTextPluginPrivate)
{
}

SpeechToTextManager::~SpeechToTextManager() = default;

void SpeechToTextManager::switchEngine(const QString &engineName)
{
    d->mEngineName = engineName;
    if (d->mSpeechToTextPlugin) {
        disconnect(d->mSpeechToTextPlugin);
        delete d->mSpeechToTextPlugin;
        d->mSpeechToTextPlugin = nullptr;
    }
    d->mSpeechToTextClient = TextSpeechToText::SpeechToTextEngineLoader::self()->createSpeechToTextClient(d->mEngineName);
    if (!d->mSpeechToTextClient) {
        const QString fallBackEngineName = TextSpeechToText::SpeechToTextEngineLoader::self()->fallbackFirstEngine();
        if (!fallBackEngineName.isEmpty()) {
            d->mSpeechToTextClient = TextSpeechToText::SpeechToTextEngineLoader::self()->createSpeechToTextClient(fallBackEngineName);
        }
    }
    if (d->mSpeechToTextClient) {
        d->mSpeechToTextPlugin = d->mSpeechToTextClient->createTextToSpeech();
        connect(d->mSpeechToTextPlugin, &TextSpeechToText::SpeechToTextPlugin::speechToTextDone, this, &SpeechToTextManager::textToSpeechDone);
    }
}

SpeechToTextManager *SpeechToTextManager::self()
{
    static SpeechToTextManager s_self;
    return &s_self;
}

#include "moc_speechtotextmanager.cpp"
