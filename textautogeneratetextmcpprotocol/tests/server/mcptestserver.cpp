/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "mcptestserver.h"
#include <QDateTime>
#include <QJsonDocument>
#include <QTimer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolError>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCErrorResponse>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCResultResponse>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPingRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
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

QJsonObject tool(const QString &name, const QString &description, const QJsonObject &properties = {}, const QStringList &required = {})
{
    QJsonObject schema{{"type"_L1, u"object"_s}, {"properties"_L1, properties}};
    if (!required.isEmpty()) {
        schema["required"_L1] = QJsonArray::fromStringList(required);
    }
    return QJsonObject{{"name"_L1, name}, {"description"_L1, description}, {"inputSchema"_L1, schema}};
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
    QJsonObject result{{"content"_L1, QJsonArray{QJsonObject{{"type"_L1, u"text"_s}, {"text"_L1, text}}}}};
    if (isError) {
        result["isError"_L1] = true;
    }
    return result;
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
    const QString method = obj.value("method"_L1).toString();
    const QJsonObject params = obj.value("params"_L1).toObject();
    if (method == "initialize"_L1) {
        // Use version of client when we support it
        QString version = params.value("protocolVersion"_L1).toString();
        if (TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionFromString(version) == ProtocolVersion::Unknown) {
            version = TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::convertProtocolVersionToString(ProtocolVersion::V2025_11_25);
        }
        sendResult(id,
                   QJsonObject{{"protocolVersion"_L1, version},
                               {"capabilities"_L1,
                                QJsonObject{{"tools"_L1, QJsonObject{{"listChanged"_L1, true}}},
                                            {"prompts"_L1, QJsonObject{{"listChanged"_L1, false}}},
                                            {"resources"_L1, QJsonObject{}}}},
                               {"serverInfo"_L1, QJsonObject{{"name"_L1, u"mcpserver_gui"_s}, {"version"_L1, u"1.0"_s}}},
                               {"instructions"_L1, u"Test server for KTextAddons MCP client"_s}});
    } else if (method == "ping"_L1) {
        sendResult(id, {});
    } else if (method == "tools/list"_L1) {
        listTools(id, params);
    } else if (method == "tools/call"_L1) {
        callTool(id, params);
    } else if (method == "prompts/list"_L1) {
        const QJsonObject prompt{
            {"name"_L1, u"greeting"_s},
            {"description"_L1, u"Say hello to someone"_s},
            {"arguments"_L1, QJsonArray{QJsonObject{{"name"_L1, u"name"_s}, {"description"_L1, u"Name of the person"_s}, {"required"_L1, true}}}}};
        sendResult(id, QJsonObject{{"prompts"_L1, QJsonArray{prompt}}});
    } else if (method == "prompts/get"_L1) {
        getPrompt(id, params);
    } else if (method == "resources/templates/list"_L1) {
        const QJsonObject resourceTemplate{{"uriTemplate"_L1, u"file:///{path}"_s},
                                           {"name"_L1, u"file"_s},
                                           {"description"_L1, u"A local file"_s},
                                           {"mimeType"_L1, u"text/plain"_s}};
        sendResult(id, QJsonObject{{"resourceTemplates"_L1, QJsonArray{resourceTemplate}}});
    } else if (method == "resources/list"_L1) {
        sendResult(id, QJsonObject{{"resources"_L1, QJsonArray{}}});
    } else {
        sendError(id, methodNotFoundCode, u"Method not found: %1"_s.arg(method));
    }
}

QJsonArray McpTestServer::tools() const
{
    QJsonArray list{
        tool(u"echo"_s, u"Return text"_s, QJsonObject{{"text"_L1, schemaProperty(u"string"_s, u"Text to return"_s)}}, {u"text"_s}),
        tool(u"add"_s,
             u"Add two numbers"_s,
             QJsonObject{{"a"_L1, schemaProperty(u"number"_s, u"First number"_s)}, {"b"_L1, schemaProperty(u"number"_s, u"Second number"_s)}},
             {u"a"_s, u"b"_s}),
        tool(u"current_time"_s, u"Return current date and time"_s),
        tool(u"fail"_s, u"Always return a tool error (isError)"_s),
        tool(u"slow"_s,
             u"Answer after a delay (to test timeout and cancel)"_s,
             QJsonObject{{"milliseconds"_L1, schemaProperty(u"integer"_s, u"Delay in milliseconds"_s)}}),
    };
    if (mExtraTool) {
        list.append(tool(u"reverse"_s, u"Reverse text"_s, QJsonObject{{"text"_L1, schemaProperty(u"string"_s, u"Text to reverse"_s)}}, {u"text"_s}));
    }
    return list;
}

void McpTestServer::listTools(const QJsonValue &id, const QJsonObject &params)
{
    const QJsonArray allTools = tools();
    bool ok = true;
    const QString cursor = params.value("cursor"_L1).toString();
    const int start = cursor.isEmpty() ? 0 : cursor.toInt(&ok);
    if (!ok || start < 0 || start >= allTools.count()) {
        sendError(id, invalidParamsCode, u"Invalid cursor: %1"_s.arg(cursor));
        return;
    }
    QJsonArray page;
    for (int i = start; i < std::min(start + toolsPageSize, static_cast<int>(allTools.count())); ++i) {
        page.append(allTools.at(i));
    }
    QJsonObject result{{"tools"_L1, page}};
    if (start + toolsPageSize < allTools.count()) {
        result["nextCursor"_L1] = QString::number(start + toolsPageSize);
    }
    sendResult(id, result);
}

void McpTestServer::callTool(const QJsonValue &id, const QJsonObject &params)
{
    const QString name = params.value("name"_L1).toString();
    const QJsonObject arguments = params.value("arguments"_L1).toObject();
    if (name == "echo"_L1) {
        sendResult(id, textResult(arguments.value("text"_L1).toString()));
    } else if (name == "add"_L1) {
        if (!arguments.value("a"_L1).isDouble() || !arguments.value("b"_L1).isDouble()) {
            sendResult(id, textResult(u"Arguments a and b must be numbers"_s, true));
            return;
        }
        sendResult(id, textResult(QString::number(arguments.value("a"_L1).toDouble() + arguments.value("b"_L1).toDouble())));
    } else if (name == "current_time"_L1) {
        sendResult(id, textResult(QDateTime::currentDateTime().toString(Qt::ISODate)));
    } else if (name == "fail"_L1) {
        sendResult(id, textResult(u"This tool always fails"_s, true));
    } else if (name == "slow"_L1) {
        const int delay = arguments.value("milliseconds"_L1).toInt(2000);
        const QString key = idToString(id);
        mSlowRequests.insert(key);
        QTimer::singleShot(delay, this, [this, id, key, delay]() {
            // Don't answer cancelled request
            if (mSlowRequests.remove(key)) {
                sendResult(id, textResult(u"Waited %1 ms"_s.arg(delay)));
            }
        });
    } else if (name == "reverse"_L1 && mExtraTool) {
        QString text = arguments.value("text"_L1).toString();
        std::reverse(text.begin(), text.end());
        sendResult(id, textResult(text));
    } else {
        sendError(id, invalidParamsCode, u"Unknown tool: %1"_s.arg(name));
    }
}

void McpTestServer::getPrompt(const QJsonValue &id, const QJsonObject &params)
{
    if (params.value("name"_L1).toString() != "greeting"_L1) {
        sendError(id, invalidParamsCode, u"Unknown prompt: %1"_s.arg(params.value("name"_L1).toString()));
        return;
    }
    const QString name = params.value("arguments"_L1).toObject().value("name"_L1).toString();
    const QJsonObject message{{"role"_L1, u"user"_s}, {"content"_L1, QJsonObject{{"type"_L1, u"text"_s}, {"text"_L1, u"Say hello to %1"_s.arg(name)}}}};
    sendResult(id, QJsonObject{{"description"_L1, u"Greeting"_s}, {"messages"_L1, QJsonArray{message}}});
}

#include "moc_mcptestserver.cpp"
