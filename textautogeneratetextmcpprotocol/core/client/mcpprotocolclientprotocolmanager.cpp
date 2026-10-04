/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "mcpprotocolclientprotocolmanager.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include "textautogeneratetextmcpprotocolcore_version.h"

#include <QCoreApplication>
#include <QJsonObject>
#include <QTimer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCancelledNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClient>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientCapabilities>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCErrorResponse>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCResultResponse>
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
    , mTimeoutTimer(new QTimer(this))
{
    connect(mTimeoutTimer, &QTimer::timeout, this, &McpProtocolClientProtocolManager::checkTimeouts);
}

McpProtocolClientProtocolManager::~McpProtocolClientProtocolManager() = default;

qint64 McpProtocolClientProtocolManager::requestId()
{
    mRequestIdentifier++;
    return mRequestIdentifier;
}

qint64 McpProtocolClientProtocolManager::executeAction(MethodType type)
{
    if (!mClient) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Client was not initialized";
        return -1;
    }
    // Only ping is allowed before the server answered the initialize request
    if (!mInitialized && type != MethodType::Ping) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Initialization not finished. Can't execute" << type;
        return -1;
    }
    if (!serverSupports(type)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Server doesn't support" << type;
        return -1;
    }
    switch (type) {
    case MethodType::Ping:
        return ping();
    case MethodType::ListTools:
        return listTools();
    case MethodType::ListPrompts:
        return listPrompts();
    case MethodType::ResourceTemplates:
        return resourceTemplates();
    case MethodType::CallTool:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Use callTool() to call a tool.";
        break;
    case MethodType::Initialize:
    case MethodType::ServerRequest:
    case MethodType::ServerNotification:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "IT's a bug. MethodType" << type << "can't be executed by client.";
        break;
    case MethodType::Unknown:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "IT's a bug. MethodType::Unknown must not used.";
        break;
    }
    return -1;
}

qint64 McpProtocolClientProtocolManager::sendRequest(const QJsonObject &request, qint64 identifier, MethodType type)
{
    // Register before sending: transport can answer synchronously
    mPendingRequests.insert(identifier, {type, QDeadlineTimer(mRequestTimeout)});
    if (!mTimeoutTimer->isActive()) {
        mTimeoutTimer->start(std::min(mRequestTimeout, std::chrono::milliseconds(1000)));
    }
    mClient->request(request);
    return identifier;
}

void McpProtocolClientProtocolManager::checkTimeouts()
{
    QList<qint64> expired;
    for (auto it = mPendingRequests.cbegin(); it != mPendingRequests.cend(); ++it) {
        if (it->deadline.hasExpired()) {
            expired.append(it.key());
        }
    }
    for (const qint64 identifier : std::as_const(expired)) {
        const MethodType type = mPendingRequests.take(identifier).type;
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Request timed out:" << identifier << type;
        if (type == MethodType::Initialize) {
            // Initialize request must not be cancelled: stop client
            Q_EMIT error(u"Initialize request timed out"_s);
            mClient->stop();
            return;
        }
        sendCancelledNotification(identifier, u"Request timed out"_s);
        // Let caller know that request failed
        McpProtocolError mcpError;
        mcpError.setCode(-32001); // Request timeout
        mcpError.setMessage(u"Request timed out"_s);
        McpProtocolJSONRPCErrorResponse response;
        response.setId(McpProtocolUtils::RequestId(identifier));
        response.setError(std::move(mcpError));
        Q_EMIT received(McpProtocolJSONRPCErrorResponse::toJson(response), type);
    }
    if (mPendingRequests.isEmpty()) {
        mTimeoutTimer->stop();
    }
}

bool McpProtocolClientProtocolManager::serverSupports(MethodType type) const
{
    // Server must declare capability before we use it
    const McpProtocolServerCapabilities capabilities = mInitializeResult.capabilities();
    switch (type) {
    case MethodType::ListTools:
    case MethodType::CallTool:
        return capabilities.tools().has_value();
    case MethodType::ListPrompts:
        return capabilities.prompts().has_value();
    case MethodType::ResourceTemplates:
        return capabilities.resources().has_value();
    case MethodType::Unknown:
    case MethodType::Ping:
    case MethodType::Initialize:
    case MethodType::ServerRequest:
    case MethodType::ServerNotification:
        break;
    }
    return true;
}

qint64 McpProtocolClientProtocolManager::callTool(const QString &name, const QJsonObject &arguments)
{
    if (!mClient || !mInitialized) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Initialization not finished. Can't call tool" << name;
        return -1;
    }
    if (!serverSupports(MethodType::CallTool)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Server doesn't support tools. Can't call tool" << name;
        return -1;
    }
    if (name.isEmpty()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Tool name is empty";
        return -1;
    }
    McpProtocolCallToolRequestParams params;
    params.setName(name);
    if (!arguments.isEmpty()) {
        QMap<QString, QJsonValue> map;
        for (auto it = arguments.constBegin(); it != arguments.constEnd(); ++it) {
            map.insert(it.key(), it.value());
        }
        params.setArguments(std::move(map));
    }
    McpProtocolCallToolRequest request;
    const qint64 identifier = requestId();
    request.setId(identifier);
    request.setParams(std::move(params));
    return sendRequest(McpProtocolCallToolRequest::toJson(request), identifier, MethodType::CallTool);
}

void McpProtocolClientProtocolManager::cancelRequest(qint64 requestId, const QString &reason)
{
    const auto it = mPendingRequests.constFind(requestId);
    if (it == mPendingRequests.cend()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Request not found:" << requestId;
        return;
    }
    if (it->type == MethodType::Initialize) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Initialize request can't be cancelled";
        return;
    }
    // Response received later will be ignored
    mPendingRequests.erase(it);
    sendCancelledNotification(requestId, reason);
}

void McpProtocolClientProtocolManager::sendCancelledNotification(qint64 identifier, const QString &reason)
{
    McpProtocolCancelledNotificationParams params;
    params.setRequestId(McpProtocolUtils::RequestId(identifier));
    if (!reason.isEmpty()) {
        params.setReason(reason);
    }
    McpProtocolCancelledNotification notification;
    notification.setParams(std::move(params));
    mClient->notify(McpProtocolCancelledNotification::toJson(notification));
}

std::chrono::milliseconds McpProtocolClientProtocolManager::requestTimeout() const
{
    return mRequestTimeout;
}

void McpProtocolClientProtocolManager::setRequestTimeout(std::chrono::milliseconds timeout)
{
    mRequestTimeout = timeout;
}

McpProtocolClientProtocolManager::MethodType McpProtocolClientProtocolManager::checkMethodType(const QJsonObject &obj)
{
    if (obj.contains("method"_L1)) {
        return obj.contains("id"_L1) ? MethodType::ServerRequest : MethodType::ServerNotification;
    }
    if (obj.contains("result"_L1) || obj.contains("error"_L1)) {
        const McpProtocolUtils::RequestId id = McpProtocolUtils::requestIdFromJson(obj.value("id"_L1));
        if (const qint64 *identifier = std::get_if<qint64>(&id)) {
            if (const auto it = mPendingRequests.constFind(*identifier); it != mPendingRequests.cend()) {
                const MethodType type = it->type;
                mPendingRequests.erase(it);
                return type;
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

void McpProtocolClientProtocolManager::stopClient()
{
    if (!mClient || !mClientStarted) {
        return;
    }
    // State is reset in slotFinished
    mClient->stop();
}

bool McpProtocolClientProtocolManager::isInitialized() const
{
    return mInitialized;
}

McpProtocolInitializeResult McpProtocolClientProtocolManager::initializeResult() const
{
    return mInitializeResult;
}

void McpProtocolClientProtocolManager::initializeClient()
{
    if (mClientStarted) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Client already initialized";
        return;
    }
    if (!mServer.isValid()) {
        // Don't create a client which can't start
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid server:" << mServer;
        Q_EMIT error(u"Invalid server settings"_s);
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
            initialize();
            Q_EMIT started();
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
    mInitialized = false;
    mInitializeResult = {};
    mPendingRequests.clear();
    mTimeoutTimer->stop();
    Q_EMIT finished();
}

void McpProtocolClientProtocolManager::slotReceived(const QJsonObject &obj)
{
    qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " receive " << obj;
    const MethodType type = checkMethodType(obj);
    if (type == MethodType::Initialize) {
        initializeResponseReceived(obj);
    } else if (type == MethodType::ServerRequest) {
        answerServerRequest(obj);
    }
    Q_EMIT received(obj, type);
}

void McpProtocolClientProtocolManager::answerServerRequest(const QJsonObject &obj)
{
    const McpProtocolUtils::RequestId id = McpProtocolUtils::requestIdFromJson(obj.value("id"_L1));
    const QString method = obj.value("method"_L1).toString();
    if (method == QLatin1StringView(McpProtocolPingRequest::type())) {
        McpProtocolJSONRPCResultResponse response;
        response.setId(id);
        mClient->respond(McpProtocolJSONRPCResultResponse::toJson(response));
        return;
    }
    // We don't support sampling/roots/elicitation yet
    qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Unsupported server request:" << method;
    McpProtocolError mcpError;
    mcpError.setCode(-32601); // JSON-RPC "Method not found"
    mcpError.setMessage(u"Method not found: %1"_s.arg(method));
    McpProtocolJSONRPCErrorResponse response;
    response.setId(id);
    response.setError(std::move(mcpError));
    mClient->respond(McpProtocolJSONRPCErrorResponse::toJson(response));
}

void McpProtocolClientProtocolManager::initializeResponseReceived(const QJsonObject &obj)
{
    if (const QJsonValue resultValue = obj.value("result"_L1); resultValue.isObject()) {
        const McpProtocolInitializeResult result = McpProtocolInitializeResult::fromJson(resultValue.toObject());
        if (McpProtocolUtils::convertProtocolVersionFromString(result.protocolVersion()) == McpProtocolUtils::ProtocolVersion::Unknown) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Unsupported protocol version:" << result.protocolVersion();
            Q_EMIT error(u"Unsupported protocol version: %1"_s.arg(result.protocolVersion()));
            return;
        }
        mInitializeResult = result;
        mInitialized = true;
        sendInitializedNotification();
        Q_EMIT initialized();
    } else {
        const McpProtocolJSONRPCErrorResponse response = McpProtocolJSONRPCErrorResponse::fromJson(obj);
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Initialize failed:" << response.error().message();
        Q_EMIT error(response.error().message());
    }
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
        TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ProtocolVersion::V2025_11_25));

    auto clientInfo = params.clientInfo();
    clientInfo.setName(mClientName.isEmpty() ? QCoreApplication::applicationName() : mClientName);
    clientInfo.setVersion(QStringLiteral(TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_VERSION_STRING));
    params.setClientInfo(clientInfo);

    initRequest.setParams(std::move(params));
    const qint64 identifier = requestId();
    initRequest.setId(identifier);
    qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " initRequest " << initRequest;
    sendRequest(TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeRequest::toJson(initRequest), identifier, MethodType::Initialize);
}

qint64 McpProtocolClientProtocolManager::ping()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest pingRequest;
    const qint64 identifier = requestId();
    pingRequest.setId(identifier);
    return sendRequest(TextAutoGenerateTextMcpProtocolCore::McpProtocolPingRequest::toJson(pingRequest), identifier, MethodType::Ping);
}

qint64 McpProtocolClientProtocolManager::listTools()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsRequest listToolsRequest;
    const qint64 identifier = requestId();
    listToolsRequest.setId(identifier);
    return sendRequest(TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsRequest::toJson(listToolsRequest), identifier, MethodType::ListTools);
}

qint64 McpProtocolClientProtocolManager::listPrompts()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsRequest listPromptsRequest;
    const qint64 identifier = requestId();
    listPromptsRequest.setId(identifier);
    return sendRequest(TextAutoGenerateTextMcpProtocolCore::McpProtocolListPromptsRequest::toJson(listPromptsRequest), identifier, MethodType::ListPrompts);
}

qint64 McpProtocolClientProtocolManager::resourceTemplates()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesRequest resourceTemplatesRequest;
    const qint64 identifier = requestId();
    resourceTemplatesRequest.setId(identifier);
    return sendRequest(TextAutoGenerateTextMcpProtocolCore::McpProtocolListResourceTemplatesRequest::toJson(resourceTemplatesRequest),
                       identifier,
                       MethodType::ResourceTemplates);
}

#include "moc_mcpprotocolclientprotocolmanager.cpp"
