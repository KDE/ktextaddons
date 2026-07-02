/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "plugincommonsaveloadpassword.h"
#include "autogeneratetext_plugincommon_debug.h"
#include <qt6keychain/keychain.h>
using namespace Qt::Literals::StringLiterals;

PluginCommonSaveLoadPassword::PluginCommonSaveLoadPassword(QObject *parent)
    : QObject(parent)
{
}

PluginCommonSaveLoadPassword::~PluginCommonSaveLoadPassword() = default;

void PluginCommonSaveLoadPassword::writePassword(const QString &passwordServiceName, const QByteArray &instanceUuid, const QString &apiKey)
{
    auto writeJob = new QKeychain::WritePasswordJob(passwordServiceName);
    connect(writeJob, &QKeychain::Job::finished, this, [this](QKeychain::Job *baseJob) {
        if (baseJob->error() != QKeychain::Error::NoError) {
            qCWarning(AUTOGENERATETEXT_PLUGINCOMMON_LOG) << "Error writing password using QKeychain:" << baseJob->errorString();
        }
        deleteLater();
    });
    writeJob->setKey(QString::fromLatin1(instanceUuid));
    writeJob->setTextData(apiKey);
    writeJob->start();
}

void PluginCommonSaveLoadPassword::loadApiKey(const QString &passwordServiceName, const QByteArray &instanceUuid)
{
    auto readJob = new QKeychain::ReadPasswordJob(passwordServiceName);
    connect(readJob, &QKeychain::Job::finished, this, [this](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error()) {
            qCWarning(AUTOGENERATETEXT_PLUGINCOMMON_LOG) << "We have an error during reading password " << job->errorString();
        } else {
            Q_EMIT loadApiKeyDone(job->textData());
        }
        deleteLater();
    });
    readJob->setKey(QString::fromLatin1(instanceUuid));
    readJob->start();
}

void PluginCommonSaveLoadPassword::removeApiKey(const QString &passwordServiceName, const QByteArray &instanceUuid)
{
    auto deleteJob = new QKeychain::DeletePasswordJob(passwordServiceName);
    deleteJob->setKey(QString::fromLatin1(instanceUuid));
    connect(deleteJob, &QKeychain::Job::finished, this, [this](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::DeletePasswordJob *>(baseJob);
        if (!job) {
            qCWarning(AUTOGENERATETEXT_PLUGINCOMMON_LOG) << "Invalid job cast in removeApiKey";
            deleteLater();
            return;
        }
        if (job->error()) {
            qCWarning(AUTOGENERATETEXT_PLUGINCOMMON_LOG) << "We have an error during deleting password " << job->errorString();
        }
        deleteLater();
    });
    deleteJob->start();
}
