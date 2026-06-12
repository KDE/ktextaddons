/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "llamacppplugin.h"
// #include "autogeneratetext_lmstudio_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"
// #include "lmstudioconfiguredialog.h"
// #include "lmstudiomanager.h"
// #include "lmstudioreply.h"
// #include "lmstudiosettings.h"
#include "misc/executableutils.h"
#include <KLocalizedString>
#include <QDesktopServices>
#include <qt6keychain/keychain.h>

using namespace Qt::Literals::StringLiterals;
LLamaCppPlugin::LLamaCppPlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                               TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                               QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, instance, parent}
// , mLMStudioSettings(new LMStudioSettings)
// , mLMStudioManager(new LMStudioManager(mLMStudioSettings, this))
{
#if 0
    connect(mLMStudioManager, &LMStudioManager::modelsLoadDone, this, [this](const LMStudioManager::ModelsInfo &modelinfo) {
        if (modelinfo.hasError) {
            setReady(false);
            Q_EMIT downloadErrorOccurred(modelinfo.errorOccured);
            mModels.clear();
        } else {
            mModels = modelinfo.models;
            setReady(true);
        }
    });
    connect(mLMStudioManager, &LMStudioManager::downloadDone, this, &LLamaCppPlugin::downloadModelFinished);
    connect(mLMStudioManager, &LMStudioManager::errorOccurred, this, &LLamaCppPlugin::errorOccurred);

    connect(manager, &TextAutoGenerateText::TextAutoGenerateManager::loadEngineDone, this, [this]() {
        if (this->manager()->textAutoGenerateTextInstancesManager()->isCurrentInstance(instanceUuid())) {
            mLMStudioManager->loadModels();
        }
    });

    connect(mLMStudioManager, &LMStudioManager::finished, this, [this](const TextAutoGenerateText::TextAutoGenerateReply::Response &replyResponse) {
        if (replyResponse.hasToolCallArguments()) {
            Q_EMIT callTools(replyResponse.info);
        }
    });
    connect(mLMStudioManager, &LMStudioManager::lmsStarted, this, &LLamaCppPlugin::processStartSuccessed);
    connect(mLMStudioManager, &LMStudioManager::lmsFailed, this, &LLamaCppPlugin::processStartFailed);
#endif
}

LLamaCppPlugin::~LLamaCppPlugin()
{
    // delete mLMStudioSettings;
}

void LLamaCppPlugin::load(const KConfigGroup &config)
{
    // mLMStudioSettings->load(config);
    loadApiKey();
}

void LLamaCppPlugin::save(KConfigGroup &config)
{
#if 0
    mLMStudioSettings->save(config);
    auto writeJob = new QKeychain::WritePasswordJob(passwordServiceName());
    connect(writeJob, &QKeychain::Job::finished, this, [](QKeychain::Job *baseJob) {
        if (baseJob->error() != QKeychain::Error::NoError) {
            qCWarning(AUTOGENERATETEXT_LMSTUDIO_PLUGIN_LOG) << "Error writing password using QKeychain:" << baseJob->errorString();
        }
    });
    writeJob->setKey(QString::fromLatin1(instanceUuid()));
    writeJob->setTextData(mLMStudioManager->apiKey());
    writeJob->start();
#endif
}

void LLamaCppPlugin::remove()
{
    removeApiKey();
}

TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType LLamaCppPlugin::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Local;
}

QString LLamaCppPlugin::translatedPluginName() const
{
    return i18n("LMStudio");
}

void LLamaCppPlugin::showConfigureDialog(QWidget *parentWidget)
{
#if 0
    LMStudioConfigureDialog d(mLMStudioManager, this, parentWidget);
    if (d.exec()) {
        Q_EMIT configChanged();
    }
#endif
}

QString LLamaCppPlugin::engineName() const
{
    return "llamacpp"_L1;
}

void LLamaCppPlugin::askToAssistant(const QString &msg)
{
    Q_UNUSED(msg)
}

void LLamaCppPlugin::sendToAssistant(const SendToAssistantInfo &info)
{
#if 0
    const TextAutoGenerateText::TextAutoGenerateTextRequest req = convertSendToAssistantInfoToTextRequest(info);
    auto reply = mLMStudioManager->getChatCompletion(req);
    if (!reply) {
        return;
    }
    const QByteArray messageUuid = info.messageUuid;
    const QByteArray chatId = info.chatId;
    mConnections.insert(
        reply,
        QPair<QByteArray, QMetaObject::Connection>(messageUuid, connect(reply, &LMStudioReply::contentAdded, this, [reply, messageUuid, chatId, this]() {
                                                       manager()->replaceContent(chatId, messageUuid, reply->readResponse(), {}); // TODO
                                                   })));
    mConnections.insert(
        reply,
        QPair<QByteArray, QMetaObject::Connection>(messageUuid, connect(reply, &LMStudioReply::finished, this, [reply, messageUuid, chatId, this] {
                                                       const auto response = reply->readResponse();
                                                       if (response.hasToolCallArguments()) {
                                                           manager()->callTools(chatId, messageUuid, response.info);
                                                       } else {
                                                           manager()->changeInProgress(chatId, messageUuid, false);
                                                       }
                                                       qCDebug(AUTOGENERATETEXT_LMSTUDIO_PLUGIN_LOG) << " progress finished";
                                                       mConnections.remove(reply);
                                                       reply->deleteLater();
                                                       // Q_EMIT finished(message); // TODO add message as argument ???
                                                   })));
#endif
}

QString LLamaCppPlugin::displayName() const
{
    return {};
    // return mLMStudioSettings->displayName();
}

void LLamaCppPlugin::setDisplayName(const QString &newName)
{
    // mLMStudioSettings->setDisplayName(newName);
}

QString LLamaCppPlugin::currentModel() const
{
#if 0
    if (mLMStudioSettings->currentModel().isEmpty()) {
        return fallBackModel();
    }
    return mLMStudioSettings->currentModel();
#endif
    return {};
}

void LLamaCppPlugin::setCurrentModel(const QString &m)
{
#if 0
    mLMStudioSettings->setCurrentModel(m);
    Q_EMIT configChanged();
    Q_EMIT currentModelChanged();
#endif
}

bool LLamaCppPlugin::hasVisionSupport() const
{
    return false;
    // return mLMStudioManager->hasVisionSupport(currentModel());
}

bool LLamaCppPlugin::hasToolsSupport() const
{
    return false;
    // return mLMStudioManager->hasToolsSupport(currentModel());
}

bool LLamaCppPlugin::hasOcrSupport() const
{
    return false;
    // return mLMStudioManager->hasOcrSupport(currentModel());
}

bool LLamaCppPlugin::hasAudioSupport() const
{
    return false;
    // return mLMStudioManager->hasAudioSupport(currentModel());
}

bool LLamaCppPlugin::hasThinkSupport() const
{
    return false;
    // return mLMStudioSettings->thoughtProcessing() && mLMStudioManager->hasThinkSupport(currentModel());
}

QString LLamaCppPlugin::shareNamePrompt() const
{
    // return LMStudioCommonModelUtils::generateUserPrompt(mLMStudioSettings->shareNameType());
    return QString{};
}

QString LLamaCppPlugin::passwordServiceName() const
{
    return QStringLiteral("LLamaCppPluginAutoGenerateText");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin::ActivateInstanceActionInfo LLamaCppPlugin::activateInstanceAction()
{
#if 0
    if (mCurrentAction) {
        delete mCurrentAction;
        mCurrentAction = nullptr;
    }
    TextAutoGenerateText::TextAutoGenerateTextPlugin::ActivateInstanceActionInfo activateInstanceInfo;
    const QString lmsPath = TextAddonsWidgets::ExecutableUtils::findExecutable(u"lms"_s);
    if (lmsPath.isEmpty()) {
#if !defined(Q_OS_WIN) && !defined(Q_OS_MACOS)
        activateInstanceInfo.text = i18n("LMStudio not found on system. Ask to your administrator system to install it.");
#else
        activateInstanceInfo.text = i18n("LMStudio not found on system. Please install it.");
        auto downloadLMSAction = new QAction(i18nc("@action", "Download LMStudio"), this);
        downloadLMSAction->setObjectName(u"downloadLMSAction"_s);
        connect(downloadLMSAction, &QAction::triggered, this, &LLamaCppPlugin::slotDownloadLMStudio);
        mCurrentAction = downloadLMSAction;
#endif
    } else {
        auto startLMSAction = new QAction(i18nc("@action", "Start LMStudio"), this);
        startLMSAction->setObjectName(u"startLMSAction"_s);
        connect(startLMSAction, &QAction::triggered, this, &LLamaCppPlugin::slotLMStudioRequested);
        mCurrentAction = startLMSAction;
    }
    activateInstanceInfo.action = mCurrentAction;
    return activateInstanceInfo;
#endif
    return {};
}

void LLamaCppPlugin::slotDownloadLMStudio()
{
#ifdef Q_OS_WIN
    QDesktopServices::openUrl(QUrl(u"https://lmstudio.ai/download?os=win32"_s));
#endif
#ifdef Q_OS_MACOS
    QDesktopServices::openUrl(QUrl(u"https://lmstudio.ai/download?os=darwin"_s));
#endif
}

void LLamaCppPlugin::slotLMStudioRequested()
{
    // mLMStudioManager->startLMStudio();
}

void LLamaCppPlugin::loadApiKey()
{
#if 0
    auto readJob = new QKeychain::ReadPasswordJob(passwordServiceName());
    connect(readJob, &QKeychain::Job::finished, this, [this](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error()) {
            qCWarning(AUTOGENERATETEXT_LMSTUDIO_PLUGIN_LOG) << "We have an error during reading password " << job->errorString();
        } else {
            mLMStudioManager->setApiKey(job->textData());
            Q_EMIT loadApiKeyDone();
        }
    });
    readJob->setKey(QString::fromLatin1(instanceUuid()));
    readJob->start();
#endif
}

void LLamaCppPlugin::removeApiKey()
{
#if 0
    auto deleteJob = new QKeychain::DeletePasswordJob(passwordServiceName());
    deleteJob->setKey(QString::fromLatin1(instanceUuid()));
    connect(deleteJob, &QKeychain::Job::finished, this, [](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::DeletePasswordJob *>(baseJob);
        if (!job) {
            qCWarning(AUTOGENERATETEXT_LMSTUDIO_PLUGIN_LOG) << "Invalid job cast in removeApiKey";
            return;
        }
        if (job->error()) {
            qCWarning(AUTOGENERATETEXT_LMSTUDIO_PLUGIN_LOG) << "We have an error during deleting password " << job->errorString();
        }
    });
    deleteJob->start();
#endif
}

#include "moc_llamacppplugin.cpp"
