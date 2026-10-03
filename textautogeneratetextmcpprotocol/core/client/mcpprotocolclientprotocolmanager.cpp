/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "mcpprotocolclientprotocolmanager.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include "textautogeneratetextmcpprotocolcore_version.h"

#include <QJsonObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClient>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientCapabilities>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListPromptsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourceTemplatesRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListToolsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPingRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolClientProtocolManager::McpProtocolClientProtocolManager(const TextAutoGenerateTextMcpProtocolCore::McpServer &server, QObject *parent)
    : QObject{parent}
    , mServer(server)
{
}

McpProtocolClientProtocolManager::~McpProtocolClientProtocolManager() = default;

qint64 McpProtocolClientProtocolManager::requestId()
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
        resourceTemplates();
        break;
    case MethodType::Initialize:
        initialize();
        break;
    case MethodType::ServerRequest:
    case MethodType::ServerNotification:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "IT's a bug. MethodType" << type << "can't be executed by client.";
        break;
    case MethodType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "IT's a bug. MethodType::Unknown must not used.";
        break;
    }
}

McpProtocolClientProtocolManager::MethodType McpProtocolClientProtocolManager::checkMethodType(const QJsonObject &obj)
{
    if (obj.contains("method"_L1)) {
        return obj.contains("id"_L1) ? MethodType::ServerRequest : MethodType::ServerNotification;
    }
    if (obj.contains("result"_L1) || obj.contains("error"_L1)) {
        const McpProtocolUtils::RequestId id = McpProtocolUtils::requestIdFromJson(obj.value("id"_L1));
        if (const qint64 *identifier = std::get_if<qint64>(&id)) {
            if (mMapIdentifier.contains(*identifier)) {
                return mMapIdentifier.take(*identifier);
            }
        }
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Response received for an unknown request id:" << obj.value("id"_L1);
        return MethodType::Unknown;
    }
    qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid message received:" << obj;
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

void McpProtocolClientProtocolManager::initializeClient()
{
    if (mClientStarted) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Client already initialized";
        return;
    }
    if (!mClient) {
        mClient = new TextAutoGenerateTextMcpProtocolCore::McpProtocolClient(mServer.transportType(), this);
        connect(mClient, &TextAutoGenerateTextMcpProtocolCore::McpProtocolClient::error, this, [this](const QString &strError) {
            qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " ERROR " << strError;
            Q_EMIT error(strError);
        });
        connect(mClient, &TextAutoGenerateTextMcpProtocolCore::McpProtocolClient::received, this, &McpProtocolClientProtocolManager::slotReceived);
        connect(mClient, &TextAutoGenerateTextMcpProtocolCore::McpProtocolClient::finished, this, &McpProtocolClientProtocolManager::slotFinished);
        connect(mClient, &TextAutoGenerateTextMcpProtocolCore::McpProtocolClient::started, this, [this]() {
            qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " Started ! ";
            Q_EMIT started();
            initialize();
        });
    }
    mClient->setSettings(mServer.settings());
    if (!mClient->canStart()) {
        return;
    }
    mClientStarted = true;
    mClient->start();
}

void McpProtocolClientProtocolManager::slotFinished()
{
    qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " Finished ! ";
    mClientStarted = false;
    mMapIdentifier.clear();
    Q_EMIT finished();
}

void McpProtocolClientProtocolManager::slotReceived(const QJsonObject &obj)
{
    qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " receive " << obj;
    const MethodType type = checkMethodType(obj);
    if (type == MethodType::Initialize && obj.contains("result"_L1)) {
        sendInitializedNotification();
    }
    Q_EMIT received(obj, type);
}

void McpProtocolClientProtocolManager::sendInitializedNotification()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializedNotification notification;
    mClient->notify(TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializedNotification::toJson(notification));
}

void McpProtocolClientProtocolManager::initialize()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest initRequest;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequestParams params;
    params.setProtocolVersion(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionToString(
        TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_03_26));

    auto clientInfo = params.clientInfo();
    clientInfo.setName(mClientName);
    clientInfo.setVersion(QStringLiteral(TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_VERSION_STRING));
    params.setClientInfo(clientInfo);

    initRequest.setParams(std::move(params));
    const qint64 identifier = requestId();
    initRequest.setId(identifier);
    qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " initRequest " << initRequest;
    mClient->request(TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest::toJson(initRequest));
    mMapIdentifier.insert(identifier, MethodType::Initialize);
}

void McpProtocolClientProtocolManager::ping()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest pingRequest;
    const qint64 identifier = requestId();
    pingRequest.setId(identifier);
    mClient->request(TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest::toJson(pingRequest));
    mMapIdentifier.insert(identifier, MethodType::Ping);
}

void McpProtocolClientProtocolManager::listTools()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsRequest listToolsRequest;
    const qint64 identifier = requestId();
    listToolsRequest.setId(identifier);
    mClient->request(TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsRequest::toJson(listToolsRequest));
    mMapIdentifier.insert(identifier, MethodType::ListTools);
}

void McpProtocolClientProtocolManager::listPrompts()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsRequest listPromptsRequest;
    const qint64 identifier = requestId();
    listPromptsRequest.setId(identifier);
    mClient->request(TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsRequest::toJson(listPromptsRequest));
    mMapIdentifier.insert(identifier, MethodType::ListPrompts);
}

void McpProtocolClientProtocolManager::resourceTemplates()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesRequest resourceTemplatesRequest;
    const qint64 identifier = requestId();
    resourceTemplatesRequest.setId(identifier);
    mClient->request(TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesRequest::toJson(resourceTemplatesRequest));
    mMapIdentifier.insert(identifier, MethodType::ResourceTemplates);
}

#include "moc_mcpprotocolclientprotocolmanager.cpp"
