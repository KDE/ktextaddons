/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "speechtotextmanager.h"

#include "speechtotextclient.h"
#include "speechtotextengineloader.h"
#include "speechtotextplugin.h"
#include "textspeechtotext_debug.h"
#include "textspeechtotextutil.h"
#include <KConfigGroup>
#include <KSharedConfig>
#include <QAudioDevice>
#include <QAudioSource>
#include <QMediaDevices>

using namespace Qt::Literals::StringLiterals;
using namespace TextSpeechToText;

namespace
{
[[nodiscard]] QAudioDevice configuredAudioInput()
{
    const KConfigGroup group(KSharedConfig::openConfig(), TextSpeechToTextUtil::soundGroupName());
    if (const QByteArray deviceIdentifier = group.readEntry("SoundDevice", QByteArray()); !deviceIdentifier.isEmpty()) {
        const auto inputs = QMediaDevices::audioInputs();
        for (const QAudioDevice &device : inputs) {
            if (device.id() == deviceIdentifier) {
                return device;
            }
        }
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "Configured audio input device not found:" << deviceIdentifier << ". Falling back to the default one.";
    }
    return QMediaDevices::defaultAudioInput();
}
}

class SpeechToTextManager::SpeechToTextPluginPrivate
{
public:
    QString mEngineName;
    TextSpeechToText::SpeechToTextPlugin *mSpeechToTextPlugin = nullptr;
    TextSpeechToText::SpeechToTextClient *mSpeechToTextClient = nullptr;
    QAudioSource *mAudioSource = nullptr;
    EngineStatus mStatus = EngineStatus::NotLoadedYet;
    bool mRecording = false;
};

SpeechToTextManager::SpeechToTextManager(QObject *parent)
    : QObject{parent}
    , d(new SpeechToTextManager::SpeechToTextPluginPrivate)
{
}

SpeechToTextManager::~SpeechToTextManager() = default;

void SpeechToTextManager::deletePlugin()
{
    stop();
    if (d->mSpeechToTextPlugin) {
        disconnect(d->mSpeechToTextPlugin);
        delete d->mSpeechToTextPlugin;
        d->mSpeechToTextPlugin = nullptr;
    }
    // TODO delete mSpeechToTextClient ?
}

void SpeechToTextManager::loadEngine()
{
    switchEngine(TextSpeechToTextUtil::loadEngineName());
}

void SpeechToTextManager::switchEngine(const QString &engineName)
{
    deletePlugin();
    auto *const loader = TextSpeechToText::SpeechToTextEngineLoader::self();
    // An empty name simply means "nothing was configured yet": don't report it as an unknown engine.
    d->mSpeechToTextClient = engineName.isEmpty() ? nullptr : loader->createSpeechToTextClient(engineName);
    d->mEngineName = d->mSpeechToTextClient ? engineName : QString();
    if (!d->mSpeechToTextClient) {
        if (const QString fallBackEngineName = loader->fallbackFirstEngine(); !fallBackEngineName.isEmpty()) {
            d->mSpeechToTextClient = loader->createSpeechToTextClient(fallBackEngineName);
            // Remember what we actually use, otherwise a later reload would retry the missing engine.
            d->mEngineName = d->mSpeechToTextClient ? fallBackEngineName : QString();
        }
    }
    if (!d->mSpeechToTextClient) {
        d->mStatus = loader->hasEngine() ? EngineStatus::EngineNotFound : EngineStatus::NoEngineAvailable;
        warnAboutMissingPlugin();
        return;
    }

    // The engine settings dialog can make a previously unusable engine usable
    // (a language model was downloaded and marked as active), so rebuild the plugin.
    connect(d->mSpeechToTextClient,
            &TextSpeechToText::SpeechToTextClient::configureChanged,
            this,
            &SpeechToTextManager::slotEngineConfigureChanged,
            Qt::UniqueConnection);
    d->mSpeechToTextPlugin = d->mSpeechToTextClient->createTextToSpeech();
    if (!d->mSpeechToTextPlugin) {
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "Engine" << d->mEngineName << "did not create a speech to text plugin.";
        d->mStatus = EngineStatus::EngineNotUsable;
        return;
    }
    if (!d->mSpeechToTextPlugin->loadSettings()) {
        d->mStatus = EngineStatus::EngineNotUsable;
        warnAboutMissingPlugin();
        deletePlugin();
        return;
    }
    connect(d->mSpeechToTextPlugin, &TextSpeechToText::SpeechToTextPlugin::speechToTextDone, this, &SpeechToTextManager::textToSpeechDone);
    d->mStatus = EngineStatus::Ready;
}

void SpeechToTextManager::warnAboutMissingPlugin() const
{
    switch (d->mStatus) {
    case EngineStatus::NotLoadedYet:
    case EngineStatus::Ready:
        break;
    case EngineStatus::NoEngineAvailable:
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "No speech to text engine available: no plugin was found in kf6/speechtotext.";
        break;
    case EngineStatus::EngineNotFound:
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "The configured speech to text engine is not installed, and no other engine could be used instead.";
        break;
    case EngineStatus::EngineNotUsable:
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "Speech to text engine" << d->mEngineName
                                        << "is installed but not usable yet: configure it (a language model is probably missing).";
        break;
    }
}

void SpeechToTextManager::slotEngineConfigureChanged()
{
    if (!d->mSpeechToTextClient) {
        return;
    }
    switchEngine(d->mEngineName);
}

SpeechToTextManager *SpeechToTextManager::self()
{
    static SpeechToTextManager s_self;
    return &s_self;
}

bool SpeechToTextManager::hasEngine() const
{
    return TextSpeechToText::SpeechToTextEngineLoader::self()->hasEngine();
}

bool SpeechToTextManager::isReady() const
{
    return d->mSpeechToTextPlugin != nullptr;
}

void SpeechToTextManager::speechToText()
{
    // Nothing asked for an engine yet: pick the configured one now rather than staying mute forever.
    if (d->mStatus == EngineStatus::NotLoadedYet) {
        loadEngine();
    }
    if (!d->mSpeechToTextPlugin) {
        warnAboutMissingPlugin();
        return;
    }
    if (d->mRecording) {
        return;
    }
    d->mSpeechToTextPlugin->speechToText();
    if (!initializeInput()) {
        return;
    }
    d->mRecording = true;
    Q_EMIT recordingChanged(true);
}

void SpeechToTextManager::stop()
{
    if (!d->mRecording) {
        return;
    }
    d->mRecording = false;
    if (d->mAudioSource) {
        d->mAudioSource->stop();
        delete d->mAudioSource;
        d->mAudioSource = nullptr;
    }
    // Only now that no more audio can arrive, let the engine emit what it has left.
    if (d->mSpeechToTextPlugin) {
        d->mSpeechToTextPlugin->stop();
    }
    Q_EMIT recordingChanged(false);
}

bool SpeechToTextManager::isRecording() const
{
    return d->mRecording;
}

bool SpeechToTextManager::initializeInput()
{
    delete d->mAudioSource;
    d->mAudioSource = nullptr;

    QIODevice *const pluginDevice = d->mSpeechToTextPlugin->audioDevice();
    if (!pluginDevice) {
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "Plugin" << d->mEngineName << "does not provide an audio device.";
        return false;
    }

    QAudioFormat format;
    format.setSampleRate(d->mSpeechToTextPlugin->sampleRate());
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    const QAudioDevice inputDevice = configuredAudioInput();
    if (inputDevice.isNull()) {
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "No audio input device available.";
        return false;
    }
    if (!inputDevice.isFormatSupported(format)) {
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "Audio format" << format << "not supported by" << inputDevice.description();
        return false;
    }

    d->mAudioSource = new QAudioSource(inputDevice, format, this);
    d->mAudioSource->setBufferSize(8000);
    d->mAudioSource->start(pluginDevice);
    if (d->mAudioSource->error() != QAudio::NoError) {
        qCWarning(TEXTSPEECHTOTEXT_LOG) << "Unable to start audio input:" << d->mAudioSource->error();
        delete d->mAudioSource;
        d->mAudioSource = nullptr;
        return false;
    }
    return true;
}

#include "moc_speechtotextmanager.cpp"
