/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "mcpprotocolclientprotocolmanager.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"

#include <QJsonObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClient>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListPromptsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourceTemplatesRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListToolsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPingRequest>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolClientProtocolManager::McpProtocolClientProtocolManager(const TextAutoGenerateTextMcpProtocolCore::McpServer &server, QObject *parent)
    : QObject{parent}
    , mServer(server)
{
}

McpProtocolClientProtocolManager::~McpProtocolClientProtocolManager() = default;

int McpProtocolClientProtocolManager::requestId()
{
    mRequestIdentifier++;
    return mRequestIdentifier;
}

void McpProtocolClientProtocolManager::executeAction(MethodType type)
{
    if (!mClient) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Client was not initialized";
        return;
    }
    switch (type) {
    case MethodType::Ping:
        ping();
        break;
    case MethodType::ListTools:
        listTools();
        break;
    case MethodType::ListPrompts:
        listPrompts();
        break;
    case MethodType::ResourceTemplates:
        resouceTemplates();
        break;
    case MethodType::Initialize:
        // TODO ?
        break;
    case MethodType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "IT's a bug. MethodType::Unknown must not used.";
        break;
    }
}

McpProtocolClientProtocolManager::MethodType McpProtocolClientProtocolManager::checkMethodType(const QJsonObject &obj) const
{
    if (obj.contains("id"_L1)) {
        return mMapIdentifier.value(obj[u"id"_s].toInt(), MethodType::Unknown);
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolClientProtocolManager::MethodType::Unknown ! it's a bug";
    return MethodType::Unknown;
}

QString McpProtocolClientProtocolManager::clientName() const
{
    return mClientName;
}

void McpProtocolClientProtocolManager::setClientName(const QString &newClientName)
{
    mClientName = newClientName;
}

void McpProtocolClientProtocolManager::initializeClient(bool)
{
    if (!mClient) {
        mClient = new TextAutoGenerateTextMcpProtocolCore::McpProtocolClient(mServer.transportType(), this);
        connect(mClient, &TextAutoGenerateTextMcpProtocolCore::McpProtocolClient::error, this, [this](const QString &strError) {
            qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " ERROR " << strError;
            Q_EMIT error(strError);
        });
        connect(mClient, &TextAutoGenerateTextMcpProtocolCore::McpProtocolClient::received, this, [this](const QJsonObject &obj) {
            qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " receive " << obj;
            Q_EMIT received(obj, McpProtocolClientProtocolManager::checkMethodType(obj));
        });
        connect(mClient, &TextAutoGenerateTextMcpProtocolCore::McpProtocolClient::started, this, [this]() {
            qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " Started ! ";
            Q_EMIT started();
        });
    }
    mClient->setSettings(mServer.settings());
    mClient->start();
    initialize();
}

void McpProtocolClientProtocolManager::initialize()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest initRequest;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequestParams params;
    params.setProtocolVersion(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionToString(
        TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_03_26));

    auto clientInfo = params.clientInfo();
    clientInfo.setName(mClientName);
    clientInfo.setVersion(u"1"_s);
    params.setClientInfo(clientInfo);

    TextAutoGenerateTextMcpProtocolCore::McpProtocolClientCapabilities capabilities = params.capabilities();
    auto roots = capabilities.roots();
    roots.emplace(true);
    capabilities.setRoots(roots);

    params.setCapabilities(capabilities);
    initRequest.setParams(params);
    const int identifier = requestId();
    initRequest.setId(identifier);
    qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " initRequest " << initRequest;
    mClient->request(TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest::toJson(initRequest));
    mMapIdentifier.insert(identifier, MethodType::Initialize);
}

void McpProtocolClientProtocolManager::ping()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest pingRequest;
    const int identifier = requestId();
    pingRequest.setId(identifier);
    mClient->request(TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest::toJson(pingRequest));
    mMapIdentifier.insert(identifier, MethodType::Ping);
}

void McpProtocolClientProtocolManager::listTools()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsRequest listToolsRequest;
    const int identifier = requestId();
    listToolsRequest.setId(identifier);
    mClient->request(TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsRequest::toJson(listToolsRequest));
    mMapIdentifier.insert(identifier, MethodType::ListTools);
}

void McpProtocolClientProtocolManager::listPrompts()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsRequest listPromptsRequest;
    const int identifier = requestId();
    listPromptsRequest.setId(identifier);
    mClient->request(TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsRequest::toJson(listPromptsRequest));
    mMapIdentifier.insert(identifier, MethodType::ListPrompts);
}

void McpProtocolClientProtocolManager::resouceTemplates()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesRequest resourceTemplatesRequest;
    const int identifier = requestId();
    resourceTemplatesRequest.setId(identifier);
    mClient->request(TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesRequest::toJson(resourceTemplatesRequest));
    mMapIdentifier.insert(identifier, MethodType::ResourceTemplates);
}

#include "moc_mcpprotocolclientprotocolmanager.cpp"
