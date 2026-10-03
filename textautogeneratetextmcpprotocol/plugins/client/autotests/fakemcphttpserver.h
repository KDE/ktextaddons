/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QHash>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QUrl>
#include <functional>
class QTcpServer;
class QTcpSocket;
// Minimal HTTP server used to simulate a MCP server
class FakeMcpHttpServer : public QObject
{
    Q_OBJECT
public:
    struct Request {
        QByteArray method;
        QByteArray path;
        // Header names are lower case
        QHash<QByteArray, QByteArray> headers;
        QByteArray body;
        [[nodiscard]] QJsonObject json() const;
        [[nodiscard]] QByteArray header(const QByteArray &name) const;
    };
    using Handler = std::function<void(const Request &request, QTcpSocket *socket)>;

    explicit FakeMcpHttpServer(QObject *parent = nullptr);
    ~FakeMcpHttpServer() override;

    [[nodiscard]] QUrl url(const QString &path) const;
    void setHandler(const Handler &handler);
    [[nodiscard]] QList<Request> requests() const;
    [[nodiscard]] QList<Request> requests(const QByteArray &method) const;

    static void sendResponse(QTcpSocket *socket,
                             int status,
                             const QByteArray &contentType = {},
                             const QByteArray &body = {},
                             const QList<std::pair<QByteArray, QByteArray>> &headers = {});
    // Send headers of an event stream and events. Connection is closed when \a close is true.
    static void sendEventStream(QTcpSocket *socket, const QByteArray &events, bool close = true);
    static void sendEvents(QTcpSocket *socket, const QByteArray &events);
    [[nodiscard]] static QByteArray jsonEvent(const QJsonObject &obj, const QByteArray &id = {});

private:
    void readData(QTcpSocket *socket);
    QTcpServer *const mTcpServer;
    QHash<QTcpSocket *, QByteArray> mBuffers;
    QList<Request> mRequests;
    Handler mHandler;
};
