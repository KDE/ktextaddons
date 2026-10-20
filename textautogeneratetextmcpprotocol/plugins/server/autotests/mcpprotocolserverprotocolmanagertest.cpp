/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolserverprotocolmanagertest.h"
#include <QJsonArray>
#include <QSignalSpy>
#include <QTcpServer>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientProtocolManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolGetPromptResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPromptMessage>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolReadResourceResult>
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
    McpProtocolImplementation serverInfo;
    serverInfo.setName(u"testserver"_s);
    serverInfo.setVersion(u"1.0"_s);
    server.setServerInfo(serverInfo);
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

#include "moc_mcpprotocolserverprotocolmanagertest.cpp"
