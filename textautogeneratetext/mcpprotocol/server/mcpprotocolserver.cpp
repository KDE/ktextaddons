/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserver.h"
#include "common/mcpprotocolplugininterface.h"
#include "textautogeneratetextmcpprotocol_debug.h"

using namespace McpProtocol;
using namespace Qt::Literals::StringLiterals;

McpProtocolServer::McpProtocolServer(McpProtocolPlugin::ProtocolType protocolType, QObject *parent)
    : QObject{parent}
    , mProtocolType(protocolType)
{
    initialize();
    // TODO load plugins !
}

McpProtocolServer::~McpProtocolServer() = default;

void McpProtocolServer::initialize()
{
    if (mPlugin) {
        mPluginInterface = mPlugin->createInterface(mProtocolType, this);
        if (mPluginInterface) {
            connect(mPluginInterface, &McpProtocolPluginInterface::error, this, &McpProtocolServer::error);
            connect(mPluginInterface, &McpProtocolPluginInterface::received, this, &McpProtocolServer::received);
            connect(mPluginInterface, &McpProtocolPluginInterface::started, this, &McpProtocolServer::started);
        }
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "plugin not found for " << mProtocolType;
    }
}

#include "moc_mcpprotocolserver.cpp"
