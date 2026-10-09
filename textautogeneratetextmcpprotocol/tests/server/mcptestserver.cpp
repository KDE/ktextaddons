/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "mcptestserver.h"
#include <QDateTime>
#include <QJsonDocument>
#include <QTimer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolError>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolGetPromptRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolGetPromptRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolGetPromptResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImplementation>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCErrorResponse>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCResultResponse>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListPromptsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListPromptsResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourceTemplatesRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourceTemplatesResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourcesRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourcesResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListToolsRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListToolsResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPaginatedRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPingRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPrompt>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptArgument>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptMessage>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResourceTemplate>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerCapabilities>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTextContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolToolListChangedNotification>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
using McpProtocolUtils::ProtocolVersion;
namespace
{
constexpr int toolsPageSize = 2;
// JSON-RPC error codes
constexpr int methodNotFoundCode = -32601;
constexpr int invalidParamsCode = -32602;

McpProtocolTool tool(const QString &name, const QString &description, const QMap<QString, QJsonObject> &properties = {}, const QStringList &required = {})
{
    McpProtocolTool::InputSchema schema;
    schema.mProperties = properties;
    if (!required.isEmpty()) {
        schema.mRequired = required;
    }
    McpProtocolTool tool;
    tool.setName(name);
    tool.setDescription(description);
    tool.setInputSchema(schema);
    return tool;
}

QJsonObject schemaProperty(const QString &type, const QString &description)
{
    return QJsonObject{{"type"_L1, type}, {"description"_L1, description}};
}

QString compact(const QJsonObject &obj)
{
    return QString::fromUtf8(QJsonDocument(obj).toJson(QJsonDocument::Compact));
}
}

McpTestServer::McpTestServer(QObject *parent)
    : QObject{parent}
    , mServer(new TextAutoGenerateTextMcpProtocolCore::McpProtocolServer(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp,
                                                                         this))
{
    connect(mServer, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServer::received, this, &McpTestServer::slotReceived);
    connect(mServer, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServer::error, this, [this](const QString &str) {
        Q_EMIT logMessage(u"ERROR: %1"_s.arg(str));
    });
    connect(mServer, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServer::started, this, [this]() {
        mRunning = true;
        Q_EMIT logMessage(u"Server started"_s);
        Q_EMIT runningChanged(true);
    });
    connect(mServer, &TextAutoGenerateTextMcpProtocolCore::McpProtocolServer::finished, this, [this]() {
        mRunning = false;
        mSlowRequests.clear();
        Q_EMIT logMessage(u"Server stopped"_s);
        Q_EMIT runningChanged(false);
    });
}

McpTestServer::~McpTestServer() = default;

void McpTestServer::start(const QUrl &url)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(url);
    mServer->setSettings(settings);
    Q_EMIT logMessage(u"Starting server on %1"_s.arg(url.toString()));
    mServer->start();
}

void McpTestServer::stop()
{
    mServer->stop();
}

bool McpTestServer::isRunning() const
{
    return mRunning;
}

void McpTestServer::toggleExtraTool()
{
    mExtraTool = !mExtraTool;
    Q_EMIT logMessage(mExtraTool ? u"Tool \"reverse\" added"_s : u"Tool \"reverse\" removed"_s);
    send(McpProtocolToolListChangedNotification::toJson({}));
}

void McpTestServer::pingClient()
{
    ++mServerRequestId;
    McpProtocolPingRequest request;
    request.setId(u"server-%1"_s.arg(mServerRequestId));
    send(McpProtocolPingRequest::toJson(request));
}

void McpTestServer::send(const QJsonObject &obj)
{
    Q_EMIT logMessage(u"--> %1"_s.arg(compact(obj)));
    mServer->send(obj);
}

void McpTestServer::sendResult(const QJsonValue &id, const QJsonObject &result)
{
    McpProtocolResult protocolResult;
    protocolResult.setAdditionalProperties(result);
    McpProtocolJSONRPCResultResponse response;
    response.setId(McpProtocolUtils::requestIdFromJson(id));
    response.setResult(protocolResult);
    send(McpProtocolJSONRPCResultResponse::toJson(response));
}

void McpTestServer::sendError(const QJsonValue &id, int code, const QString &message)
{
    McpProtocolError error;
    error.setCode(code);
    error.setMessage(message);
    McpProtocolJSONRPCErrorResponse response;
    response.setId(McpProtocolUtils::requestIdFromJson(id));
    response.setError(error);
    send(McpProtocolJSONRPCErrorResponse::toJson(response));
}

QString McpTestServer::idToString(const QJsonValue &id)
{
    return id.isString() ? id.toString() : QString::number(id.toInteger());
}

QJsonObject McpTestServer::textResult(const QString &text, bool isError)
{
    McpProtocolTextContent content;
    content.setText(text);
    McpProtocolCallToolResult result;
    result.setContent({content});
    if (isError) {
        result.setIsError(true);
    }
    return McpProtocolCallToolResult::toJson(result);
}

void McpTestServer::slotReceived(const QJsonObject &obj)
{
    Q_EMIT logMessage(u"<-- %1"_s.arg(compact(obj)));
    if (!obj.contains("method"_L1)) {
        // Response to our ping request
        return;
    }
    if (!obj.contains("id"_L1)) {
        if (obj.value("method"_L1).toString() == "notifications/cancelled"_L1) {
            const QString id = idToString(obj.value("params"_L1).toObject().value("requestId"_L1));
            if (mSlowRequests.remove(id)) {
                Q_EMIT logMessage(u"Request %1 cancelled by client"_s.arg(id));
            }
        }
        return;
    }
    handleRequest(obj);
}

void McpTestServer::handleRequest(const QJsonObject &obj)
{
    const QJsonValue id = obj.value("id"_L1);
    const QByteArray method = obj.value("method"_L1).toString().toLatin1();
    const QJsonObject params = obj.value("params"_L1).toObject();
    if (method == McpProtocolInitializeRequest::type()) {
        // Use version of client when we support it
        QString version = McpProtocolInitializeRequestParams::fromJson(params).protocolVersion();
        if (McpProtocolUtils::convertProtocolVersionFromString(version) == ProtocolVersion::Unknown) {
            version = McpProtocolUtils::convertProtocolVersionToString(ProtocolVersion::V2025_11_25);
        }
        McpProtocolServerCapabilities capabilities;
        capabilities.setTools(McpProtocolServerCapabilities::Tools().listChanged(true));
        capabilities.setPrompts(McpProtocolServerCapabilities::Prompts().listChanged(false));
        capabilities.setResources(McpProtocolServerCapabilities::Resources());

        McpProtocolImplementation serverInfo;
        serverInfo.setName(u"mcpserver_gui"_s);
        serverInfo.setVersion(u"1.0"_s);

        McpProtocolInitializeResult result;
        result.setProtocolVersion(version);
        result.setCapabilities(capabilities);
        result.setServerInfo(serverInfo);
        result.setInstructions(u"Test server for KTextAddons MCP client"_s);
        sendResult(id, McpProtocolInitializeResult::toJson(result));
    } else if (method == McpProtocolPingRequest::type()) {
        sendResult(id, {});
    } else if (method == McpProtocolListToolsRequest::type()) {
        listTools(id, params);
    } else if (method == McpProtocolCallToolRequest::type()) {
        callTool(id, params);
    } else if (method == McpProtocolListPromptsRequest::type()) {
        McpProtocolPromptArgument argument;
        argument.setName(u"name"_s);
        argument.setDescription(u"Name of the person"_s);
        argument.setRequired(true);

        McpProtocolPrompt prompt;
        prompt.setName(u"greeting"_s);
        prompt.setDescription(u"Say hello to someone"_s);
        prompt.setArguments(QList<McpProtocolPromptArgument>{argument});

        McpProtocolListPromptsResult result;
        result.setPrompts({prompt});
        sendResult(id, McpProtocolListPromptsResult::toJson(result));
    } else if (method == McpProtocolGetPromptRequest::type()) {
        getPrompt(id, params);
    } else if (method == McpProtocolListResourceTemplatesRequest::type()) {
        McpProtocolResourceTemplate resourceTemplate;
        resourceTemplate.setUriTemplate(u"file:///{path}"_s);
        resourceTemplate.setName(u"file"_s);
        resourceTemplate.setDescription(u"A local file"_s);
        resourceTemplate.setMimeType(u"text/plain"_s);

        McpProtocolListResourceTemplatesResult result;
        result.setResourceTemplates({resourceTemplate});
        sendResult(id, McpProtocolListResourceTemplatesResult::toJson(result));
    } else if (method == McpProtocolListResourcesRequest::type()) {
        sendResult(id, McpProtocolListResourcesResult::toJson({}));
    } else {
        sendError(id, methodNotFoundCode, u"Method not found: %1"_s.arg(QString::fromLatin1(method)));
    }
}

QList<McpProtocolTool> McpTestServer::tools() const
{
    QList<McpProtocolTool> list{
        tool(u"echo"_s, u"Return text"_s, QMap<QString, QJsonObject>{{u"text"_s, schemaProperty(u"string"_s, u"Text to return"_s)}}, {u"text"_s}),
        tool(u"add"_s,
             u"Add two numbers"_s,
             QMap<QString, QJsonObject>{{u"a"_s, schemaProperty(u"number"_s, u"First number"_s)}, {u"b"_s, schemaProperty(u"number"_s, u"Second number"_s)}},
             {u"a"_s, u"b"_s}),
        tool(u"current_time"_s, u"Return current date and time"_s),
        tool(u"fail"_s, u"Always return a tool error (isError)"_s),
        tool(u"slow"_s,
             u"Answer after a delay (to test timeout and cancel)"_s,
             QMap<QString, QJsonObject>{{u"milliseconds"_s, schemaProperty(u"integer"_s, u"Delay in milliseconds"_s)}}),
    };
    if (mExtraTool) {
        list.append(
            tool(u"reverse"_s, u"Reverse text"_s, QMap<QString, QJsonObject>{{u"text"_s, schemaProperty(u"string"_s, u"Text to reverse"_s)}}, {u"text"_s}));
    }
    return list;
}

void McpTestServer::listTools(const QJsonValue &id, const QJsonObject &params)
{
    const QList<McpProtocolTool> allTools = tools();
    bool ok = true;
    const QString cursor = McpProtocolPaginatedRequestParams::fromJson(params).cursor();
    const int start = cursor.isEmpty() ? 0 : cursor.toInt(&ok);
    if (!ok || start < 0 || start >= allTools.count()) {
        sendError(id, invalidParamsCode, u"Invalid cursor: %1"_s.arg(cursor));
        return;
    }
    McpProtocolListToolsResult result;
    result.setTools(allTools.mid(start, toolsPageSize));
    if (start + toolsPageSize < allTools.count()) {
        result.setNextCursor(QString::number(start + toolsPageSize));
    }
    sendResult(id, McpProtocolListToolsResult::toJson(result));
}

void McpTestServer::callTool(const QJsonValue &id, const QJsonObject &params)
{
    const McpProtocolCallToolRequestParams callToolParams = McpProtocolCallToolRequestParams::fromJson(params);
    const QString name = callToolParams.name();
    const QMap<QString, QJsonValue> arguments = callToolParams.arguments().value_or(QMap<QString, QJsonValue>{});
    if (name == "echo"_L1) {
        sendResult(id, textResult(arguments.value(u"text"_s).toString()));
    } else if (name == "add"_L1) {
        if (!arguments.value(u"a"_s).isDouble() || !arguments.value(u"b"_s).isDouble()) {
            sendResult(id, textResult(u"Arguments a and b must be numbers"_s, true));
            return;
        }
        sendResult(id, textResult(QString::number(arguments.value(u"a"_s).toDouble() + arguments.value(u"b"_s).toDouble())));
    } else if (name == "current_time"_L1) {
        sendResult(id, textResult(QDateTime::currentDateTime().toString(Qt::ISODate)));
    } else if (name == "fail"_L1) {
        sendResult(id, textResult(u"This tool always fails"_s, true));
    } else if (name == "slow"_L1) {
        const int delay = arguments.value(u"milliseconds"_s).toInt(2000);
        const QString key = idToString(id);
        mSlowRequests.insert(key);
        QTimer::singleShot(delay, this, [this, id, key, delay]() {
            // Don't answer cancelled request
            if (mSlowRequests.remove(key)) {
                sendResult(id, textResult(u"Waited %1 ms"_s.arg(delay)));
            }
        });
    } else if (name == "reverse"_L1 && mExtraTool) {
        QString text = arguments.value(u"text"_s).toString();
        std::reverse(text.begin(), text.end());
        sendResult(id, textResult(text));
    } else {
        sendError(id, invalidParamsCode, u"Unknown tool: %1"_s.arg(name));
    }
}

void McpTestServer::getPrompt(const QJsonValue &id, const QJsonObject &params)
{
    const McpProtocolGetPromptRequestParams getPromptParams = McpProtocolGetPromptRequestParams::fromJson(params);
    if (getPromptParams.name() != "greeting"_L1) {
        sendError(id, invalidParamsCode, u"Unknown prompt: %1"_s.arg(getPromptParams.name()));
        return;
    }
    const QString name = getPromptParams.arguments().value_or(QMap<QString, QString>{}).value(u"name"_s);
    McpProtocolTextContent content;
    content.setText(u"Say hello to %1"_s.arg(name));
    McpProtocolPromptMessage message;
    message.setRole(McpProtocolUtils::Role::User);
    message.setContent(content);

    McpProtocolGetPromptResult result;
    result.setDescription(u"Greeting"_s);
    result.setMessages({message});
    sendResult(id, McpProtocolGetPromptResult::toJson(result));
}

#include "moc_mcptestserver.cpp"
