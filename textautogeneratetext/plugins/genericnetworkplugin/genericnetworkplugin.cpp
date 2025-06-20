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
}

GenericNetworkPlugin::~GenericNetworkPlugin()
{
    delete mSettings;
}

void GenericNetworkPlugin::load(const KConfigGroup &config)
{
    mSettings->setDisplayName(config.readEntry(QStringLiteral("Name")));
    mSettings->setCurrentModel(config.readEntry(QStringLiteral("CurrentModel")));
}

void GenericNetworkPlugin::save(KConfigGroup &config)
{
    config.writeEntry(QStringLiteral("Name"), mSettings->displayName());
    config.writeEntry(QStringLiteral("CurrentModel"), mSettings->currentModel());
}

QStringList GenericNetworkPlugin::models() const
{
    return {};
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
