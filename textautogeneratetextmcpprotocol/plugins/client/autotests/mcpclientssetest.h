/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpClientSseTest : public QObject
{
    Q_OBJECT
public:
    explicit McpClientSseTest(QObject *parent = nullptr);
    ~McpClientSseTest() override = default;

private Q_SLOTS:
    void shouldPostMessagesToEndpoint();
    void shouldCreateErrorResponseWhenPostFailed();
};
