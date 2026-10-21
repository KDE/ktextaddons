/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverprotocolmanager.h"
#include "mcpprotocolserverprompt.h"
#include "mcpprotocolserverresource.h"
#include "mcpprotocolservertool.h"
#include "mcpprotocolservertoolcall.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include "textautogeneratetextmcpprotocolcore_version.h"
#include <KLocalizedString>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCancelledNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCompleteRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCompleteRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCompleteResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestFormParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestURLParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolError>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolGetPromptRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolGetPromptRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCErrorResponse>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCResultResponse>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListPromptsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListPromptsResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourcesRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourcesResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListRootsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListRootsResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListToolsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListToolsResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolLoggingMessageNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPaginatedRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPingRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptArgument>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptListChangedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolReadResourceRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolReadResourceRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResourceListChangedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolRootsListChangedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSetLevelRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSetLevelRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolListChangedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <algorithm>
#include <utility>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

namespace
{
QString compact(const QJsonObject &obj)
{
    return QString::fromUtf8(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}

QString requestIdToString(const McpProtocolUtils::RequestId &id)
{
    return std::visit(
        [](const auto &v) -> QString {
            if constexpr (std::is_same_v<std::decay_t<decltype(v)>, QString>) {
                return v;
            } else {
                return QString::number(v);
            }
        },
        id);
}

// String id "1" and number id 1 are different requests: add type in key
QString requestIdKey(const McpProtocolUtils::RequestId &id)
{
    return (std::holds_alternative<QString>(id) ? u"s:"_s : u"n:"_s) + requestIdToString(id);
}
}

McpProtocolServerProtocolManager::McpProtocolServerProtocolManager(McpProtocolPlugin::TransportType transportType, QObject *parent)
    : QObject{parent}
    , mServer(new McpProtocolServer(transportType, this))
{
    connect(mServer, &McpProtocolServer::received, this, &McpProtocolServerProtocolManager::slotReceived);
    connect(mServer, &McpProtocolServer::error, this, &McpProtocolServerProtocolManager::slotError);
    connect(mServer, &McpProtocolServer::started, this, &McpProtocolServerProtocolManager::slotStarted);
    connect(mServer, &McpProtocolServer::finished, this, &McpProtocolServerProtocolManager::slotFinished);
}

McpProtocolServerProtocolManager::~McpProtocolServerProtocolManager()
{
    // Calls are children: avoid to emit signals to a partially destroyed object
    // Tell tools (still alive here) to stop their work
    const auto calls = std::exchange(mPendingCalls, {});
    for (McpProtocolServerToolCall *call : calls) {
        call->disconnect(this);
        call->cancel();
    }
}

void McpProtocolServerProtocolManager::setSettings(const McpProtocolSettings &settings)
{
    mSettings = settings;
}

void McpProtocolServerProtocolManager::start()
{
    // Transport checks settings: stdio server doesn't need any
    mServer->setSettings(mSettings);
    if (!mServer->canStart()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Server can not start";
        return;
    }
    if (mSettings.serverUrl().isEmpty()) {
        Q_EMIT logMessage(i18n("Starting server"));
    } else {
        Q_EMIT logMessage(i18n("Starting server on %1", mSettings.serverUrl().toString()));
    }
    mServer->start();
}

void McpProtocolServerProtocolManager::stop()
{
    mServer->stop();
}

bool McpProtocolServerProtocolManager::isRunning() const
{
    return mRunning;
}

void McpProtocolServerProtocolManager::setServerInfo(const McpProtocolImplementation &serverInfo)
{
    mServerInfo = serverInfo;
}

void McpProtocolServerProtocolManager::setInstructions(const QString &instructions)
{
    mInstructions = instructions;
}

void McpProtocolServerProtocolManager::setToolsPageSize(int size)
{
    if (size <= 0) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid tools page size" << size;
        return;
    }
    mToolsPageSize = size;
}

McpProtocolServerTool *McpProtocolServerProtocolManager::findTool(const QString &name) const
{
    for (const auto &tool : mTools) {
        if (tool->definition().name() == name) {
            return tool.get();
        }
    }
    return nullptr;
}

void McpProtocolServerProtocolManager::addTool(std::unique_ptr<McpProtocolServerTool> tool)
{
    if (!tool) {
        return;
    }
    const QString name = tool->definition().name();
    auto it = std::find_if(mTools.begin(), mTools.end(), [&name](const auto &t) {
        return t->definition().name() == name;
    });
    if (it != mTools.end()) {
        // Pending calls reference the old tool
        cancelToolCalls(name);
        *it = std::move(tool);
    } else {
        mTools.push_back(std::move(tool));
    }
    sendToolListChanged();
}

bool McpProtocolServerProtocolManager::removeTool(const QString &name)
{
    const auto it = std::find_if(mTools.begin(), mTools.end(), [&name](const auto &t) {
        return t->definition().name() == name;
    });
    if (it == mTools.end()) {
        return false;
    }
    cancelToolCalls(name);
    mTools.erase(it);
    sendToolListChanged();
    return true;
}

void McpProtocolServerProtocolManager::cancelToolCalls(const QString &name)
{
    // cancel() emits signals: don't iterate on mPendingCalls while calling it
    QList<McpProtocolServerToolCall *> calls;
    mPendingCalls.removeIf([&name, &calls](const auto &it) {
        if (it.value()->name() == name) {
            calls.append(it.value());
            return true;
        }
        return false;
    });
    for (McpProtocolServerToolCall *call : std::as_const(calls)) {
        // Client didn't cancel request: it waits for an answer
        sendError(call->requestId(), internalErrorCode, u"Tool removed: %1"_s.arg(name));
        call->cancel();
        call->deleteLater();
    }
}

QList<McpProtocolTool> McpProtocolServerProtocolManager::tools() const
{
    QList<McpProtocolTool> list;
    list.reserve(mTools.size());
    for (const auto &tool : mTools) {
        list.append(tool->definition());
    }
    return list;
}

void McpProtocolServerProtocolManager::sendToolListChanged()
{
    sendNotification(McpProtocolToolListChangedNotification::toJson({}));
}

void McpProtocolServerProtocolManager::sendNotification(const QJsonObject &notification)
{
    if (mRunning) {
        send(notification);
    }
}

McpProtocolServerPrompt *McpProtocolServerProtocolManager::findPrompt(const QString &name) const
{
    const auto it = std::find_if(mPrompts.cbegin(), mPrompts.cend(), [&name](const auto &p) {
        return p->definition().name() == name;
    });
    return it == mPrompts.cend() ? nullptr : it->get();
}

void McpProtocolServerProtocolManager::addPrompt(std::unique_ptr<McpProtocolServerPrompt> prompt)
{
    if (!prompt) {
        return;
    }
    const QString name = prompt->definition().name();
    auto it = std::find_if(mPrompts.begin(), mPrompts.end(), [&name](const auto &p) {
        return p->definition().name() == name;
    });
    if (it != mPrompts.end()) {
        *it = std::move(prompt);
    } else {
        mPrompts.push_back(std::move(prompt));
    }
    sendNotification(McpProtocolPromptListChangedNotification::toJson({}));
}

bool McpProtocolServerProtocolManager::removePrompt(const QString &name)
{
    const auto it = std::find_if(mPrompts.begin(), mPrompts.end(), [&name](const auto &p) {
        return p->definition().name() == name;
    });
    if (it == mPrompts.end()) {
        return false;
    }
    mPrompts.erase(it);
    sendNotification(McpProtocolPromptListChangedNotification::toJson({}));
    return true;
}

QList<McpProtocolPrompt> McpProtocolServerProtocolManager::prompts() const
{
    QList<McpProtocolPrompt> list;
    list.reserve(mPrompts.size());
    for (const auto &prompt : mPrompts) {
        list.append(prompt->definition());
    }
    return list;
}

McpProtocolServerResource *McpProtocolServerProtocolManager::findResource(const QString &uri) const
{
    const auto it = std::find_if(mResources.cbegin(), mResources.cend(), [&uri](const auto &r) {
        return r->definition().uri() == uri;
    });
    return it == mResources.cend() ? nullptr : it->get();
}

void McpProtocolServerProtocolManager::addResource(std::unique_ptr<McpProtocolServerResource> resource)
{
    if (!resource) {
        return;
    }
    const QString uri = resource->definition().uri();
    auto it = std::find_if(mResources.begin(), mResources.end(), [&uri](const auto &r) {
        return r->definition().uri() == uri;
    });
    if (it != mResources.end()) {
        *it = std::move(resource);
    } else {
        mResources.push_back(std::move(resource));
    }
    sendNotification(McpProtocolResourceListChangedNotification::toJson({}));
}

bool McpProtocolServerProtocolManager::removeResource(const QString &uri)
{
    const auto it = std::find_if(mResources.begin(), mResources.end(), [&uri](const auto &r) {
        return r->definition().uri() == uri;
    });
    if (it == mResources.end()) {
        return false;
    }
    mResources.erase(it);
    sendNotification(McpProtocolResourceListChangedNotification::toJson({}));
    return true;
}

QList<McpProtocolResource> McpProtocolServerProtocolManager::resources() const
{
    QList<McpProtocolResource> list;
    list.reserve(mResources.size());
    for (const auto &resource : mResources) {
        list.append(resource->definition());
    }
    return list;
}

void McpProtocolServerProtocolManager::send(const QJsonObject &obj)
{
    Q_EMIT logMessage(u"--> %1"_s.arg(compact(obj)));
    mServer->send(obj);
}

void McpProtocolServerProtocolManager::sendResult(const QJsonValue &id, const QJsonObject &result)
{
    McpProtocolResult protocolResult;
    protocolResult.setAdditionalProperties(result);
    McpProtocolJSONRPCResultResponse response;
    response.setId(McpProtocolUtils::requestIdFromJson(id));
    response.setResult(protocolResult);
    send(McpProtocolJSONRPCResultResponse::toJson(response));
}

void McpProtocolServerProtocolManager::sendError(const QJsonValue &id, int code, const QString &message)
{
    McpProtocolError error;
    error.setCode(code);
    error.setMessage(message);
    McpProtocolJSONRPCErrorResponse response;
    // Null id: request id couldn't be read
    if (!id.isNull() && !id.isUndefined()) {
        response.setId(McpProtocolUtils::requestIdFromJson(id));
    }
    response.setError(error);
    send(McpProtocolJSONRPCErrorResponse::toJson(response));
}

void McpProtocolServerProtocolManager::slotReceived(const QJsonObject &obj)
{
    Q_EMIT logMessage(u"<-- %1"_s.arg(compact(obj)));
    if (!obj.contains("method"_L1)) {
        // Response to a request sent by server
        handleClientResponse(obj);
        return;
    }
    if (!obj.contains("id"_L1)) {
        handleNotification(obj);
        return;
    }
    handleRequest(obj);
}

void McpProtocolServerProtocolManager::handleNotification(const QJsonObject &obj)
{
    const QByteArray method = obj.value("method"_L1).toString().toLatin1();
    if (method == McpProtocolCancelledNotification::type()) {
        cancelRequest(obj);
    } else if (method == McpProtocolRootsListChangedNotification::type()) {
        Q_EMIT rootsListChanged();
    }
}

void McpProtocolServerProtocolManager::handleClientResponse(const QJsonObject &obj)
{
    const McpProtocolUtils::RequestId id = McpProtocolUtils::requestIdFromJson(obj.value("id"_L1));
    // Server only sends number ids
    const qint64 *identifier = std::get_if<qint64>(&id);
    const auto it = identifier ? mPendingClientRequests.constFind(*identifier) : mPendingClientRequests.cend();
    if (it == mPendingClientRequests.cend()) {
        // Request can be cancelled before answer is received
        qCDebug(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Response received for an unknown request id:" << obj.value("id"_L1);
        return;
    }
    const qint64 requestId = *identifier;
    const ClientRequestType type = it.value();
    mPendingClientRequests.erase(it);
    if (obj.contains("error"_L1)) {
        const McpProtocolError error = McpProtocolJSONRPCErrorResponse::fromJson(obj).error();
        Q_EMIT clientRequestFailed(requestId, error.code(), error.message());
        return;
    }
    const QJsonObject result = obj.value("result"_L1).toObject();
    switch (type) {
    case ClientRequestType::Sampling:
        Q_EMIT samplingResultReceived(requestId, McpProtocolCreateMessageResult::fromJson(result));
        break;
    case ClientRequestType::Elicitation:
        Q_EMIT elicitationResultReceived(requestId, McpProtocolElicitResult::fromJson(result));
        break;
    case ClientRequestType::Roots:
        Q_EMIT rootsReceived(requestId, McpProtocolListRootsResult::fromJson(result).roots());
        break;
    }
}

McpProtocolClientCapabilities McpProtocolServerProtocolManager::clientCapabilities() const
{
    return mClientCapabilities;
}

qint64 McpProtocolServerProtocolManager::sendClientRequest(ClientRequestType type, const QJsonObject &request)
{
    if (!mRunning) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Server is not running: request can not be sent";
        return -1;
    }
    const qint64 requestId = mNextClientRequestId++;
    QJsonObject obj = request;
    obj["id"_L1] = requestId;
    mPendingClientRequests.insert(requestId, type);
    send(obj);
    return requestId;
}

qint64 McpProtocolServerProtocolManager::requestSampling(const McpProtocolCreateMessageRequestParams &params)
{
    const std::optional<McpProtocolClientCapabilities::Sampling> sampling = mClientCapabilities.sampling();
    if (!sampling.has_value()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Client doesn't support sampling";
        return -1;
    }
    // Specification: tools must not be sent when client doesn't support them
    if (params.tools().has_value() && !sampling->tools().has_value()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Client doesn't support tools in sampling";
        return -1;
    }
    if (!params.isValid()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid sampling params";
        return -1;
    }
    McpProtocolCreateMessageRequest request;
    request.setParams(params);
    return sendClientRequest(ClientRequestType::Sampling, McpProtocolCreateMessageRequest::toJson(request));
}

qint64 McpProtocolServerProtocolManager::requestElicitation(const McpProtocolUtils::ElicitRequestParams &params)
{
    const std::optional<McpProtocolClientCapabilities::Elicitation> elicitation = mClientCapabilities.elicitation();
    if (!elicitation.has_value()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Client doesn't support elicitation";
        return -1;
    }
    bool modeSupported = false;
    bool valid = false;
    if (const auto urlParams = std::get_if<McpProtocolElicitRequestURLParams>(&params)) {
        modeSupported = elicitation->url().has_value();
        valid = urlParams->isValid();
    } else {
        // Specification: empty elicitation capability means form mode
        modeSupported = elicitation->form().has_value() || !elicitation->url().has_value();
        valid = std::get<McpProtocolElicitRequestFormParams>(params).isValid();
    }
    if (!modeSupported) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Client doesn't support this elicitation mode";
        return -1;
    }
    if (!valid) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid elicitation params";
        return -1;
    }
    McpProtocolElicitRequest request;
    request.setParams(params);
    return sendClientRequest(ClientRequestType::Elicitation, McpProtocolElicitRequest::toJson(request));
}

qint64 McpProtocolServerProtocolManager::requestRoots()
{
    if (!mClientCapabilities.roots().has_value()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Client doesn't support roots";
        return -1;
    }
    return sendClientRequest(ClientRequestType::Roots, McpProtocolListRootsRequest::toJson({}));
}

void McpProtocolServerProtocolManager::cancelClientRequest(qint64 requestId, const QString &reason)
{
    if (!mPendingClientRequests.remove(requestId)) {
        return;
    }
    McpProtocolCancelledNotificationParams params;
    params.setRequestId(McpProtocolUtils::RequestId(requestId));
    if (!reason.isEmpty()) {
        params.setReason(reason);
    }
    McpProtocolCancelledNotification notification;
    notification.setParams(std::move(params));
    sendNotification(McpProtocolCancelledNotification::toJson(notification));
}

void McpProtocolServerProtocolManager::failAllClientRequests(const QString &message)
{
    const auto requests = std::exchange(mPendingClientRequests, {});
    for (auto it = requests.cbegin(), end = requests.cend(); it != end; ++it) {
        Q_EMIT clientRequestFailed(it.key(), internalErrorCode, message);
    }
}

void McpProtocolServerProtocolManager::handleRequest(const QJsonObject &obj)
{
    const QJsonValue id = obj.value("id"_L1);
    const QByteArray method = obj.value("method"_L1).toString().toLatin1();
    const QJsonObject params = obj.value("params"_L1).toObject();
    if (method == McpProtocolInitializeRequest::type()) {
        initialize(id, params);
    } else if (method == McpProtocolPingRequest::type()) {
        sendResult(id, {});
    } else if (method == McpProtocolListToolsRequest::type()) {
        listTools(id, params);
    } else if (method == McpProtocolCallToolRequest::type()) {
        callTool(id, params);
    } else if (method == McpProtocolListPromptsRequest::type()) {
        listPrompts(id, params);
    } else if (method == McpProtocolGetPromptRequest::type()) {
        getPrompt(id, params);
    } else if (method == McpProtocolListResourcesRequest::type()) {
        listResources(id, params);
    } else if (method == McpProtocolReadResourceRequest::type()) {
        readResource(id, params);
    } else if (method == McpProtocolCompleteRequest::type()) {
        complete(id, params);
    } else if (method == McpProtocolSetLevelRequest::type()) {
        setLoggingLevel(id, params);
    } else if (!handleCustomRequest(id, method, params)) {
        sendError(id, methodNotFoundCode, u"Method not found: %1"_s.arg(QString::fromLatin1(method)));
    }
}

McpProtocolServerCapabilities McpProtocolServerProtocolManager::capabilities() const
{
    McpProtocolServerCapabilities capabilities;
    capabilities.setTools(McpProtocolServerCapabilities::Tools().listChanged(true));
    capabilities.setLogging(QMap<QString, QJsonValue>{});
    if (!mPrompts.empty()) {
        capabilities.setPrompts(McpProtocolServerCapabilities::Prompts().listChanged(true));
        capabilities.setCompletions(QMap<QString, QJsonValue>{});
    }
    if (!mResources.empty()) {
        capabilities.setResources(McpProtocolServerCapabilities::Resources().listChanged(true));
    }
    return capabilities;
}

bool McpProtocolServerProtocolManager::handleCustomRequest(const QJsonValue &id, const QByteArray &method, const QJsonObject &params)
{
    Q_UNUSED(id)
    Q_UNUSED(method)
    Q_UNUSED(params)
    return false;
}

std::optional<QStringList> McpProtocolServerProtocolManager::completeResourceTemplate(const QString &uri,
                                                                                      const QString &argumentName,
                                                                                      const QString &value,
                                                                                      const QMap<QString, QString> &arguments) const
{
    Q_UNUSED(uri)
    Q_UNUSED(argumentName)
    Q_UNUSED(value)
    Q_UNUSED(arguments)
    return std::nullopt;
}

void McpProtocolServerProtocolManager::initialize(const QJsonValue &id, const QJsonObject &params)
{
    // Use version of client when we support it
    const McpProtocolInitializeRequestParams initializeParams = McpProtocolInitializeRequestParams::fromJson(params);
    QString version = initializeParams.protocolVersion();
    if (McpProtocolUtils::convertProtocolVersionFromString(version) == McpProtocolUtils::ProtocolVersion::Unknown) {
        version = McpProtocolUtils::convertProtocolVersionToString(McpProtocolUtils::ProtocolVersion::V2025_11_25);
    }
    // New client: previous one will never answer
    failAllClientRequests(u"Client reinitialized"_s);
    mClientCapabilities = initializeParams.capabilities();
    McpProtocolInitializeResult result;
    result.setProtocolVersion(version);
    result.setCapabilities(capabilities());
    // name and version are required: client rejects initialize result without them
    McpProtocolImplementation serverInfo = mServerInfo;
    if (serverInfo.name().isEmpty()) {
        serverInfo.setName(QCoreApplication::applicationName());
    }
    if (serverInfo.version().isEmpty()) {
        const QString applicationVersion = QCoreApplication::applicationVersion();
        serverInfo.setVersion(applicationVersion.isEmpty() ? QStringLiteral(TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_VERSION_STRING) : applicationVersion);
    }
    result.setServerInfo(serverInfo);
    if (!mInstructions.isEmpty()) {
        result.setInstructions(mInstructions);
    }
    sendResult(id, McpProtocolInitializeResult::toJson(result));
}

std::optional<qsizetype> McpProtocolServerProtocolManager::pageStart(const QJsonValue &id, const QJsonObject &params, qsizetype count)
{
    bool ok = true;
    const QString cursor = McpProtocolPaginatedRequestParams::fromJson(params).cursor().value_or(QString());
    const qsizetype start = cursor.isEmpty() ? 0 : cursor.toLongLong(&ok);
    // An empty list is valid on first page
    if (!ok || start < 0 || (start > 0 && start >= count)) {
        sendError(id, invalidParamsCode, u"Invalid cursor: %1"_s.arg(cursor));
        return std::nullopt;
    }
    return start;
}

std::optional<QString> McpProtocolServerProtocolManager::nextCursor(qsizetype start, qsizetype count) const
{
    if (start + mToolsPageSize < count) {
        return QString::number(start + mToolsPageSize);
    }
    return std::nullopt;
}

void McpProtocolServerProtocolManager::listTools(const QJsonValue &id, const QJsonObject &params)
{
    const QList<McpProtocolTool> allTools = tools();
    const std::optional<qsizetype> start = pageStart(id, params, allTools.count());
    if (!start.has_value()) {
        return;
    }
    McpProtocolListToolsResult result;
    result.setTools(allTools.mid(*start, mToolsPageSize));
    result.setNextCursor(nextCursor(*start, allTools.count()));
    sendResult(id, McpProtocolListToolsResult::toJson(result));
}

void McpProtocolServerProtocolManager::listPrompts(const QJsonValue &id, const QJsonObject &params)
{
    const QList<McpProtocolPrompt> allPrompts = prompts();
    const std::optional<qsizetype> start = pageStart(id, params, allPrompts.count());
    if (!start.has_value()) {
        return;
    }
    McpProtocolListPromptsResult result;
    result.setPrompts(allPrompts.mid(*start, mToolsPageSize));
    result.setNextCursor(nextCursor(*start, allPrompts.count()));
    sendResult(id, McpProtocolListPromptsResult::toJson(result));
}

void McpProtocolServerProtocolManager::getPrompt(const QJsonValue &id, const QJsonObject &params)
{
    const McpProtocolGetPromptRequestParams getPromptParams = McpProtocolGetPromptRequestParams::fromJson(params);
    const McpProtocolServerPrompt *prompt = findPrompt(getPromptParams.name());
    if (!prompt) {
        sendError(id, invalidParamsCode, u"Unknown prompt: %1"_s.arg(getPromptParams.name()));
        return;
    }
    const QMap<QString, QString> arguments = getPromptParams.arguments().value_or(QMap<QString, QString>{});
    const QList<McpProtocolPromptArgument> definitionArguments = prompt->definition().arguments().value_or(QList<McpProtocolPromptArgument>{});
    for (const McpProtocolPromptArgument &argument : definitionArguments) {
        if (argument.required().value_or(false) && !arguments.contains(argument.name())) {
            sendError(id, invalidParamsCode, u"Missing required argument: %1"_s.arg(argument.name()));
            return;
        }
    }
    sendResult(id, McpProtocolGetPromptResult::toJson(prompt->get(arguments)));
}

void McpProtocolServerProtocolManager::listResources(const QJsonValue &id, const QJsonObject &params)
{
    const QList<McpProtocolResource> allResources = resources();
    const std::optional<qsizetype> start = pageStart(id, params, allResources.count());
    if (!start.has_value()) {
        return;
    }
    McpProtocolListResourcesResult result;
    result.setResources(allResources.mid(*start, mToolsPageSize));
    result.setNextCursor(nextCursor(*start, allResources.count()));
    sendResult(id, McpProtocolListResourcesResult::toJson(result));
}

void McpProtocolServerProtocolManager::readResource(const QJsonValue &id, const QJsonObject &params)
{
    const QString uri = McpProtocolReadResourceRequestParams::fromJson(params).uri();
    const McpProtocolServerResource *resource = findResource(uri);
    if (!resource) {
        sendError(id, resourceNotFoundCode, u"Resource not found: %1"_s.arg(uri));
        return;
    }
    const McpProtocolReadResourceResult result = resource->read();
    if (result.contents().isEmpty()) {
        sendError(id, internalErrorCode, u"Unable to read resource: %1"_s.arg(uri));
        return;
    }
    sendResult(id, McpProtocolReadResourceResult::toJson(result));
}

void McpProtocolServerProtocolManager::complete(const QJsonValue &id, const QJsonObject &params)
{
    const McpProtocolCompleteRequestParams completeParams = McpProtocolCompleteRequestParams::fromJson(params);
    if (!completeParams.isValid()) {
        sendError(id, invalidParamsCode, u"Invalid completion params"_s);
        return;
    }
    const McpProtocolCompleteRequestParams::Argument argument = completeParams.argument();
    const QMap<QString, QString> arguments =
        completeParams.context().value_or(McpProtocolCompleteRequestParams::Context{}).arguments().value_or(QMap<QString, QString>{});
    QStringList values;
    const McpProtocolUtils::CompleteRequestParamsRef ref = completeParams.ref();
    if (const auto promptRef = std::get_if<McpProtocolPromptReference>(&ref)) {
        const McpProtocolServerPrompt *prompt = findPrompt(promptRef->name());
        if (!prompt) {
            sendError(id, invalidParamsCode, u"Unknown prompt: %1"_s.arg(promptRef->name()));
            return;
        }
        values = prompt->complete(argument.name(), argument.value(), arguments);
    } else {
        const QString uri = std::get<McpProtocolResourceTemplateReference>(ref).uri();
        const std::optional<QStringList> templateValues = completeResourceTemplate(uri, argument.name(), argument.value(), arguments);
        if (!templateValues.has_value()) {
            sendError(id, invalidParamsCode, u"Unknown resource template: %1"_s.arg(uri));
            return;
        }
        values = *templateValues;
    }
    McpProtocolCompleteResult::Completion completion;
    const bool hasMore = values.count() > maxCompletionValues;
    if (hasMore) {
        completion.setTotal(static_cast<int>(values.count()));
        values.resize(maxCompletionValues);
    }
    completion.setHasMore(hasMore);
    completion.setValues(std::move(values));
    McpProtocolCompleteResult result;
    result.setCompletion(std::move(completion));
    sendResult(id, McpProtocolCompleteResult::toJson(result));
}

void McpProtocolServerProtocolManager::setLoggingLevel(const QJsonValue &id, const QJsonObject &params)
{
    const McpProtocolSetLevelRequestParams setLevelParams = McpProtocolSetLevelRequestParams::fromJson(params);
    if (!setLevelParams.isValid()) {
        sendError(id, invalidParamsCode, u"Invalid logging level"_s);
        return;
    }
    mLoggingLevel = setLevelParams.level();
    sendResult(id, {});
}

McpProtocolUtils::LoggingLevel McpProtocolServerProtocolManager::loggingLevel() const
{
    return mLoggingLevel;
}

void McpProtocolServerProtocolManager::sendLogMessage(McpProtocolUtils::LoggingLevel level, const QJsonValue &data, const QString &logger)
{
    if (level == McpProtocolUtils::LoggingLevel::Unknown) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Invalid logging level";
        return;
    }
    // Levels are sorted by severity
    if (level < mLoggingLevel) {
        return;
    }
    McpProtocolLoggingMessageNotificationParams params;
    params.setLevel(level);
    params.setData(data);
    if (!logger.isEmpty()) {
        params.setLogger(logger);
    }
    McpProtocolLoggingMessageNotification notification;
    notification.setParams(std::move(params));
    sendNotification(McpProtocolLoggingMessageNotification::toJson(notification));
}

void McpProtocolServerProtocolManager::callTool(const QJsonValue &id, const QJsonObject &params)
{
    const McpProtocolCallToolRequestParams callToolParams = McpProtocolCallToolRequestParams::fromJson(params);
    const QString name = callToolParams.name();
    McpProtocolServerTool *tool = findTool(name);
    if (!tool) {
        sendError(id, invalidParamsCode, u"Unknown tool: %1"_s.arg(name));
        return;
    }
    const McpProtocolUtils::RequestId requestId = McpProtocolUtils::requestIdFromJson(id);
    const QString key = requestIdKey(requestId);
    if (mPendingCalls.contains(key)) {
        sendError(id, invalidParamsCode, u"Request id already used: %1"_s.arg(requestIdToString(requestId)));
        return;
    }
    auto call = new McpProtocolServerToolCall(id, name, callToolParams.arguments().value_or(QMap<QString, QJsonValue>{}), this);
    mPendingCalls.insert(key, call);
    connect(call, &McpProtocolServerToolCall::resultReady, this, [this, id, key](const QJsonObject &result) {
        sendResult(id, result);
        removeCall(key);
    });
    connect(call, &McpProtocolServerToolCall::errorReady, this, [this, id, key](int code, const QString &message) {
        sendError(id, code, message);
        removeCall(key);
    });
    // Tool can answer directly (call can be deleted after it)
    tool->call(call);
}

void McpProtocolServerProtocolManager::removeCall(const QString &key)
{
    if (McpProtocolServerToolCall *call = mPendingCalls.take(key)) {
        call->deleteLater();
    }
}

void McpProtocolServerProtocolManager::cancelRequest(const QJsonObject &obj)
{
    const auto requestId = McpProtocolCancelledNotification::fromJson(obj).params().requestId();
    if (!requestId.has_value()) {
        return;
    }
    if (McpProtocolServerToolCall *call = mPendingCalls.take(requestIdKey(*requestId))) {
        Q_EMIT logMessage(i18n("Request %1 cancelled by client", requestIdToString(*requestId)));
        call->cancel();
        call->deleteLater();
    }
}

void McpProtocolServerProtocolManager::cancelAllCalls()
{
    const auto calls = std::exchange(mPendingCalls, {});
    for (McpProtocolServerToolCall *call : calls) {
        call->cancel();
        call->deleteLater();
    }
}

void McpProtocolServerProtocolManager::slotError(const QString &str)
{
    Q_EMIT logMessage(i18n("Error: %1", str));
}

void McpProtocolServerProtocolManager::slotStarted()
{
    mRunning = true;
    Q_EMIT logMessage(i18n("Server started"));
    Q_EMIT runningChanged(true);
}

void McpProtocolServerProtocolManager::slotFinished()
{
    mRunning = false;
    // Next client starts with default level
    mLoggingLevel = McpProtocolUtils::LoggingLevel::Info;
    mClientCapabilities = {};
    cancelAllCalls();
    failAllClientRequests(u"Server stopped"_s);
    Q_EMIT logMessage(i18n("Server stopped"));
    Q_EMIT runningChanged(false);
}

#include "moc_mcpprotocolserverprotocolmanager.cpp"
