/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralplugin.h"
#include "autogeneratetext_mistral_debug.h"
#include "mistralmanager.h"
#include "mistralutils.h"
#include <qt6keychain/keychain.h>

using namespace Qt::Literals::StringLiterals;
MistralPlugin::MistralPlugin(MistralManager *manager, QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{parent}
    , mMistralManager(manager)
{
}

MistralPlugin::~MistralPlugin() = default;

bool MistralPlugin::loadSettings()
{
    auto readJob = new QKeychain::ReadPasswordJob(MistralUtils::mistralGroupName(), this);
    connect(readJob, &QKeychain::Job::finished, this, &MistralPlugin::slotApiKeyRead);
    readJob->setKey(MistralUtils::apiGroupName());
    readJob->start();
    return true;
}

void MistralPlugin::clear()
{
}

void MistralPlugin::setPrompt(const QString &text)
{
    // TODO
}

QString MistralPlugin::engineName() const
{
    return name();
}

void MistralPlugin::sendToAssistant(const SendToAssistantInfo &info)
{
    // TODO
}

void MistralPlugin::askToAssistant(const QString &msg)
{
    // TODO
}

void MistralPlugin::cancelRequest(const QByteArray &uuid)
{
    // TODO
}

void MistralPlugin::slotApiKeyRead(QKeychain::Job *baseJob)
{
    auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
    Q_ASSERT(job);
    if (!job->error()) {
        mMistralManager->setApiKey(job->textData());
    } else {
        qCWarning(AUTOGENERATETEXT_MISTRAL_LOG) << "We have an error during reading password " << job->errorString();
    }
}

QString MistralPlugin::name()
{
    return "mistral"_L1;
}

#include "moc_mistralplugin.cpp"
