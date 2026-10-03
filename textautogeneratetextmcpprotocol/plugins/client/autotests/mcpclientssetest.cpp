/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientssetest.h"
#include "fakemcphttpserver.h"
#include "sse/mcpclientsseplugininterface.h"
#include <QPointer>
#include <QSignalSpy>
#include <QTcpSocket>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpClientSseTest)

namespace
{
QJsonObject jsonRequest(const QString &method, int id)
{
    return QJsonObject{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, id}, {"method"_L1, method}};
}
}

McpClientSseTest::McpClientSseTest(QObject *parent)
    : QObject{parent}
{
}

void McpClientSseTest::shouldPostMessagesToEndpoint()
{
    FakeMcpHttpServer server;
    QPointer<QTcpSocket> sseSocket;
    server.setHandler([&sseSocket](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
        if (request.method == "GET") {
            // Keep stream open, answers are sent in it
            sseSocket = socket;
            FakeMcpHttpServer::sendEventStream(socket, ": hello\n\nevent: endpoint\ndata: /messages?sessionId=1\n\n", false);
            return;
        }
        FakeMcpHttpServer::sendResponse(socket, 202);
        const QJsonObject response{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, request.json().value("id"_L1)}, {"result"_L1, QJsonObject{}}};
        // Split event to check buffering
        const QByteArray event = "event: message\n" + FakeMcpHttpServer::jsonEvent(response);
        FakeMcpHttpServer::sendEvents(sseSocket, event.left(10));
        FakeMcpHttpServer::sendEvents(sseSocket, event.mid(10));
    });
    McpClientSsePluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(server.url(u"/sse"_s));
    settings.setHeaders({u"Authorization: Bearer token"_s});
    client.setSettings(settings);
    QSignalSpy startedSpy(&client, &McpClientSsePluginInterface::started);
    QSignalSpy receivedSpy(&client, &McpClientSsePluginInterface::received);
    QSignalSpy finishedSpy(&client, &McpClientSsePluginInterface::finished);
    client.start();
    // Started when endpoint is received
    QTRY_COMPARE(startedSpy.count(), 1);

    client.send(jsonRequest(u"ping"_s, 1));
    QTRY_COMPARE(receivedSpy.count(), 1);
    QCOMPARE(receivedSpy.at(0).at(0).toJsonObject().value("id"_L1).toInt(), 1);
    const auto posts = server.requests("POST");
    QCOMPARE(posts.count(), 1);
    QCOMPARE(posts.at(0).path, "/messages?sessionId=1"_ba);
    QCOMPARE(posts.at(0).header("Authorization"), "Bearer token"_ba);
    QCOMPARE(posts.at(0).json(), jsonRequest(u"ping"_s, 1));

    client.stop();
    QTRY_COMPARE(finishedSpy.count(), 1);
}

void McpClientSseTest::shouldCreateErrorResponseWhenPostFailed()
{
    FakeMcpHttpServer server;
    server.setHandler([](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
        if (request.method == "GET") {
            FakeMcpHttpServer::sendEventStream(socket, "event: endpoint\ndata: /messages\n\n", false);
            return;
        }
        FakeMcpHttpServer::sendResponse(socket, 500);
    });
    McpClientSsePluginInterface client;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
    settings.setServerUrl(server.url(u"/sse"_s));
    client.setSettings(settings);
    QSignalSpy startedSpy(&client, &McpClientSsePluginInterface::started);
    QSignalSpy receivedSpy(&client, &McpClientSsePluginInterface::received);
    client.start();
    QTRY_COMPARE(startedSpy.count(), 1);
    client.send(jsonRequest(u"ping"_s, 7));
    QTRY_COMPARE(receivedSpy.count(), 1);
    const QJsonObject response = receivedSpy.at(0).at(0).toJsonObject();
    QCOMPARE(response.value("id"_L1).toInt(), 7);
    QCOMPARE(response.value("error"_L1).toObject().value("code"_L1).toInt(), -32000);
}

#include "moc_mcpclientssetest.cpp"
