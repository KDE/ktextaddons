/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>
namespace McpProtocol
{
class McpProtocolClient : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolClient(QObject *parent = nullptr);
    ~McpProtocolClient() override;
};
}
