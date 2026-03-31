/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>
namespace McpProtocol
{
class McpProtocolServer : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolServer(QObject *parent = nullptr);
    ~McpProtocolServer() override;
};
}
