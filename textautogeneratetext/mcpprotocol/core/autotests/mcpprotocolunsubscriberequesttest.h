/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolUnsubscribeRequestTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolUnsubscribeRequestTest(QObject *parent = nullptr);
    ~McpProtocolUnsubscribeRequestTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
