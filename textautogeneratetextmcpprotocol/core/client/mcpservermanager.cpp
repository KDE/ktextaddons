/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpservermanager.h"
#include "common/mcpprotocolcommonutils.h"
#include "models/mcpservermodel.h"
#include <KConfigGroup>
#include <KSharedConfig>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
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
    for (const auto &group : mcpServerList) {
        const KConfigGroup configGroup(config, group);
        McpServer server;
        server.load(configGroup);
        if (server.isValid()) {
            mcpServers.append(std::move(server));
        } else {
            mInvalidServerEntries.append(configGroup.entryMap());
        }
    }
    mMcpServerModel->setMcpServers(std::move(mcpServers));
    Q_EMIT serverLoaded();
}

void McpServerManager::saveServers()
{
    auto config = KSharedConfig::openConfig(serverConfigFileName());
    const auto instanceList = McpProtocolCommonUtils::mcpServerList(config);
    for (const auto &group : instanceList) {
        config->deleteGroup(group);
    }

    const QList<McpServer> serverLst = mMcpServerModel->mcpServers();
    for (int i = 0; i < serverLst.count(); ++i) {
        const auto &server = serverLst.at(i);
        KConfigGroup group = config->group(u"Mcp Server #%1"_s.arg(i));
        server.save(group);
    }
    for (int i = 0; i < mInvalidServerEntries.count(); ++i) {
        KConfigGroup group = config->group(u"Mcp Server #%1"_s.arg(serverLst.count() + i));
        const QMap<QString, QString> &entries = mInvalidServerEntries.at(i);
        for (auto it = entries.cbegin(); it != entries.cend(); ++it) {
            group.writeEntry(it.key(), it.value());
        }
    }
    config->sync();
}

#include "moc_mcpservermanager.cpp"
