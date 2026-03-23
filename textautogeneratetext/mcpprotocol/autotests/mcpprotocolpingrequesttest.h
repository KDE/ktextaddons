/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolPingRequestTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolPingRequestTest(QObject *parent = nullptr);
    ~McpProtocolPingRequestTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
