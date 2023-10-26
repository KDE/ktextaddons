/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextmanager.h"
#include "speechtotextclient.h"
#include "speechtotextengineloader.h"
#include "speechtotextplugin.h"
#include "textspeechtotext_debug.h"
#include <QAudioSource>

using namespace TextSpeechToText;

class SpeechToTextManager::SpeechToTextPluginPrivate
{
public:
    QString mEngineName;
    TextSpeechToText::SpeechToTextPlugin *mSpeechToTextPlugin = nullptr;
    TextSpeechToText::SpeechToTextClient *mSpeechToTextClient = nullptr;
    QAudioSource *mAudioSource = nullptr;
};

SpeechToTextManager::SpeechToTextManager(QObject *parent)
    : QObject{parent}
    , d(new SpeechToTextManager::SpeechToTextPluginPrivate)
{
}

SpeechToTextManager::~SpeechToTextManager() = default;

void SpeechToTextManager::deletePlugin()
{
    if (d->mSpeechToTextPlugin) {
        disconnect(d->mSpeechToTextPlugin);
        delete d->mSpeechToTextPlugin;
        d->mSpeechToTextPlugin = nullptr;
    }
    // TODO delete mSpeechToTextClient ?
}

void SpeechToTextManager::switchEngine(const QString &engineName)
{
    d->mEngineName = engineName;
    deletePlugin();
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
        if (!d->mSpeechToTextPlugin->loadSettings()) {
            qCWarning(TEXTSPEECHTOTEXT_LOG) << "Impossible to initialize text to speech plugin";
            deletePlugin();
        }
    }
}

SpeechToTextManager *SpeechToTextManager::self()
{
    static SpeechToTextManager s_self;
    return &s_self;
}

void SpeechToTextManager::speechToText()
{
    d->mSpeechToTextPlugin->speechToText();
}

void SpeechToTextManager::initializeInput()
{
    if (!d->mSpeechToTextPlugin) {
        return;
    }

    delete d->mAudioSource;

    QAudioFormat format;
    format.setSampleRate(d->mSpeechToTextPlugin->sampleRate());
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    d->mAudioSource = new QAudioSource(format, this);
    d->mAudioSource->setBufferSize(8000);
    d->mAudioSource->start(d->mSpeechToTextPlugin->audioDevice());
}

#include "moc_speechtotextmanager.cpp"
