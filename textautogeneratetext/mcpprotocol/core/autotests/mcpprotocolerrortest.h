/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class McpProtocolErrorTest : public QObject
{
    Q_OBJECT
public:
    explicit McpProtocolErrorTest(QObject *parent = nullptr);
    ~McpProtocolErrorTest() override = default;

private Q_SLOTS:
    void shouldhaveDefaultValues();
};
