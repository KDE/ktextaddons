/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolSubscriptionsListenRequestTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolSubscriptionsListenRequestTest(QObject *parent = nullptr);
    ~McpProtocolSubscriptionsListenRequestTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldConvertJson();
    void shouldRejectMissingRequiredFields();
};
