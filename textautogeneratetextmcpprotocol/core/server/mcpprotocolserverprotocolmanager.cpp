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
#include <KLocalizedString>
#include <QJsonDocument>
#include <QJsonObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCancelledNotification>
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
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListToolsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListToolsResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPaginatedRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPingRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptArgument>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptListChangedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolReadResourceRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolReadResourceRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResourceListChangedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServer>
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
        // Response to a request sent by server (ping…)
        return;
    }
    if (!obj.contains("id"_L1)) {
        if (obj.value("method"_L1).toString().toLatin1() == McpProtocolCancelledNotification::type()) {
            cancelRequest(obj);
        }
        return;
    }
    handleRequest(obj);
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
    } else if (!handleCustomRequest(id, method, params)) {
        sendError(id, methodNotFoundCode, u"Method not found: %1"_s.arg(QString::fromLatin1(method)));
    }
}

McpProtocolServerCapabilities McpProtocolServerProtocolManager::capabilities() const
{
    McpProtocolServerCapabilities capabilities;
    capabilities.setTools(McpProtocolServerCapabilities::Tools().listChanged(true));
    if (!mPrompts.empty()) {
        capabilities.setPrompts(McpProtocolServerCapabilities::Prompts().listChanged(true));
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

void McpProtocolServerProtocolManager::initialize(const QJsonValue &id, const QJsonObject &params)
{
    // Use version of client when we support it
    QString version = McpProtocolInitializeRequestParams::fromJson(params).protocolVersion();
    if (McpProtocolUtils::convertProtocolVersionFromString(version) == McpProtocolUtils::ProtocolVersion::Unknown) {
        version = McpProtocolUtils::convertProtocolVersionToString(McpProtocolUtils::ProtocolVersion::V2025_11_25);
    }
    McpProtocolInitializeResult result;
    result.setProtocolVersion(version);
    result.setCapabilities(capabilities());
    result.setServerInfo(mServerInfo);
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
    cancelAllCalls();
    Q_EMIT logMessage(i18n("Server stopped"));
    Q_EMIT runningChanged(false);
}

#include "moc_mcpprotocolserverprotocolmanager.cpp"
