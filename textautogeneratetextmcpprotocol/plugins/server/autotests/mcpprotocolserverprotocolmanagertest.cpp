/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverprotocolmanagertest.h"
#include <QCoreApplication>
#include <QJsonArray>
#include <QRegularExpression>
#include <QSignalSpy>
#include <QTcpServer>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientProtocolManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCompleteRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCompleteResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageRequestParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestFormParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestURLParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolGetPromptResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImplementation>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolLoggingMessageNotificationParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptMessage>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolReadResourceResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolRoot>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSamplingMessage>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerPrompt>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerProtocolManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerResource>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTextContent>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTextResourceContents>
#include <memory>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
using MethodType = McpProtocolClientProtocolManager::MethodType;
QTEST_GUILESS_MAIN(McpProtocolServerProtocolManagerTest)

namespace
{
class GreetingPrompt : public McpProtocolServerPrompt
{
public:
    explicit GreetingPrompt(const QString &name = u"greeting"_s)
        : mName(name)
    {
    }

    [[nodiscard]] McpProtocolPrompt definition() const override
    {
        return createPrompt(mName, u"Say hello"_s, {createArgument(u"name"_s, u"Name of the person"_s, true), createArgument(u"style"_s, u"Style"_s)});
    }

    [[nodiscard]] McpProtocolGetPromptResult get(const QMap<QString, QString> &arguments) const override
    {
        return createUserTextResult(u"Say hello to %1"_s.arg(arguments.value(u"name"_s)), u"Greeting"_s);
    }

    [[nodiscard]] QStringList complete(const QString &argumentName, const QString &value, const QMap<QString, QString> &arguments) const override
    {
        Q_UNUSED(arguments)
        if (argumentName == "style"_L1) {
            return QStringList{u"formal"_s, u"friendly"_s, u"funny"_s}.filter(QRegularExpression(u"^"_s + QRegularExpression::escape(value)));
        }
        if (argumentName == "name"_L1) {
            // More values than allowed in result
            QStringList names;
            for (int i = 0; i < 150; ++i) {
                names.append(value + QString::number(i));
            }
            return names;
        }
        return {};
    }

private:
    const QString mName;
};

class TextResource : public McpProtocolServerResource
{
public:
    explicit TextResource(const QString &uri, const QString &text)
        : mUri(uri)
        , mText(text)
    {
    }

    [[nodiscard]] McpProtocolResource definition() const override
    {
        return createResource(mUri, u"resource"_s, u"A resource"_s, u"text/plain"_s);
    }

    [[nodiscard]] McpProtocolReadResourceResult read() const override
    {
        // Empty text: simulate a read error
        return mText.isEmpty() ? McpProtocolReadResourceResult() : textResult(mText);
    }

private:
    const QString mUri;
    const QString mText;
};

QUrl freeUrl()
{
    QTcpServer server;
    server.listen(QHostAddress::LocalHost);
    return QUrl(u"http://127.0.0.1:%1/mcp"_s.arg(server.serverPort()));
}

void startServer(McpProtocolServerProtocolManager &server, const QUrl &url)
{
    McpProtocolSettings settings;
    settings.setServerUrl(url);
    server.setSettings(settings);
    server.start();
    QVERIFY(server.isRunning());
}

McpServer serverSettings(const QUrl &url)
{
    McpServer server;
    server.setName(u"test"_s);
    server.createUniqueIdentifier();
    server.setTransportType(McpProtocolPlugin::TransportType::StreamableHttp);
    McpProtocolSettings settings;
    settings.setServerUrl(url);
    server.setSettings(settings);
    return server;
}

void initialize(McpProtocolClientProtocolManager &client)
{
    const QSignalSpy initializedSpy(&client, &McpProtocolClientProtocolManager::initialized);
    client.initializeClient();
    QTRY_COMPARE(initializedSpy.count(), 1);
}

// Wait response of request \a identifier
QJsonObject waitResponse(McpProtocolClientProtocolManager &client, qint64 identifier)
{
    QJsonObject response;
    const QMetaObject::Connection connection =
        QObject::connect(&client, &McpProtocolClientProtocolManager::received, &client, [&response, identifier](const QJsonObject &obj) {
            if (obj.value("id"_L1).toInteger() == identifier) {
                response = obj;
            }
        });
    if (!QTest::qWaitFor(
            [&response]() {
                return !response.isEmpty();
            },
            5000)) {
        qWarning() << "No response received for request" << identifier;
    }
    QObject::disconnect(connection);
    return response;
}

QStringList names(const QJsonObject &response, const QString &key)
{
    QStringList list;
    const QJsonArray items = response.value("result"_L1).toObject().value(key).toArray();
    for (const auto &item : items) {
        const QJsonObject obj = item.toObject();
        list.append(obj.contains("uri"_L1) ? obj.value("uri"_L1).toString() : obj.value("name"_L1).toString());
    }
    return list;
}

int errorCode(const QJsonObject &response)
{
    return response.value("error"_L1).toObject().value("code"_L1).toInt();
}

McpProtocolCompleteRequestParams completeParams(const McpProtocolUtils::CompleteRequestParamsRef &ref, const QString &argumentName, const QString &value)
{
    McpProtocolCompleteRequestParams::Argument argument;
    argument.setName(argumentName);
    argument.setValue(value);
    McpProtocolCompleteRequestParams params;
    params.setRef(ref);
    params.setArgument(argument);
    return params;
}

McpProtocolPromptReference promptReference(const QString &name)
{
    McpProtocolPromptReference reference;
    reference.setName(name);
    return reference;
}

McpProtocolTextContent textContent(const QString &text)
{
    McpProtocolTextContent content;
    content.setText(text);
    return content;
}

McpProtocolCreateMessageRequestParams samplingParams(const QString &text)
{
    McpProtocolSamplingMessage message;
    message.setRole(McpProtocolUtils::Role::User);
    message.setContent(textContent(text));
    McpProtocolCreateMessageRequestParams params;
    params.setMaxTokens(100);
    params.setMessages({message});
    return params;
}

McpProtocolElicitRequestFormParams formParams(const QString &message)
{
    McpProtocolElicitRequestFormParams::RequestedSchema schema;
    schema.setProperties({{u"name"_s, McpProtocolStringSchema()}});
    McpProtocolElicitRequestFormParams params;
    params.setMessage(message);
    params.setRequestedSchema(schema);
    return params;
}

McpProtocolRoot root(const QString &uri)
{
    McpProtocolRoot root;
    root.setUri(uri);
    return root;
}
}

McpProtocolServerProtocolManagerTest::McpProtocolServerProtocolManagerTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolServerProtocolManagerTest::shouldAnnouncePromptsAndResourcesWhenRegistered()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    server.addPrompt(std::make_unique<GreetingPrompt>());
    server.addResource(std::make_unique<TextResource>(u"file:///a.txt"_s, u"a"_s));
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    const McpProtocolServerCapabilities capabilities = client.initializeResult().capabilities();
    QVERIFY(capabilities.tools().has_value());
    QVERIFY(capabilities.prompts().has_value());
    QCOMPARE(capabilities.prompts()->listChanged(), true);
    QVERIFY(capabilities.resources().has_value());
    QCOMPARE(capabilities.resources()->listChanged(), true);
}

void McpProtocolServerProtocolManagerTest::shouldUseDefaultServerInfo()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    // No setServerInfo(): application name is used, client must accept it
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    const McpProtocolImplementation serverInfo = client.initializeResult().serverInfo();
    QCOMPARE(serverInfo.name(), QCoreApplication::applicationName());
    QVERIFY(!serverInfo.version().isEmpty());
}

void McpProtocolServerProtocolManagerTest::shouldKeepServerInfo()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    McpProtocolImplementation serverInfo;
    serverInfo.setName(u"testserver"_s);
    serverInfo.setVersion(u"1.0"_s);
    serverInfo.setTitle(u"Test server"_s);
    server.setServerInfo(serverInfo);
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    QCOMPARE(client.initializeResult().serverInfo(), serverInfo);
}

void McpProtocolServerProtocolManagerTest::shouldNotAnnouncePromptsAndResourcesByDefault()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    const McpProtocolServerCapabilities capabilities = client.initializeResult().capabilities();
    QVERIFY(capabilities.tools().has_value());
    QVERIFY(!capabilities.prompts().has_value());
    QVERIFY(!capabilities.resources().has_value());
}

void McpProtocolServerProtocolManagerTest::shouldListAndGetPrompt()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    server.addPrompt(std::make_unique<GreetingPrompt>());
    QCOMPARE(server.prompts().count(), 1);
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    const QJsonObject list = waitResponse(client, client.executeAction(MethodType::ListPrompts));
    QCOMPARE(names(list, u"prompts"_s), QStringList{u"greeting"_s});
    const QJsonArray arguments = list.value("result"_L1).toObject().value("prompts"_L1).toArray().at(0).toObject().value("arguments"_L1).toArray();
    QCOMPARE(arguments.count(), 2);
    QCOMPARE(arguments.at(0).toObject().value("required"_L1).toBool(), true);

    const QJsonObject response = waitResponse(client, client.getPrompt(u"greeting"_s, {{u"name"_s, u"Laurent"_s}}));
    const McpProtocolGetPromptResult result = McpProtocolGetPromptResult::fromJson(response.value("result"_L1).toObject());
    QCOMPARE(result.description(), u"Greeting"_s);
    QCOMPARE(result.messages().count(), 1);
    const McpProtocolUtils::ContentBlock content = result.messages().at(0).content();
    const auto text = std::get_if<McpProtocolTextContent>(&content);
    QVERIFY(text);
    QCOMPARE(text->text(), u"Say hello to Laurent"_s);
}

void McpProtocolServerProtocolManagerTest::shouldReturnErrorForInvalidPromptRequest()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    server.addPrompt(std::make_unique<GreetingPrompt>());
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    // Unknown prompt
    QCOMPARE(errorCode(waitResponse(client, client.getPrompt(u"unknown"_s))), McpProtocolServerProtocolManager::invalidParamsCode);
    // Missing required argument "name"
    const QJsonObject response = waitResponse(client, client.getPrompt(u"greeting"_s, {{u"style"_s, u"formal"_s}}));
    QCOMPARE(errorCode(response), McpProtocolServerProtocolManager::invalidParamsCode);
    QVERIFY(response.value("error"_L1).toObject().value("message"_L1).toString().contains(u"name"_s));
}

void McpProtocolServerProtocolManagerTest::shouldListAndReadResource()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    server.addResource(std::make_unique<TextResource>(u"file:///a.txt"_s, u"content of a"_s));
    // Same uri: replaced
    server.addResource(std::make_unique<TextResource>(u"file:///a.txt"_s, u"new content of a"_s));
    QCOMPARE(server.resources().count(), 1);
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    const QJsonObject list = waitResponse(client, client.executeAction(MethodType::ListResources));
    QCOMPARE(names(list, u"resources"_s), QStringList{u"file:///a.txt"_s});

    const QJsonObject response = waitResponse(client, client.readResource(u"file:///a.txt"_s));
    const McpProtocolReadResourceResult result = McpProtocolReadResourceResult::fromJson(response.value("result"_L1).toObject());
    const QList<McpProtocolUtils::EmbeddedResourceResource> allContents = result.contents();
    QCOMPARE(allContents.count(), 1);
    const auto contents = std::get_if<McpProtocolTextResourceContents>(&allContents.at(0));
    QVERIFY(contents);
    QCOMPARE(contents->text(), u"new content of a"_s);
    QCOMPARE(contents->uri(), u"file:///a.txt"_s);
    QCOMPARE(contents->mimeType(), u"text/plain"_s);
}

void McpProtocolServerProtocolManagerTest::shouldReturnErrorForInvalidResourceRequest()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    server.addResource(std::make_unique<TextResource>(u"file:///broken.txt"_s, QString()));
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    QCOMPARE(errorCode(waitResponse(client, client.readResource(u"file:///unknown.txt"_s))), McpProtocolServerProtocolManager::resourceNotFoundCode);
    QCOMPARE(errorCode(waitResponse(client, client.readResource(u"file:///broken.txt"_s))), McpProtocolServerProtocolManager::internalErrorCode);
}

void McpProtocolServerProtocolManagerTest::shouldPaginatePromptsAndResources()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    server.setToolsPageSize(2);
    for (const auto &name : {u"p1"_s, u"p2"_s, u"p3"_s}) {
        server.addPrompt(std::make_unique<GreetingPrompt>(name));
        server.addResource(std::make_unique<TextResource>(u"file:///%1"_s.arg(name), name));
    }
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    QList<McpProtocolClientProtocolManager::MessageInfo> infos;
    connect(&client, &McpProtocolClientProtocolManager::messageLogged, this, [&infos](const McpProtocolClientProtocolManager::MessageInfo &info) {
        if (info.direction == McpProtocolClientProtocolManager::MessageDirection::Sent) {
            infos.append(info);
        }
    });
    // Client merges all pages
    const QJsonObject prompts = waitResponse(client, client.executeAction(MethodType::ListPrompts));
    QCOMPARE(names(prompts, u"prompts"_s), (QStringList{u"p1"_s, u"p2"_s, u"p3"_s}));
    QCOMPARE(infos.count(), 2);
    const QJsonObject resources = waitResponse(client, client.executeAction(MethodType::ListResources));
    QCOMPARE(names(resources, u"resources"_s), (QStringList{u"file:///p1"_s, u"file:///p2"_s, u"file:///p3"_s}));
    QCOMPARE(infos.count(), 4);
}

void McpProtocolServerProtocolManagerTest::shouldNotifyListChanged()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    server.addPrompt(std::make_unique<GreetingPrompt>());
    server.addResource(std::make_unique<TextResource>(u"file:///a.txt"_s, u"a"_s));
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    const QSignalSpy promptsSpy(&client, &McpProtocolClientProtocolManager::promptsListChanged);
    const QSignalSpy resourcesSpy(&client, &McpProtocolClientProtocolManager::resourcesListChanged);
    // Notifications use event stream opened by client after initialization
    QTest::qWait(200);
    server.addPrompt(std::make_unique<GreetingPrompt>(u"other"_s));
    QTRY_COMPARE(promptsSpy.count(), 1);
    QVERIFY(server.removePrompt(u"greeting"_s));
    QTRY_COMPARE(promptsSpy.count(), 2);
    QVERIFY(!server.removePrompt(u"greeting"_s));
    QVERIFY(server.removeResource(u"file:///a.txt"_s));
    QTRY_COMPARE(resourcesSpy.count(), 1);
    QVERIFY(!server.removeResource(u"file:///a.txt"_s));
    QCOMPARE(server.prompts().count(), 1);
    QVERIFY(server.resources().isEmpty());
}

void McpProtocolServerProtocolManagerTest::shouldCompletePromptArgument()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    server.addPrompt(std::make_unique<GreetingPrompt>());
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    QVERIFY(client.initializeResult().capabilities().completions().has_value());

    QJsonObject response = waitResponse(client, client.complete(completeParams(promptReference(u"greeting"_s), u"style"_s, u"f"_s)));
    McpProtocolCompleteResult::Completion completion = McpProtocolCompleteResult::fromJson(response.value("result"_L1).toObject()).completion();
    QCOMPARE(completion.values(), (QStringList{u"formal"_s, u"friendly"_s, u"funny"_s}));
    QCOMPARE(completion.hasMore(), false);
    QVERIFY(!completion.total().has_value());

    response = waitResponse(client, client.complete(completeParams(promptReference(u"greeting"_s), u"style"_s, u"fr"_s)));
    completion = McpProtocolCompleteResult::fromJson(response.value("result"_L1).toObject()).completion();
    QCOMPARE(completion.values(), QStringList{u"friendly"_s});

    // Result is truncated
    response = waitResponse(client, client.complete(completeParams(promptReference(u"greeting"_s), u"name"_s, u"a"_s)));
    completion = McpProtocolCompleteResult::fromJson(response.value("result"_L1).toObject()).completion();
    QCOMPARE(completion.values().count(), McpProtocolServerProtocolManager::maxCompletionValues);
    QCOMPARE(completion.values().constFirst(), u"a0"_s);
    QCOMPARE(completion.hasMore(), true);
    QCOMPARE(completion.total(), 150);

    // No completion for this argument
    response = waitResponse(client, client.complete(completeParams(promptReference(u"greeting"_s), u"other"_s, {})));
    completion = McpProtocolCompleteResult::fromJson(response.value("result"_L1).toObject()).completion();
    QVERIFY(completion.values().isEmpty());
    QCOMPARE(completion.hasMore(), false);
}

void McpProtocolServerProtocolManagerTest::shouldReturnErrorForInvalidCompletionRequest()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    server.addPrompt(std::make_unique<GreetingPrompt>());
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    // Unknown prompt
    QCOMPARE(errorCode(waitResponse(client, client.complete(completeParams(promptReference(u"unknown"_s), u"style"_s, {})))),
             McpProtocolServerProtocolManager::invalidParamsCode);
    // No resource template by default
    McpProtocolResourceTemplateReference templateReference;
    templateReference.setUri(u"file:///{path}"_s);
    QCOMPARE(errorCode(waitResponse(client, client.complete(completeParams(templateReference, u"path"_s, {})))),
             McpProtocolServerProtocolManager::invalidParamsCode);
}

void McpProtocolServerProtocolManagerTest::shouldSendLogMessagesFromLoggingLevel()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    QCOMPARE(server.loggingLevel(), McpProtocolUtils::LoggingLevel::Info);
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    QVERIFY(client.initializeResult().capabilities().logging().has_value());
    // No prompt: completions are not supported
    QVERIFY(!client.initializeResult().capabilities().completions().has_value());

    QList<McpProtocolLoggingMessageNotificationParams> messages;
    connect(&client, &McpProtocolClientProtocolManager::loggingMessageReceived, this, [&messages](const McpProtocolLoggingMessageNotificationParams &params) {
        messages.append(params);
    });
    // Notifications use event stream opened by client after initialization
    QTest::qWait(200);
    // Debug is lower than default level
    server.sendLogMessage(McpProtocolUtils::LoggingLevel::Debug, u"debug"_s);
    server.sendLogMessage(McpProtocolUtils::LoggingLevel::Info, u"info"_s);
    QTRY_COMPARE(messages.count(), 1);
    QCOMPARE(messages.at(0).level(), McpProtocolUtils::LoggingLevel::Info);
    QCOMPARE(messages.at(0).data(), QJsonValue(u"info"_s));
    QVERIFY(!messages.at(0).logger().has_value());

    const QJsonObject response = waitResponse(client, client.setLoggingLevel(McpProtocolUtils::LoggingLevel::Error));
    QVERIFY(response.contains("result"_L1));
    QCOMPARE(server.loggingLevel(), McpProtocolUtils::LoggingLevel::Error);
    server.sendLogMessage(McpProtocolUtils::LoggingLevel::Warning, u"warning"_s);
    const QJsonObject data{{u"text"_s, u"critical"_s}};
    server.sendLogMessage(McpProtocolUtils::LoggingLevel::Critical, data, u"database"_s);
    QTRY_COMPARE(messages.count(), 2);
    QCOMPARE(messages.at(1).level(), McpProtocolUtils::LoggingLevel::Critical);
    QCOMPARE(messages.at(1).data(), QJsonValue(data));
    QCOMPARE(messages.at(1).logger(), u"database"_s);
}

void McpProtocolServerProtocolManagerTest::shouldNotSendClientRequestsWithoutCapabilities()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    // Server is not running
    QCOMPARE(server.requestRoots(), -1);
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    initialize(client);
    const McpProtocolClientCapabilities capabilities = server.clientCapabilities();
    QVERIFY(!capabilities.sampling().has_value());
    QVERIFY(!capabilities.elicitation().has_value());
    QVERIFY(!capabilities.roots().has_value());
    QCOMPARE(server.requestSampling(samplingParams(u"hello"_s)), -1);
    QCOMPARE(server.requestElicitation(formParams(u"name?"_s)), -1);
    QCOMPARE(server.requestRoots(), -1);
}

void McpProtocolServerProtocolManagerTest::shouldRequestSampling()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    client.setSamplingSupported(true);
    bool reject = false;
    connect(&client,
            &McpProtocolClientProtocolManager::samplingRequested,
            this,
            [&client, &reject](const McpProtocolUtils::RequestId &id, const McpProtocolCreateMessageRequest &request) {
                if (reject) {
                    client.rejectSampling(id);
                    return;
                }
                const auto content = std::get<McpProtocolTextContent>(request.params().messages().constFirst().content());
                McpProtocolCreateMessageResult result;
                result.setModel(u"model"_s);
                result.setRole(McpProtocolUtils::Role::Assistant);
                result.setContent(textContent(u"answer to "_s + content.text()));
                client.respondToSampling(id, result);
            });
    initialize(client);
    QVERIFY(server.clientCapabilities().sampling().has_value());

    const QSignalSpy resultSpy(&server, &McpProtocolServerProtocolManager::samplingResultReceived);
    const QSignalSpy failedSpy(&server, &McpProtocolServerProtocolManager::clientRequestFailed);
    // Invalid params: no message
    QCOMPARE(server.requestSampling(McpProtocolCreateMessageRequestParams()), -1);
    // Client doesn't support tools in sampling
    McpProtocolCreateMessageRequestParams toolsParams = samplingParams(u"hello"_s);
    toolsParams.setTools(QList<McpProtocolTool>{});
    QCOMPARE(server.requestSampling(toolsParams), -1);

    const qint64 requestId = server.requestSampling(samplingParams(u"hello"_s));
    QVERIFY(requestId > 0);
    QTRY_COMPARE(resultSpy.count(), 1);
    QCOMPARE(resultSpy.at(0).at(0).toLongLong(), requestId);
    const auto result = resultSpy.at(0).at(1).value<McpProtocolCreateMessageResult>();
    QCOMPARE(result.model(), u"model"_s);
    QCOMPARE(std::get<McpProtocolTextContent>(result.content()).text(), u"answer to hello"_s);

    reject = true;
    const qint64 rejectedId = server.requestSampling(samplingParams(u"hello"_s));
    QVERIFY(rejectedId != requestId);
    QTRY_COMPARE(failedSpy.count(), 1);
    QCOMPARE(failedSpy.at(0).at(0).toLongLong(), rejectedId);
    QCOMPARE(failedSpy.at(0).at(1).toInt(), -1);
    QCOMPARE(resultSpy.count(), 1);
}

void McpProtocolServerProtocolManagerTest::shouldRequestElicitation()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    client.setElicitationSupported(true);
    bool answer = true;
    connect(&client,
            &McpProtocolClientProtocolManager::elicitationRequested,
            this,
            [&client, &answer](const McpProtocolUtils::RequestId &id, const McpProtocolElicitRequest &request) {
                QCOMPARE(std::get<McpProtocolElicitRequestFormParams>(request.params()).message(), u"name?"_s);
                if (!answer) {
                    // User didn't answer yet
                    return;
                }
                McpProtocolElicitResult result;
                result.setAction(McpProtocolElicitResult::Action::Accept);
                result.setContent(QMap<QString, McpProtocolUtils::ElicitResultContentValue>{{u"name"_s, u"Konqi"_s}});
                client.respondToElicitation(id, result);
            });
    initialize(client);
    QVERIFY(server.clientCapabilities().elicitation().has_value());

    // Client only supports form mode
    McpProtocolElicitRequestURLParams urlParams;
    urlParams.setElicitationId(u"1"_s);
    urlParams.setMessage(u"login"_s);
    urlParams.setUrl(u"https://kde.org"_s);
    QCOMPARE(server.requestElicitation(urlParams), -1);

    const QSignalSpy resultSpy(&server, &McpProtocolServerProtocolManager::elicitationResultReceived);
    const qint64 requestId = server.requestElicitation(formParams(u"name?"_s));
    QVERIFY(requestId > 0);
    QTRY_COMPARE(resultSpy.count(), 1);
    QCOMPARE(resultSpy.at(0).at(0).toLongLong(), requestId);
    const auto result = resultSpy.at(0).at(1).value<McpProtocolElicitResult>();
    QCOMPARE(result.action(), McpProtocolElicitResult::Action::Accept);
    QCOMPARE(std::get<QString>(result.content()->value(u"name"_s)), u"Konqi"_s);

    // Server cancels request while user doesn't answer
    answer = false;
    const QSignalSpy requestedSpy(&client, &McpProtocolClientProtocolManager::elicitationRequested);
    const QSignalSpy cancelledSpy(&client, &McpProtocolClientProtocolManager::userRequestCancelled);
    const qint64 cancelledId = server.requestElicitation(formParams(u"name?"_s));
    QTRY_COMPARE(requestedSpy.count(), 1);
    server.cancelClientRequest(cancelledId, u"Timeout"_s);
    QTRY_COMPARE(cancelledSpy.count(), 1);
    QCOMPARE(cancelledSpy.at(0).at(0).value<McpProtocolUtils::RequestId>(), McpProtocolUtils::RequestId(cancelledId));
}

void McpProtocolServerProtocolManagerTest::shouldRequestRoots()
{
    const QUrl url = freeUrl();
    McpProtocolServerProtocolManager server(McpProtocolPlugin::TransportType::StreamableHttp);
    startServer(server, url);

    McpProtocolClientProtocolManager client(serverSettings(url));
    client.setRootsSupported(true);
    client.setRoots({root(u"file:///home/user/project"_s)});
    initialize(client);
    QCOMPARE(server.clientCapabilities().roots()->listChanged(), true);

    const QSignalSpy rootsSpy(&server, &McpProtocolServerProtocolManager::rootsReceived);
    const qint64 requestId = server.requestRoots();
    QVERIFY(requestId > 0);
    QTRY_COMPARE(rootsSpy.count(), 1);
    QCOMPARE(rootsSpy.at(0).at(0).toLongLong(), requestId);
    QCOMPARE(rootsSpy.at(0).at(1).value<QList<McpProtocolRoot>>(), QList<McpProtocolRoot>{root(u"file:///home/user/project"_s)});

    const QSignalSpy changedSpy(&server, &McpProtocolServerProtocolManager::rootsListChanged);
    client.setRoots({root(u"file:///tmp"_s)});
    QTRY_COMPARE(changedSpy.count(), 1);
}

#include "moc_mcpprotocolserverprotocolmanagertest.cpp"
