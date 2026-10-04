/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "fakemcphttpserver.h"
#include <QJsonDocument>
#include <QTcpServer>
#include <QTcpSocket>
using namespace Qt::Literals::StringLiterals;

FakeMcpHttpServer::FakeMcpHttpServer(QObject *parent)
    : QObject{parent}
    , mTcpServer(new QTcpServer(this))
{
    mTcpServer->listen(QHostAddress::LocalHost);
    connect(mTcpServer, &QTcpServer::newConnection, this, [this]() {
        while (QTcpSocket *socket = mTcpServer->nextPendingConnection()) {
            connect(socket, &QTcpSocket::readyRead, this, [this, socket]() {
                readData(socket);
            });
            connect(socket, &QTcpSocket::disconnected, this, [this, socket]() {
                mBuffers.remove(socket);
                socket->deleteLater();
            });
        }
    });
}

FakeMcpHttpServer::~FakeMcpHttpServer() = default;

QUrl FakeMcpHttpServer::url(const QString &path) const
{
    return QUrl(u"http://127.0.0.1:%1%2"_s.arg(mTcpServer->serverPort()).arg(path));
}

void FakeMcpHttpServer::setHandler(const Handler &handler)
{
    mHandler = handler;
}

QList<FakeMcpHttpServer::Request> FakeMcpHttpServer::requests() const
{
    return mRequests;
}

QList<FakeMcpHttpServer::Request> FakeMcpHttpServer::requests(const QByteArray &method) const
{
    QList<Request> result;
    for (const auto &request : mRequests) {
        if (request.method == method) {
            result.append(request);
        }
    }
    return result;
}

void FakeMcpHttpServer::readData(QTcpSocket *socket)
{
    QByteArray &buffer = mBuffers[socket];
    buffer.append(socket->readAll());
    // A socket can contain several requests (keep-alive)
    while (true) {
        const qsizetype headerEnd = buffer.indexOf("\r\n\r\n");
        if (headerEnd == -1) {
            return;
        }
        const QList<QByteArray> lines = buffer.left(headerEnd).split('\n');
        Request request;
        const QList<QByteArray> requestLine = lines.constFirst().trimmed().split(' ');
        request.method = requestLine.value(0);
        request.path = requestLine.value(1);
        for (qsizetype i = 1; i < lines.count(); ++i) {
            const QByteArray &line = lines.at(i);
            const qsizetype index = line.indexOf(':');
            if (index > 0) {
                request.headers.insert(line.left(index).trimmed().toLower(), line.mid(index + 1).trimmed());
            }
        }
        const qsizetype contentLength = request.headers.value("content-length").toLongLong();
        if (buffer.size() < headerEnd + 4 + contentLength) {
            return;
        }
        request.body = buffer.mid(headerEnd + 4, contentLength);
        buffer.remove(0, headerEnd + 4 + contentLength);
        mRequests.append(request);
        if (mHandler) {
            mHandler(request, socket);
        } else {
            sendResponse(socket, 404);
        }
        if (socket->state() != QAbstractSocket::ConnectedState) {
            return;
        }
    }
}

QJsonObject FakeMcpHttpServer::Request::json() const
{
    return QJsonDocument::fromJson(body).object();
}

QByteArray FakeMcpHttpServer::Request::header(const QByteArray &name) const
{
    return headers.value(name.toLower());
}

void FakeMcpHttpServer::sendResponse(QTcpSocket *socket,
                                     int status,
                                     const QByteArray &contentType,
                                     const QByteArray &body,
                                     const QList<std::pair<QByteArray, QByteArray>> &headers)
{
    QByteArray response = "HTTP/1.1 " + QByteArray::number(status) + " Status\r\n";
    if (!contentType.isEmpty()) {
        response += "Content-Type: " + contentType + "\r\n";
    }
    for (const auto &[name, value] : headers) {
        response += name + ": " + value + "\r\n";
    }
    response += "Content-Length: " + QByteArray::number(body.size()) + "\r\n\r\n" + body;
    socket->write(response);
}

void FakeMcpHttpServer::sendEventStream(QTcpSocket *socket, const QByteArray &events, bool close)
{
    socket->write("HTTP/1.1 200 OK\r\nContent-Type: text/event-stream\r\nConnection: close\r\n\r\n");
    sendEvents(socket, events);
    if (close) {
        socket->disconnectFromHost();
    }
}

void FakeMcpHttpServer::sendEvents(QTcpSocket *socket, const QByteArray &events)
{
    socket->write(events);
    socket->flush();
}

QByteArray FakeMcpHttpServer::jsonEvent(const QJsonObject &obj, const QByteArray &id)
{
    QByteArray event;
    if (!id.isEmpty()) {
        event += "id: " + id + '\n';
    }
    event += "data: " + QJsonDocument(obj).toJson(QJsonDocument::Compact) + "\n\n";
    return event;
}

#include "moc_fakemcphttpserver.cpp"
