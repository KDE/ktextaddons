/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericnetworkplugin.h"
#include "genericnetworkconfiguredialog.h"
#include "genericnetworkmanager.h"
#include "genericnetworkserverinfo.h"
#include "genericnetworksettings.h"
#include <qt6keychain/keychain.h>

using namespace Qt::Literals::StringLiterals;
GenericNetworkPlugin::GenericNetworkPlugin(const QString &serverIdentifier, TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, parent}
    , mSettings(new GenericNetworkSettings)
    , mGenericManager(new GenericNetworkManager(mSettings, this))
{
    const GenericNetworkServerInfo info;
    mGenericManager->setPluginNetworkType(info.pluginNetworkTypeFromString(serverIdentifier));
    connect(mGenericManager,
            &GenericNetworkManager::modelsLoadDone,
            this,
            [this](const TextAutoGenerateText::TextAutoGenerateManagerBase::ModelsInfo &modelinfo) {
                if (modelinfo.hasError) {
                    setReady(false);
                    Q_EMIT errorOccurred(modelinfo.errorOccured);
                    mModels.clear();
                } else {
                    setReady(true);
                    mModels = modelinfo.models;
                }
            });
    mGenericManager->loadModels();
}

GenericNetworkPlugin::~GenericNetworkPlugin()
{
    delete mSettings;
}

void GenericNetworkPlugin::load(const KConfigGroup &config)
{
    mSettings->setDisplayName(config.readEntry(u"Name"_s));
    mSettings->setCurrentModel(config.readEntry(u"CurrentModel"_s));
    mSettings->setTemperature(config.readEntry(u"Temperature"_s, 0.0));
    mSettings->setMaxTokens(config.readEntry(u"MaxToken"_s, 2048));
}

void GenericNetworkPlugin::save(KConfigGroup &config)
{
    config.writeEntry(u"Name"_s, mSettings->displayName());
    config.writeEntry(u"CurrentModel"_s, mSettings->currentModel());
    config.writeEntry(u"MaxToken"_s, mSettings->maxTokens());
    config.writeEntry(u"Temperature"_s, mSettings->temperature());
}

QStringList GenericNetworkPlugin::models() const
{
    return mModels;
}

void GenericNetworkPlugin::clear()
{
}

void GenericNetworkPlugin::setPrompt(const QString &text)
{
    // TODO
}

QString GenericNetworkPlugin::engineName() const
{
    return name();
}

void GenericNetworkPlugin::sendToAssistant(const SendToAssistantInfo &info)
{
    // TODO
}

void GenericNetworkPlugin::askToAssistant(const QString &msg)
{
    // TODO
}

void GenericNetworkPlugin::cancelRequest(const QByteArray &uuid)
{
    // TODO
}

void GenericNetworkPlugin::slotApiKeyRead(QKeychain::Job *baseJob)
{
    /*
    auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
    Q_ASSERT(job);
    if (!job->error()) {
        mMistralManager->setApiKey(job->textData());
    } else {
        qCWarning(AUTOGENERATETEXT_MISTRAL_LOG) << "We have an error during reading password " << job->errorString();
    }
    */
}

QString GenericNetworkPlugin::name() const
{
    const GenericNetworkServerInfo info;
    return info.pluginName(mGenericManager->pluginNetworkType());
}

QString GenericNetworkPlugin::translatedPluginName() const
{
    return mGenericManager->translatedPluginName();
}

void GenericNetworkPlugin::showConfigureDialog(QWidget *parentWidget)
{
    GenericNetworkConfigureDialog d(mGenericManager, parentWidget);
    if (d.exec()) {
        Q_EMIT configChanged();
    }
}

QString GenericNetworkPlugin::displayName() const
{
    return mSettings->displayName();
}

void GenericNetworkPlugin::setDisplayName(const QString &newName)
{
    mSettings->setDisplayName(newName);
}

QString GenericNetworkPlugin::currentModel() const
{
    return mSettings->currentModel();
}

#include "moc_genericnetworkplugin.cpp"
