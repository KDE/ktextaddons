/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpservermanager.h"
#include "common/mcpprotocolutils.h"
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

void McpServerManager::loadServers()
{
    auto config = KSharedConfig::openConfig(McpProtocolUtils::serverConfigFileName());
    const QStringList mcpServerList = McpProtocolUtils::mcpServerList(config);
    if (mcpServerList.isEmpty()) {
        return; // nothing to be done...
    }

    QList<McpServer> mcpServers;
    for (const auto &group : mcpServerList) {
        const KConfigGroup configGroup(config, group);
        McpServer server;
        server.load(configGroup);
        if (server.isValid()) {
            mcpServers.append(server);
        }
    }
    mMcpServerModel->setMcpServers(mcpServers);
}

void McpServerManager::saveServers()
{
    auto config = KSharedConfig::openConfig(McpProtocolUtils::serverConfigFileName());
    const auto instanceList = McpProtocolUtils::mcpServerList(config);
    for (const auto &group : instanceList) {
        config->deleteGroup(group);
    }

    const QList<McpServer> serverLst = mMcpServerModel->mcpServers();
    for (int i = 0; i < serverLst.count(); ++i) {
        auto server = serverLst.at(i);
        KConfigGroup group = config->group(u"Mcp Server #%1"_s.arg(i));
        server.save(group);
    }
    config->sync();
}

#include "moc_mcpservermanager.cpp"
