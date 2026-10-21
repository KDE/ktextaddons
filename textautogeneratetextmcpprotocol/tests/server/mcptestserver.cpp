/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "mcptestserver.h"
#include <QDateTime>
#include <QJsonObject>
#include <QTimer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestFormParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestURLParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImplementation>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourceTemplatesRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListResourceTemplatesResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPingRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolResourceTemplate>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolRoot>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSamplingMessage>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerPrompt>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerResource>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerTool>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolCall>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTextContent>
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

// Finish \a call with \a handler when client answers request \a requestId (sent by tool to client)
template<typename Signal, typename Handler>
void waitClientAnswer(McpProtocolServerProtocolManager *manager, McpProtocolServerToolCall *call, qint64 requestId, Signal signal, Handler handler)
{
    if (requestId < 0) {
        call->finishWithText(u"Client doesn't support this request"_s, true);
        return;
    }
    // call is the context: connections are dropped when call is deleted
    QObject::connect(manager, signal, call, [call, requestId, handler](qint64 id, const auto &answer) {
        if (id == requestId) {
            handler(call, answer);
        }
    });
    QObject::connect(manager, &McpProtocolServerProtocolManager::clientRequestFailed, call, [call, requestId](qint64 id, int code, const QString &message) {
        if (id == requestId) {
            call->finishWithText(u"Client error %1: %2"_s.arg(code).arg(message), true);
        }
    });
    // Client doesn't wait anymore for tool result: user doesn't have to answer
    QObject::connect(call, &McpProtocolServerToolCall::cancelled, manager, [manager, requestId]() {
        manager->cancelClientRequest(requestId, u"Tool call cancelled"_s);
    });
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
    addFunctionTool(this, McpProtocolServerTool::createTool(u"ask_name"_s, u"Ask user name (elicitation)"_s), [this](McpProtocolServerToolCall *call) {
        McpProtocolStringSchema nameSchema;
        nameSchema.setTitle(u"Name"_s);
        McpProtocolElicitRequestFormParams::RequestedSchema schema;
        schema.setProperties({{u"name"_s, nameSchema}});
        schema.setRequired(QStringList{u"name"_s});
        McpProtocolElicitRequestFormParams params;
        params.setMessage(u"What is your name?"_s);
        params.setRequestedSchema(schema);
        waitClientAnswer(this,
                         call,
                         requestElicitation(params),
                         &McpProtocolServerProtocolManager::elicitationResultReceived,
                         [](McpProtocolServerToolCall *call, const McpProtocolElicitResult &result) {
                             if (result.action() != McpProtocolElicitResult::Action::Accept) {
                                 call->finishWithText(u"User didn't give a name (%1)"_s.arg(McpProtocolElicitResult::convertActionToString(result.action())));
                                 return;
                             }
                             const McpProtocolUtils::ElicitResultContentValue value =
                                 result.content().value_or(QMap<QString, McpProtocolUtils::ElicitResultContentValue>{}).value(u"name"_s);
                             const auto name = std::get_if<QString>(&value);
                             call->finishWithText(u"Hello %1"_s.arg(name ? *name : QString()));
                         });
    });
    addFunctionTool(
        this,
        McpProtocolServerTool::createTool(u"summarize"_s,
                                          u"Summarize text with client LLM (sampling)"_s,
                                          QMap<QString, QJsonObject>{{u"text"_s, McpProtocolServerTool::schemaProperty(u"string"_s, u"Text to summarize"_s)}},
                                          {u"text"_s}),
        [this](McpProtocolServerToolCall *call) {
            McpProtocolTextContent content;
            content.setText(u"Summarize this text in one sentence:\n%1"_s.arg(call->arguments().value(u"text"_s).toString()));
            McpProtocolSamplingMessage message;
            message.setRole(McpProtocolUtils::Role::User);
            message.setContent(content);
            McpProtocolCreateMessageRequestParams params;
            params.setMessages({message});
            params.setMaxTokens(200);
            waitClientAnswer(this,
                             call,
                             requestSampling(params),
                             &McpProtocolServerProtocolManager::samplingResultReceived,
                             [](McpProtocolServerToolCall *call, const McpProtocolCreateMessageResult &result) {
                                 const McpProtocolUtils::CreateMessageResultContent resultContent = result.content();
                                 if (const auto text = std::get_if<McpProtocolTextContent>(&resultContent)) {
                                     call->finishWithText(text->text());
                                 } else {
                                     call->finishWithText(u"Client didn't return text"_s, true);
                                 }
                             });
        });
    addFunctionTool(this, McpProtocolServerTool::createTool(u"list_roots"_s, u"List client roots"_s), [this](McpProtocolServerToolCall *call) {
        waitClientAnswer(this,
                         call,
                         requestRoots(),
                         &McpProtocolServerProtocolManager::rootsReceived,
                         [](McpProtocolServerToolCall *call, const QList<McpProtocolRoot> &roots) {
                             QStringList uris;
                             uris.reserve(roots.count());
                             for (const McpProtocolRoot &root : roots) {
                                 uris.append(root.uri());
                             }
                             call->finishWithText(uris.isEmpty() ? u"No root"_s : uris.join(u'\n'));
                         });
    });
    connect(this, &McpProtocolServerProtocolManager::rootsListChanged, this, [this]() {
        Q_EMIT logMessage(u"Client roots changed"_s);
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
