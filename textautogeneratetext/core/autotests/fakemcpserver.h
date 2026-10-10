/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "fakemcphttpserver.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QPointer>
#include <QTcpSocket>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>

using namespace Qt::Literals::StringLiterals;

inline QJsonObject tool(const QString &name, bool readOnly = false)
{
    QJsonObject obj{
        {"name"_L1, name},
        {"description"_L1, u"Description of %1"_s.arg(name)},
        {"inputSchema"_L1, QJsonObject{{"type"_L1, u"object"_s}, {"properties"_L1, QJsonObject{{"city"_L1, QJsonObject{{"type"_L1, u"string"_s}}}}}}}};
    if (readOnly) {
        obj["annotations"_L1] = QJsonObject{{"readOnlyHint"_L1, true}};
    }
    return obj;
}

// MCP server: tools are returned by tools/list, GET stream is kept open to send notifications
class FakeMcpServer
{
public:
    FakeMcpServer()
    {
        server.setHandler([this](const FakeMcpHttpServer::Request &request, QTcpSocket *socket) {
            if (request.method == "GET") {
                eventStream = socket;
                FakeMcpHttpServer::sendEventStream(socket, ": open\n\n", false);
                return;
            }
            if (request.method == "DELETE") {
                FakeMcpHttpServer::sendResponse(socket, 200);
                return;
            }
            const QJsonObject obj = request.json();
            const QString method = obj.value("method"_L1).toString();
            receivedRequests.append(obj);
            QJsonObject result;
            if (method == "initialize"_L1) {
                result = QJsonObject{{"protocolVersion"_L1, u"2025-11-25"_s},
                                     {"capabilities"_L1, QJsonObject{{"tools"_L1, QJsonObject{{"listChanged"_L1, true}}}}},
                                     {"serverInfo"_L1, QJsonObject{{"name"_L1, u"fake"_s}, {"version"_L1, u"1"_s}}}};
            } else if (method == "tools/list"_L1) {
                result = QJsonObject{{"tools"_L1, tools}};
            } else if (method == "tools/call"_L1) {
                // Returns name and arguments (json) of tool
                const QJsonObject params = obj.value("params"_L1).toObject();
                const QString name = params.value("name"_L1).toString();
                if (name == u"slow"_s) {
                    // Never answers
                    return;
                }
                const QString arguments = QString::fromUtf8(QJsonDocument(params.value("arguments"_L1).toObject()).toJson(QJsonDocument::Compact));
                const QJsonObject content{{"type"_L1, u"text"_s}, {"text"_L1, QString(name + u' ' + arguments)}};
                result = QJsonObject{{"content"_L1, QJsonArray{content}}, {"isError"_L1, name == u"failing"_s}};
            } else {
                FakeMcpHttpServer::sendResponse(socket, 202);
                return;
            }
            const QJsonObject response{{"jsonrpc"_L1, u"2.0"_s}, {"id"_L1, obj.value("id"_L1)}, {"result"_L1, result}};
            FakeMcpHttpServer::sendResponse(socket,
                                            200,
                                            "application/json",
                                            QJsonDocument(response).toJson(QJsonDocument::Compact),
                                            {{"Mcp-Session-Id"_ba, "session"_ba}});
        });
    }

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpServer mcpServer(const QString &name) const
    {
        TextAutoGenerateTextMcpProtocolCore::McpServer mcpServer;
        mcpServer.setName(name);
        mcpServer.createUniqueIdentifier();
        mcpServer.setTransportType(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType::StreamableHttp);
        TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings settings;
        settings.setServerUrl(server.url(u"/mcp"_s));
        mcpServer.setSettings(settings);
        return mcpServer;
    }

    FakeMcpHttpServer server;
    QJsonArray tools{tool(u"weather"_s, true), tool(u"get time"_s)};
    QPointer<QTcpSocket> eventStream;
    // Requests and notifications received from client
    QList<QJsonObject> receivedRequests;
};
