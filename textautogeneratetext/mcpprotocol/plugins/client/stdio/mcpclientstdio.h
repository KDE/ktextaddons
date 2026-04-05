/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>
class QProcess;
class McpClientStdioPluginInterface;
class McpClientStdio : public QObject
{
    Q_OBJECT
public:
    explicit McpClientStdio(McpClientStdioPluginInterface *interface, QObject *parent = nullptr);
    ~McpClientStdio() override;

    void connection();
    void send(const QJsonObject &obj);

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj);
    void error(const QString &str);
    void finished();

private:
    QProcess *const mProcess;
    McpClientStdioPluginInterface *const mInterface;
};
