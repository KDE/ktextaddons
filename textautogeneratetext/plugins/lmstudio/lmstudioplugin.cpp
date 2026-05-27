/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lmstudioplugin.h"
#include "autogeneratetext_lmstudio_plugin_debug.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "lmstudioconfiguredialog.h"
#include "lmstudiomanager.h"
#include "lmstudioreply.h"
#include "lmstudiosettings.h"
#include "misc/executableutils.h"
#include <KLocalizedString>
#include <qt6keychain/keychain.h>
#include <qtpreprocessorsupport.h>

using namespace Qt::Literals::StringLiterals;
LMStudioPlugin::LMStudioPlugin(TextAutoGenerateText::TextAutoGenerateManager *manager,
                               TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                               QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, instance, parent}
    , mLMStudioSettings(new LMStudioSettings)
    , mLMStudioManager(new LMStudioManager(mLMStudioSettings, this))
{
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
    connect(mLMStudioManager, &LMStudioManager::downloadDone, this, &LMStudioPlugin::downloadModelFinished);
    connect(mLMStudioManager, &LMStudioManager::errorOccurred, this, &LMStudioPlugin::errorOccurred);

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
}

LMStudioPlugin::~LMStudioPlugin()
{
    delete mLMStudioSettings;
}

void LMStudioPlugin::load(const KConfigGroup &config)
{
    mLMStudioSettings->load(config);
    loadApiKey();
}

void LMStudioPlugin::save(KConfigGroup &config)
{
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
}

void LMStudioPlugin::remove()
{
    removeApiKey();
}

TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType LMStudioPlugin::engineType() const
{
    return TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Local;
}

QString LMStudioPlugin::translatedPluginName() const
{
    return i18n("LMStudio");
}

void LMStudioPlugin::showConfigureDialog(QWidget *parentWidget)
{
    Q_UNUSED(parentWidget)
    LMStudioConfigureDialog d(mLMStudioManager, this, parentWidget);
    if (d.exec()) {
        Q_EMIT configChanged();
    }
}

QString LMStudioPlugin::engineName() const
{
    return "lmstudio"_L1;
}

void LMStudioPlugin::askToAssistant(const QString &msg)
{
    Q_UNUSED(msg)
}

void LMStudioPlugin::sendToAssistant(const SendToAssistantInfo &info)
{
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
}

QString LMStudioPlugin::displayName() const
{
    return mLMStudioSettings->displayName();
}

void LMStudioPlugin::setDisplayName(const QString &newName)
{
    mLMStudioSettings->setDisplayName(newName);
}

QString LMStudioPlugin::currentModel() const
{
    if (mLMStudioSettings->currentModel().isEmpty()) {
        return fallBackModel();
    }
    return mLMStudioSettings->currentModel();
}

void LMStudioPlugin::setCurrentModel(const QString &m)
{
    mLMStudioSettings->setCurrentModel(m);
    Q_EMIT configChanged();
    Q_EMIT currentModelChanged();
}

bool LMStudioPlugin::hasVisionSupport() const
{
    return mLMStudioManager->hasVisionSupport(currentModel());
}

bool LMStudioPlugin::hasToolsSupport() const
{
    return mLMStudioManager->hasToolsSupport(currentModel());
}

bool LMStudioPlugin::hasOcrSupport() const
{
    return mLMStudioManager->hasOcrSupport(currentModel());
}

bool LMStudioPlugin::hasAudioSupport() const
{
    return mLMStudioManager->hasAudioSupport(currentModel());
}

bool LMStudioPlugin::hasThinkSupport() const
{
    return mLMStudioSettings->thoughtProcessing() && mLMStudioManager->hasThinkSupport(currentModel());
}

QString LMStudioPlugin::shareNamePrompt() const
{
    // return LMStudioCommonModelUtils::generateUserPrompt(mLMStudioSettings->shareNameType());
    return QString{};
}

QString LMStudioPlugin::passwordServiceName() const
{
    return QStringLiteral("LMStudioPluginAutoGenerateText");
}

TextAutoGenerateText::TextAutoGenerateTextPlugin::ActivateInstanceActionInfo LMStudioPlugin::activateInstanceAction()
{
    if (mCurrentAction) {
        delete mCurrentAction;
        mCurrentAction = nullptr;
    }
#if 1
    TextAutoGenerateText::TextAutoGenerateTextPlugin::ActivateInstanceActionInfo activateInstanceInfo;
    const QString lmsPath = TextAddonsWidgets::ExecutableUtils::findExecutable(u"lms"_s);
    if (lmsPath.isEmpty()) {
#if !defined(Q_OS_WIN) && !defined(Q_OS_MACOS)
        activateInstanceInfo.text = i18n("LMStudio not found on system. Ask to your administrator system to install it.");
#else
        activateInstanceInfo.text = i18n("LMStudio not found on system. Please install it.");
        auto downloadLMSAction = new QAction(i18nc("@action", "Download LMStudio"), this);
        downloadLMSAction->setObjectName(u"downloadLMSAction"_s);
        connect(downloadLMSAction, &QAction::triggered, this, &LMStudioPlugin::slotDownloadLMStudio);
        mCurrentAction = downloadOllamaAction;
#endif
    } else {
        auto startLMSAction = new QAction(i18nc("@action", "Start LMStudio"), this);
        startLMSAction->setObjectName(u"startLMSAction"_s);
        connect(startLMSAction, &QAction::triggered, this, &LMStudioPlugin::slotLMStudioRequested);
        mCurrentAction = startLMSAction;
    }
    activateInstanceInfo.action = mCurrentAction;
    return activateInstanceInfo;
#else
    return {};
#endif
}

void LMStudioPlugin::slotDownloadLMStudio()
{
#ifdef Q_OS_WIN
    QDesktopServices::openUrl(QUrl(u"https://lmstudio.ai/download?os=win32"_s));
#endif
#ifdef Q_OS_MACOS
    QDesktopServices::openUrl(QUrl(u"https://lmstudio.ai/download?os=darwin"_s));
#endif
}

void LMStudioPlugin::slotLMStudioRequested()
{
#if 0
    mLMStudioManager->startLMStudio();
#endif
}

void LMStudioPlugin::loadApiKey()
{
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
}

void LMStudioPlugin::removeApiKey()
{
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
}

#include "moc_lmstudioplugin.cpp"
