/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolCancelledNotificationParamsTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolCancelledNotificationParamsTest(QObject *parent = nullptr);
    ~McpProtocolCancelledNotificationParamsTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
