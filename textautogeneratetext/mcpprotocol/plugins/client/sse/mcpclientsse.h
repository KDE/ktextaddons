/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>
class QNetworkAccessManager;
class QNetworkReply;
class QJsonObject;
class McpClientSsePluginInterface;
class McpClientSse : public QObject
{
    Q_OBJECT
public:
    explicit McpClientSse(McpClientSsePluginInterface *interface, QObject *parent = nullptr);
    ~McpClientSse() override;

    void connection();

    void send(const QJsonObject &obj);

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj);
    void error(const QString &str);
    void finished();

private:
    void slotRead();
    QNetworkAccessManager *const mNetworkAccessManager;
    QNetworkReply *mReply = nullptr;
    McpClientSsePluginInterface *const mInterface;
};
