/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>
class QProcess;
class McpServerStdioPluginInterface;
class McpServerStdio : public QObject
{
    Q_OBJECT
public:
    explicit McpServerStdio(McpServerStdioPluginInterface *interface, QObject *parent = nullptr);
    ~McpServerStdio() override;

    void connection();
    void send(const QJsonObject &obj);

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj);
    void error(const QString &str);
    void finished();

private:
    QProcess *const mProcess;
    McpServerStdioPluginInterface *const mInterface;
};
