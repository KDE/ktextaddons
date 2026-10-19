/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpservermanager.h"
#include "common/mcpprotocolcommonutils.h"
#include "common/mcpprotocolkeychainutils.h"
#include "models/mcpservermodel.h"
#include <KConfigGroup>
#include <KSharedConfig>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

static QString hasAuthTokenKey()
{
    return u"HasAuthToken"_s;
}

McpServerManager::McpServerManager(QObject *parent)
    : QObject{parent}
    , mMcpServerModel(new McpServerModel(this))
{
}

McpServerManager::~McpServerManager() = default;

McpServerModel *McpServerManager::mcpServerModel() const
{
    return mMcpServerModel;
}

QString McpServerManager::serverConfigFileName() const
{
    return McpProtocolCommonUtils::serverConfigFileName();
}

void McpServerManager::loadServers()
{
    const auto config = KSharedConfig::openConfig(serverConfigFileName());
    const QStringList mcpServerList = McpProtocolCommonUtils::mcpServerList(config);
    QList<McpServer> mcpServers;
    mcpServers.reserve(mcpServerList.count());
    mInvalidServerEntries.clear();
    QList<QByteArray> authTokenIdentifiers;
    for (const auto &group : mcpServerList) {
        const KConfigGroup configGroup(config, group);
        McpServer server;
        server.load(configGroup);
        if (server.isValid()) {
            if (configGroup.readEntry(hasAuthTokenKey(), false)) {
                authTokenIdentifiers.append(server.identifier());
            }
            mcpServers.append(std::move(server));
        } else {
            mInvalidServerEntries.append(configGroup.entryMap());
        }
    }
    mMcpServerModel->setMcpServers(std::move(mcpServers));
    loadAuthTokens(authTokenIdentifiers);
}

void McpServerManager::loadAuthTokens(const QList<QByteArray> &identifiers)
{
    const int generation = ++mLoadGeneration;
    mStoredAuthTokens.clear();
    mPendingAuthTokenReads = QSet<QByteArray>(identifiers.cbegin(), identifiers.cend());
    if (mPendingAuthTokenReads.isEmpty()) {
        Q_EMIT serverLoaded();
        return;
    }
    for (const QByteArray &identifier : identifiers) {
        McpProtocolKeychainUtils::readAuthToken(identifier, this, [this, identifier, generation](const QByteArray &token) {
            // A new loadServers() was called in between
            if (generation != mLoadGeneration) {
                return;
            }
            if (!token.isEmpty()) {
                mStoredAuthTokens.insert(identifier, token);
                if (McpServer server = mMcpServerModel->mcpServer(identifier); !server.identifier().isEmpty()) {
                    McpProtocolSettings settings = server.settings();
                    settings.setAuthToken(token);
                    server.setSettings(std::move(settings));
                    mMcpServerModel->editMcpServer(server);
                }
            }
            mPendingAuthTokenReads.remove(identifier);
            if (mPendingAuthTokenReads.isEmpty()) {
                Q_EMIT serverLoaded();
            }
        });
    }
}

void McpServerManager::saveServers()
{
    auto config = KSharedConfig::openConfig(serverConfigFileName());
    const auto instanceList = McpProtocolCommonUtils::mcpServerList(config);
    QSet<QByteArray> previousAuthTokenIdentifiers;
    for (const auto &group : instanceList) {
        const KConfigGroup configGroup(config, group);
        if (configGroup.readEntry(hasAuthTokenKey(), false)) {
            previousAuthTokenIdentifiers.insert(configGroup.readEntry("Id", QByteArray()));
        }
        config->deleteGroup(group);
    }

    QSet<QByteArray> authTokenIdentifiers;
    const QList<McpServer> serverLst = mMcpServerModel->mcpServers();
    for (int i = 0; i < serverLst.count(); ++i) {
        const auto &server = serverLst.at(i);
        KConfigGroup group = config->group(u"Mcp Server #%1"_s.arg(i));
        server.save(group);
        const QByteArray identifier = server.identifier();
        if (const QByteArray token = server.settings().authToken(); !token.isEmpty()) {
            if (mStoredAuthTokens.value(identifier) != token) {
                McpProtocolKeychainUtils::writeAuthToken(identifier, token);
                mStoredAuthTokens.insert(identifier, token);
            }
            authTokenIdentifiers.insert(identifier);
        } else if (mPendingAuthTokenReads.contains(identifier)) {
            // Token not read from keychain yet: keep it
            authTokenIdentifiers.insert(identifier);
        }
        if (authTokenIdentifiers.contains(identifier)) {
            group.writeEntry(hasAuthTokenKey(), true);
        }
    }
    for (int i = 0; i < mInvalidServerEntries.count(); ++i) {
        KConfigGroup group = config->group(u"Mcp Server #%1"_s.arg(serverLst.count() + i));
        const QMap<QString, QString> &entries = mInvalidServerEntries.at(i);
        for (auto it = entries.cbegin(); it != entries.cend(); ++it) {
            group.writeEntry(it.key(), it.value());
        }
        if (group.readEntry(hasAuthTokenKey(), false)) {
            authTokenIdentifiers.insert(group.readEntry("Id", QByteArray()));
        }
    }
    config->sync();

    // Server removed or token cleared
    for (const QByteArray &identifier : std::as_const(previousAuthTokenIdentifiers)) {
        if (!identifier.isEmpty() && !authTokenIdentifiers.contains(identifier)) {
            McpProtocolKeychainUtils::removeAuthToken(identifier);
            mStoredAuthTokens.remove(identifier);
        }
    }
}

#include "moc_mcpservermanager.cpp"
