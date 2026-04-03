/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolclient.h"
#include "common/mcpprotocolplugininterface.h"

using namespace McpProtocol;
using namespace Qt::Literals::StringLiterals;
McpProtocolClient::McpProtocolClient(McpProtocolPlugin::ProtocolType protocolType, QObject *parent)
    : QObject{parent}
    , mProtocolType(protocolType)
{
    initialize();
}

McpProtocolClient::~McpProtocolClient() = default;

void McpProtocolClient::initialize()
{
    if (mPlugin) {
        mPluginInterface = mPlugin->createInterface(mProtocolType, this);
        connect(mPluginInterface, &McpProtocolPluginInterface::error, this, &McpProtocolClient::error);
        connect(mPluginInterface, &McpProtocolPluginInterface::received, this, &McpProtocolClient::received);
        connect(mPluginInterface, &McpProtocolPluginInterface::started, this, &McpProtocolClient::started);
    }
}

void McpProtocolClient::start()
{
    if (mPluginInterface) {
        mPluginInterface->start();
    }
    // TODO
}

McpProtocolPlugin::ProtocolType McpProtocolClient::protocolType() const
{
    return mProtocolType;
}

#include "moc_mcpprotocolclient.cpp"
