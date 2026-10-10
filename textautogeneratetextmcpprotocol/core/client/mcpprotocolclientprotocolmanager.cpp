/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#include "mcpprotocolclientprotocolmanager.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include "textautogeneratetextmcpprotocolcore_version.h"

#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCancelledNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClient>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientCapabilities>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolGetPromptRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCErrorResponse>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCResultResponse>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListPromptsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourceTemplatesRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourcesRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListToolsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPingRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptListChangedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResourceListChangedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolListChangedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
namespace
{
// Avoid infinite loop when server always returns a cursor
constexpr int maxPages = 100;
}
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
    case MethodType::GetPrompt:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Use getPrompt() to get a prompt.";
        break;
    case MethodType::ListTools:
    case MethodType::ListPrompts:
    case MethodType::ResourceTemplates:
    case MethodType::ListResources:
        return listRequest(type);
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

qint64 McpProtocolClientProtocolManager::getPrompt(const QString &name, const QMap<QString, QString> &arguments)
{
    if (!mClient || !mInitialized) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Initialization not finished. Can't get prompt" << name;
        return -1;
    }
    if (!serverSupports(MethodType::GetPrompt)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Server doesn't support prompts. Can't get prompt" << name;
        return -1;
    }
    if (name.isEmpty()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Prompt name is empty";
        return -1;
    }
    McpProtocolGetPromptRequestParams params;
    params.setName(name);
    if (!arguments.isEmpty()) {
        params.setArguments(arguments);
    }
    McpProtocolGetPromptRequest request;
    const qint64 identifier = requestId();
    request.setId(identifier);
    request.setParams(std::move(params));
    return sendRequest(McpProtocolGetPromptRequest::toJson(request), identifier, MethodType::GetPrompt);
}

qint64 McpProtocolClientProtocolManager::sendRequest(const QJsonObject &request, qint64 identifier, MethodType type)
{
    return sendRequest(request, identifier, type, PendingRequest());
}

qint64 McpProtocolClientProtocolManager::sendRequest(const QJsonObject &request, qint64 identifier, MethodType type, PendingRequest pending)
{
    pending.type = type;
    pending.deadline = QDeadlineTimer(mRequestTimeout);
    if (pending.originalId == 0) {
        pending.originalId = identifier;
    }
    const qint64 originalId = pending.originalId;
    // Register before sending: transport can answer synchronously
    mPendingRequests.insert(identifier, std::move(pending));
    if (!mTimeoutTimer->isActive()) {
        mTimeoutTimer->start(std::min(mRequestTimeout, std::chrono::milliseconds(1000)));
    }
    mClient->request(request);
    return originalId;
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
        const PendingRequest pending = mPendingRequests.take(identifier);
        const MethodType type = pending.type;
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
        response.setId(McpProtocolUtils::RequestId(pending.originalId));
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
    case MethodType::GetPrompt:
        return capabilities.prompts().has_value();
    case MethodType::ListResources:
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
    // List request can be in progress with another page request
    const auto it = std::find_if(mPendingRequests.cbegin(), mPendingRequests.cend(), [requestId](const PendingRequest &pending) {
        return pending.originalId == requestId;
    });
    if (it == mPendingRequests.cend()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Request not found:" << requestId;
        return;
    }
    if (it->type == MethodType::Initialize) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Initialize request can't be cancelled";
        return;
    }
    // Response received later will be ignored
    const qint64 identifier = it.key();
    mPendingRequests.erase(it);
    sendCancelledNotification(identifier, reason);
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

void McpProtocolClientProtocolManager::slotReceived(const QJsonObject &message)
{
    qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << " receive " << message;
    QJsonObject obj = message;
    MethodType type = MethodType::Unknown;
    if (obj.contains("method"_L1)) {
        type = obj.contains("id"_L1) ? MethodType::ServerRequest : MethodType::ServerNotification;
        if (type == MethodType::ServerRequest) {
            answerServerRequest(obj);
        }
    } else if (obj.contains("result"_L1) || obj.contains("error"_L1)) {
        const McpProtocolUtils::RequestId id = McpProtocolUtils::requestIdFromJson(obj.value("id"_L1));
        const qint64 *identifier = std::get_if<qint64>(&id);
        if (identifier && mPendingRequests.contains(*identifier)) {
            PendingRequest pending = mPendingRequests.take(*identifier);
            type = pending.type;
            if (type == MethodType::Initialize) {
                initializeResponseReceived(obj);
            } else if (!listKey(type).isEmpty() && !processPaginatedResponse(obj, pending)) {
                // Next page requested
                return;
            }
        } else {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Response received for an unknown request id:" << obj.value("id"_L1);
        }
    } else {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid message received:" << obj;
    }
    Q_EMIT received(obj, type);
    if (type == MethodType::ServerNotification) {
        serverNotificationReceived(obj);
    }
}

void McpProtocolClientProtocolManager::serverNotificationReceived(const QJsonObject &obj)
{
    const QString method = obj.value("method"_L1).toString();
    if (method == QLatin1StringView(McpProtocolToolListChangedNotification::type())) {
        Q_EMIT toolsListChanged();
    } else if (method == QLatin1StringView(McpProtocolPromptListChangedNotification::type())) {
        Q_EMIT promptsListChanged();
    } else if (method == QLatin1StringView(McpProtocolResourceListChangedNotification::type())) {
        Q_EMIT resourcesListChanged();
    }
}

QString McpProtocolClientProtocolManager::listKey(MethodType type)
{
    switch (type) {
    case MethodType::ListTools:
        return u"tools"_s;
    case MethodType::ListPrompts:
        return u"prompts"_s;
    case MethodType::ListResources:
        return u"resources"_s;
    case MethodType::ResourceTemplates:
        return u"resourceTemplates"_s;
    case MethodType::GetPrompt:
    case MethodType::Unknown:
    case MethodType::Ping:
    case MethodType::Initialize:
    case MethodType::ServerRequest:
    case MethodType::ServerNotification:
    case MethodType::CallTool:
        break;
    }
    return {};
}

bool McpProtocolClientProtocolManager::processPaginatedResponse(QJsonObject &obj, PendingRequest &pending)
{
    // Caller only knows first request id
    obj["id"_L1] = pending.originalId;
    if (!obj.contains("result"_L1)) {
        // Error
        return true;
    }
    QJsonObject result = obj.value("result"_L1).toObject();
    const QString key = listKey(pending.type);
    const QJsonArray page = result.value(key).toArray();
    for (const auto &item : page) {
        pending.items.append(item);
    }
    ++pending.pageCount;
    if (const QString nextCursor = result.value("nextCursor"_L1).toString(); !nextCursor.isEmpty()) {
        if (nextCursor == pending.cursor || pending.pageCount >= maxPages) {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Stop pagination of" << pending.type << "after" << pending.pageCount << "pages";
        } else {
            pending.cursor = nextCursor;
            listRequest(pending.type, std::move(pending));
            return false;
        }
    }
    // All pages are received: return all items in one response
    result[key] = pending.items;
    result.remove("nextCursor"_L1);
    obj["result"_L1] = result;
    return true;
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

qint64 McpProtocolClientProtocolManager::listRequest(MethodType type)
{
    return listRequest(type, PendingRequest());
}

qint64 McpProtocolClientProtocolManager::listRequest(MethodType type, PendingRequest pending)
{
    std::optional<McpProtocolPaginatedRequestParams> params;
    if (!pending.cursor.isEmpty()) {
        McpProtocolPaginatedRequestParams paginatedParams;
        paginatedParams.setCursor(pending.cursor);
        params = std::move(paginatedParams);
    }
    const qint64 identifier = requestId();
    QJsonObject request;
    switch (type) {
    case MethodType::ListTools: {
        McpProtocolListToolsRequest listToolsRequest;
        listToolsRequest.setId(identifier);
        listToolsRequest.setParams(std::move(params));
        request = McpProtocolListToolsRequest::toJson(listToolsRequest);
        break;
    }
    case MethodType::ListResources: {
        McpProtocolListResourcesRequest listResourcesRequest;
        listResourcesRequest.setId(identifier);
        listResourcesRequest.setParams(std::move(params));
        request = McpProtocolListResourcesRequest::toJson(listResourcesRequest);
        break;
    }
    case MethodType::ListPrompts: {
        McpProtocolListPromptsRequest listPromptsRequest;
        listPromptsRequest.setId(identifier);
        listPromptsRequest.setParams(std::move(params));
        request = McpProtocolListPromptsRequest::toJson(listPromptsRequest);
        break;
    }
    case MethodType::ResourceTemplates: {
        McpProtocolListResourceTemplatesRequest resourceTemplatesRequest;
        resourceTemplatesRequest.setId(identifier);
        resourceTemplatesRequest.setParams(std::move(params));
        request = McpProtocolListResourceTemplatesRequest::toJson(resourceTemplatesRequest);
        break;
    }
    default:
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "It's a bug:" << type << "is not a list request";
        return -1;
    }
    return sendRequest(request, identifier, type, std::move(pending));
}

#include "moc_mcpprotocolclientprotocolmanager.cpp"
