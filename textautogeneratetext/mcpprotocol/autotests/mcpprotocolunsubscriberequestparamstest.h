/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolUnsubscribeRequestParamsTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolUnsubscribeRequestParamsTest(QObject *parent = nullptr);
    ~McpProtocolUnsubscribeRequestParamsTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
