/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolSubscriptionsAcknowledgedNotificationTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolSubscriptionsAcknowledgedNotificationTest(QObject *parent = nullptr);
    ~McpProtocolSubscriptionsAcknowledgedNotificationTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldConvertJson();
    void shouldRejectMissingRequiredFields();
};
