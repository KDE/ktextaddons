/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolclient.h"
#include "common/mcpprotocolplugininterface.h"
#include "textautogeneratetextmcpprotocol_debug.h"

using namespace McpProtocol;
using namespace Qt::Literals::StringLiterals;
McpProtocolClient::McpProtocolClient(McpProtocolPlugin::ProtocolType protocolType, QObject *parent)
    : QObject{parent}
    , mProtocolType(protocolType)
{
    loadPlugin();
    initialize();
}

McpProtocolClient::~McpProtocolClient() = default;

void McpProtocolClient::loadPlugin()
{
    // TODO load plugins !
}

void McpProtocolClient::initialize()
{
    if (mPlugin) {
        mPluginInterface = mPlugin->createInterface(mProtocolType, this);
        if (mPluginInterface) {
            connect(mPluginInterface, &McpProtocolPluginInterface::error, this, &McpProtocolClient::error);
            connect(mPluginInterface, &McpProtocolPluginInterface::received, this, &McpProtocolClient::received);
            connect(mPluginInterface, &McpProtocolPluginInterface::started, this, &McpProtocolClient::started);
        }
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "plugin not found for " << mProtocolType;
    }
}

void McpProtocolClient::setSettings(McpProtocolSettings *settings)
{
    if (mPluginInterface) {
        mPluginInterface->setSettings(settings);
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "mPluginInterface is nullptr. It's a bug";
    }
}

bool McpProtocolClient::canStart() const
{
    if (mPluginInterface) {
        const bool result = mPluginInterface->canStart();
        if (!result) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Impossible to start client. Missing McpProtocolSettings. It's a bug";
        }
        return result;
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Impossible to start client. mPluginInterface is null. It's a bug";
    return false;
}

void McpProtocolClient::start()
{
    if (canStart()) {
        mPluginInterface->start();
    }
}

McpProtocolPlugin::ProtocolType McpProtocolClient::protocolType() const
{
    return mProtocolType;
}

#include "moc_mcpprotocolclient.cpp"
