/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/mcpbase.h"
#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include <QList>
#include <QPointer>
#include <memory>
class QTcpServer;
class QTcpSocket;
class McpServerStreamHttpPluginInterface;
/*
 * Server side of the Streamable HTTP transport: listen on serverUrl, receive messages sent by POST,
 * answer requests in the POST response and send other messages in the GET event stream.
 */
class McpServerStreamableHttp : public TextAutoGenerateTextMcpProtocolCore::McpBase
{
    Q_OBJECT
public:
    explicit McpServerStreamableHttp(McpServerStreamHttpPluginInterface *interface, QObject *parent = nullptr);
    ~McpServerStreamableHttp() override;

    void connection() override;
    void send(const QJsonObject &obj) override;
    void stop() override;

private:
    struct HttpRequest {
        QByteArray method;
        QByteArray path;
        // Header names are lower case
        QHash<QByteArray, QByteArray> headers;
        QByteArray body;
    };
    // POST waiting for responses of its requests
    struct PendingPost {
        QPointer<QTcpSocket> socket;
        // Keys of request ids, in order of the batch
        QList<QByteArray> ids;
        QHash<QByteArray, QJsonObject> responses;
        bool batch = false;
        bool initialize = false;
    };
    using PendingPostPtr = std::shared_ptr<PendingPost>;

    void newConnection();
    void readData(QTcpSocket *socket);
    void socketDisconnected(QTcpSocket *socket);
    void handleRequest(QTcpSocket *socket, const HttpRequest &request);
    void handlePost(QTcpSocket *socket, const HttpRequest &request);
    void handleGet(QTcpSocket *socket, const HttpRequest &request);
    void handleDelete(QTcpSocket *socket, const HttpRequest &request);
    [[nodiscard]] bool checkSession(QTcpSocket *socket, const HttpRequest &request);
    [[nodiscard]] bool isAllowedOrigin(const HttpRequest &request) const;
    void sendEvent(const QJsonObject &obj);
    void sendPostResponse(const PendingPostPtr &pending);
    void terminateSession();
    void closeSockets();
    static void writeResponse(QTcpSocket *socket,
                              int status,
                              const QByteArray &contentType = {},
                              const QByteArray &body = {},
                              const QList<std::pair<QByteArray, QByteArray>> &headers = {});
    static void writeJsonRpcError(QTcpSocket *socket, int status, int code, const QString &message);
    QTcpServer *const mTcpServer;
    McpServerStreamHttpPluginInterface *const mInterface;
    QString mPath;
    QByteArray mSessionId;
    // Data received for each connection, until request is complete
    QHash<QTcpSocket *, QByteArray> mBuffers;
    QHash<QByteArray, PendingPostPtr> mPendingRequests;
    // GET stream used to send requests and notifications to client
    QPointer<QTcpSocket> mEventStreamSocket;
    // Messages sent while client doesn't listen event stream
    QList<QJsonObject> mPendingMessages;
    quint64 mEventId = 0;
    bool mStarted = false;
};
