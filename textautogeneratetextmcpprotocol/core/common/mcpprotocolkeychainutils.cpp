/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolkeychainutils.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <qt6keychain/keychain.h>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

static QString mcpAuthTokenServiceName()
{
    return u"ktextaddons-mcp"_s;
}

void McpProtocolKeychainUtils::writeAuthToken(const QByteArray &serverIdentifier, const QByteArray &token)
{
    auto writeJob = new QKeychain::WritePasswordJob(mcpAuthTokenServiceName());
    QObject::connect(writeJob, &QKeychain::Job::finished, writeJob, [](QKeychain::Job *baseJob) {
        if (baseJob->error() != QKeychain::Error::NoError) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Error writing auth token using QKeychain:" << baseJob->errorString();
        }
    });
    writeJob->setKey(QString::fromLatin1(serverIdentifier));
    writeJob->setBinaryData(token);
    writeJob->start();
}

void McpProtocolKeychainUtils::readAuthToken(const QByteArray &serverIdentifier, QObject *context, std::function<void(const QByteArray &)> callback)
{
    auto readJob = new QKeychain::ReadPasswordJob(mcpAuthTokenServiceName());
    QObject::connect(readJob, &QKeychain::Job::finished, context, [callback = std::move(callback)](QKeychain::Job *baseJob) {
        auto job = qobject_cast<QKeychain::ReadPasswordJob *>(baseJob);
        Q_ASSERT(job);
        if (job->error() != QKeychain::Error::NoError) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Error reading auth token using QKeychain:" << job->errorString();
            callback({});
            return;
        }
        callback(job->binaryData());
    });
    readJob->setKey(QString::fromLatin1(serverIdentifier));
    readJob->start();
}

void McpProtocolKeychainUtils::removeAuthToken(const QByteArray &serverIdentifier)
{
    auto deleteJob = new QKeychain::DeletePasswordJob(mcpAuthTokenServiceName());
    QObject::connect(deleteJob, &QKeychain::Job::finished, deleteJob, [](QKeychain::Job *baseJob) {
        if (baseJob->error() != QKeychain::Error::NoError && baseJob->error() != QKeychain::Error::EntryNotFound) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Error removing auth token using QKeychain:" << baseJob->errorString();
        }
    });
    deleteJob->setKey(QString::fromLatin1(serverIdentifier));
    deleteJob->start();
}
