/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "genericnetworkplugin.h"
#include "genericnetworkconfiguredialog.h"
#include "genericnetworkmanager.h"
#include <qt6keychain/keychain.h>

using namespace Qt::Literals::StringLiterals;
GenericNetworkPlugin::GenericNetworkPlugin(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{parent}
    , mManager(new GenericNetworkManager(this))
{
}

GenericNetworkPlugin::~GenericNetworkPlugin() = default;

void GenericNetworkPlugin::load()
{
}

void GenericNetworkPlugin::save()
{
}

bool GenericNetworkPlugin::loadSettings()
{
    /*
    auto readJob = new QKeychain::ReadPasswordJob(MistralUtils::mistralGroupName(), this);
    connect(readJob, &QKeychain::Job::finished, this, &GenericNetworkPlugin::slotApiKeyRead);
    readJob->setKey(MistralUtils::apiGroupName());
    readJob->start();
    */
    return true;
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

void GenericNetworkPlugin::showConfigureDialog(QWidget *parentWidget)
{
    GenericNetworkConfigureDialog d(mManager, parentWidget);
    d.exec();
}

#include "moc_genericnetworkplugin.cpp"
