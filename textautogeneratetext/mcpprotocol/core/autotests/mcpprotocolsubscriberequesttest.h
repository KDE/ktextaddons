/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolSubscribeRequestTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolSubscribeRequestTest(QObject *parent = nullptr);
    ~McpProtocolSubscribeRequestTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
