/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserver.h"
#include "common/mcpprotocolplugininterface.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <KPluginFactory>
#include <KPluginMetaData>

using namespace McpProtocol;
using namespace Qt::Literals::StringLiterals;

McpProtocolServer::McpProtocolServer(McpProtocolPlugin::ProtocolType protocolType, QObject *parent)
    : QObject{parent}
    , mProtocolType(protocolType)
{
    loadPlugin();
}

McpProtocolServer::~McpProtocolServer() = default;

void McpProtocolServer::loadPlugin()
{
    const KPluginMetaData serverPlugin(u"kf6/textautogeneratetext/mcpprotocol/autogeneratetext_mcpprotocolserverplugin"_s);
    const auto result = KPluginFactory::instantiatePlugin<McpProtocol::McpProtocolPlugin>(serverPlugin, this);
    if (result) {
        mPlugin = result.plugin;
    }
    initialize();
}

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

void McpProtocolServer::setSettings(McpProtocolSettings *settings)
{
    if (mPluginInterface) {
        mPluginInterface->setSettings(settings);
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "mPluginInterface is nullptr. It's a bug";
    }
}

bool McpProtocolServer::canStart() const
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

void McpProtocolServer::start()
{
    if (canStart()) {
        mPluginInterface->start();
    }
}

#include "moc_mcpprotocolserver.cpp"
