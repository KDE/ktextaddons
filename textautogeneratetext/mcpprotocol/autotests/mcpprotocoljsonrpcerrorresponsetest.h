/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolJSONRPCErrorResponseTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolJSONRPCErrorResponseTest(QObject *parent = nullptr);
    ~McpProtocolJSONRPCErrorResponseTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
