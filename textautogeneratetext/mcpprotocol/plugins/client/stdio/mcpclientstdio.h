/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>
class QProcess;
class McpClientStdio : public QObject
{
    Q_OBJECT
public:
    explicit McpClientStdio(QObject *parent = nullptr);
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
};
