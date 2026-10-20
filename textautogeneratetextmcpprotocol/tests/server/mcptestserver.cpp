/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "mcptestserver.h"
#include <QDateTime>
#include <QJsonObject>
#include <QTimer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImplementation>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourceTemplatesRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourceTemplatesResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPingRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResourceTemplate>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerPrompt>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerResource>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerTool>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <functional>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
namespace
{
constexpr int toolsPageSize = 2;

// Tool defined by a function
class FunctionTool : public McpProtocolServerTool
{
public:
    using Handler = std::function<void(McpProtocolServerToolCall *)>;
    FunctionTool(const McpProtocolTool &definition, Handler handler)
        : mDefinition(definition)
        , mHandler(std::move(handler))
    {
    }

    [[nodiscard]] McpProtocolTool definition() const override
    {
        return mDefinition;
    }

    void call(McpProtocolServerToolCall *call) override
    {
        mHandler(call);
    }

private:
    const McpProtocolTool mDefinition;
    const Handler mHandler;
};

void addFunctionTool(McpProtocolServerProtocolManager *manager, const McpProtocolTool &definition, FunctionTool::Handler handler)
{
    manager->addTool(std::make_unique<FunctionTool>(definition, std::move(handler)));
}

class GreetingPrompt : public McpProtocolServerPrompt
{
public:
    [[nodiscard]] McpProtocolPrompt definition() const override
    {
        return createPrompt(u"greeting"_s, u"Say hello to someone"_s, {createArgument(u"name"_s, u"Name of the person"_s, true)});
    }

    [[nodiscard]] McpProtocolGetPromptResult get(const QMap<QString, QString> &arguments) const override
    {
        return createUserTextResult(u"Say hello to %1"_s.arg(arguments.value(u"name"_s)), u"Greeting"_s);
    }
};

class TextResource : public McpProtocolServerResource
{
public:
    [[nodiscard]] McpProtocolResource definition() const override
    {
        return createResource(u"file:///resource1"_s, u"resource1"_s, u"description resource1"_s, u"text/plain"_s);
    }

    [[nodiscard]] McpProtocolReadResourceResult read() const override
    {
        return textResult(u"Content of resource1"_s);
    }
};
}

McpTestServer::McpTestServer(QObject *parent)
    : McpProtocolServerProtocolManager(McpProtocolPlugin::TransportType::StreamableHttp, parent)
{
    McpProtocolImplementation serverInfo;
    serverInfo.setName(u"mcpserver_gui"_s);
    serverInfo.setVersion(u"1.0"_s);
    setServerInfo(serverInfo);
    setInstructions(u"Test server for KTextAddons MCP client"_s);
    setToolsPageSize(toolsPageSize);

    addFunctionTool(
        this,
        McpProtocolServerTool::createTool(u"echo"_s,
                                          u"Return text"_s,
                                          QMap<QString, QJsonObject>{{u"text"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Text to return"_s)}},
                                          {u"text"_s}),
        [](McpProtocolServerToolCall *call) {
            call->finishWithText(call->arguments().value(u"text"_s).toString());
        });
    addFunctionTool(
        this,
        McpProtocolServerTool::createTool(u"add"_s,
                                          u"Add two numbers"_s,
                                          QMap<QString, QJsonObject>{{u"a"_s, McpProtocolServerTool::schemaProperty(u"number"_s, u"First number"_s)},
                                                                     {u"b"_s, McpProtocolServerTool::schemaProperty(u"number"_s, u"Second number"_s)}},
                                          {u"a"_s, u"b"_s}),
        [](McpProtocolServerToolCall *call) {
            const QMap<QString, QJsonValue> arguments = call->arguments();
            if (!arguments.value(u"a"_s).isDouble() || !arguments.value(u"b"_s).isDouble()) {
                call->finishWithText(u"Arguments a and b must be numbers"_s, true);
                return;
            }
            call->finishWithText(QString::number(arguments.value(u"a"_s).toDouble() + arguments.value(u"b"_s).toDouble()));
        });
    addFunctionTool(this, McpProtocolServerTool::createTool(u"current_time"_s, u"Return current date and time"_s), [](McpProtocolServerToolCall *call) {
        call->finishWithText(QDateTime::currentDateTime().toString(Qt::ISODate));
    });
    addFunctionTool(this, McpProtocolServerTool::createTool(u"fail"_s, u"Always return a tool error (isError)"_s), [](McpProtocolServerToolCall *call) {
        call->finishWithText(u"This tool always fails"_s, true);
    });
    addFunctionTool(this,
                    McpProtocolServerTool::createTool(
                        u"slow"_s,
                        u"Answer after a delay (to test timeout and cancel)"_s,
                        QMap<QString, QJsonObject>{{u"milliseconds"_s, McpProtocolServerTool::schemaProperty(u"integer"_s, u"Delay in milliseconds"_s)}}),
                    [](McpProtocolServerToolCall *call) {
                        const int delay = call->arguments().value(u"milliseconds"_s).toInt(2000);
                        // call is the context: timer is dropped when request is cancelled (call deleted)
                        QTimer::singleShot(delay, call, [call, delay]() {
                            call->finishWithText(u"Waited %1 ms"_s.arg(delay));
                        });
                    });
    addPrompt(std::make_unique<GreetingPrompt>());
    addResource(std::make_unique<TextResource>());
}

McpTestServer::~McpTestServer() = default;

void McpTestServer::start(const QUrl &url, const QString &token)
{
    McpProtocolSettings settings;
    settings.setServerUrl(url);
    settings.setAuthToken(token.toUtf8());
    setSettings(settings);
    McpProtocolServerProtocolManager::start();
}

void McpTestServer::toggleExtraTool()
{
    mExtraTool = !mExtraTool;
    if (mExtraTool) {
        addFunctionTool(
            this,
            McpProtocolServerTool::createTool(u"reverse"_s,
                                              u"Reverse text"_s,
                                              QMap<QString, QJsonObject>{{u"text"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Text to reverse"_s)}},
                                              {u"text"_s}),
            [](McpProtocolServerToolCall *call) {
                QString text = call->arguments().value(u"text"_s).toString();
                std::reverse(text.begin(), text.end());
                call->finishWithText(text);
            });
        Q_EMIT logMessage(u"Tool \"reverse\" added"_s);
    } else {
        removeTool(u"reverse"_s);
        Q_EMIT logMessage(u"Tool \"reverse\" removed"_s);
    }
}

void McpTestServer::pingClient()
{
    ++mServerRequestId;
    McpProtocolPingRequest request;
    request.setId(u"server-%1"_s.arg(mServerRequestId));
    send(McpProtocolPingRequest::toJson(request));
}

bool McpTestServer::handleCustomRequest(const QJsonValue &id, const QByteArray &method, const QJsonObject &params)
{
    Q_UNUSED(params)
    if (method != McpProtocolListResourceTemplatesRequest::type()) {
        return false;
    }
    McpProtocolResourceTemplate resourceTemplate;
    resourceTemplate.setUriTemplate(u"file:///{path}"_s);
    resourceTemplate.setName(u"file"_s);
    resourceTemplate.setDescription(u"A local file"_s);
    resourceTemplate.setMimeType(u"text/plain"_s);

    McpProtocolListResourceTemplatesResult result;
    result.setResourceTemplates({resourceTemplate});
    sendResult(id, McpProtocolListResourceTemplatesResult::toJson(result));
    return true;
}

#include "moc_mcptestserver.cpp"
