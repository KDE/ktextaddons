/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericnetworkplugin.h"
#include "genericnetworkconfiguredialog.h"
#include "genericnetworkmanager.h"
#include "genericnetworkserverinfo.h"
#include <qt6keychain/keychain.h>

using namespace Qt::Literals::StringLiterals;
GenericNetworkPlugin::GenericNetworkPlugin(const QString &serverIdentifier, TextAutoGenerateText::TextAutoGenerateManager *manager, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{manager, parent}
    , mGenericManager(new GenericNetworkManager(this))
{
    const GenericNetworkServerInfo info;
    mGenericManager->setPluginNetworkType(info.pluginNetworkTypeFromString(serverIdentifier));
}

GenericNetworkPlugin::~GenericNetworkPlugin() = default;

void GenericNetworkPlugin::load(const KConfigGroup &config)
{
}

void GenericNetworkPlugin::save(KConfigGroup &config)
{
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

QString GenericNetworkPlugin::name()
{
    return "mistral"_L1;
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

#include "moc_genericnetworkplugin.cpp"
