/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>
class McpServerStreamHttpPluginInterface;
class McpServerStreamHttp : public QObject
{
    Q_OBJECT
public:
    explicit McpServerStreamHttp(McpServerStreamHttpPluginInterface *interface, QObject *parent = nullptr);
    ~McpServerStreamHttp() override;

    void connection();

    void send(const QJsonObject &obj);

private:
    McpServerStreamHttpPluginInterface *const mInterface;
};
